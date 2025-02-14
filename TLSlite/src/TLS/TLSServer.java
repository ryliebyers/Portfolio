package TLS;



import java.io.*;
import java.math.BigInteger;
import java.net.ServerSocket;
import java.security.*;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;
import java.util.Arrays;
import javax.crypto.*;
import javax.crypto.spec.SecretKeySpec;
import java.net.Socket;
import java.security.cert.Certificate;

public class TLSServer {
    static byte[] serverEncrypt;
    static byte[] clientEncrypt;
    static byte[] serverMAC;
    static byte[] clientMAC;
    static byte[] serverIV;
    static byte[] clientIV;
    static byte[] serverNonce;
    public static Certificate serverCert;
    static BigInteger DHPrivateKeyServer;
    static BigInteger DHPublicKeyServer;
    static BigInteger signedDHPublicKeyServer;

    static BigInteger sharedSecretKey;

    static ServerSocket serverSocket;

    static Socket socket;
    static PrivateKey privateKeyFromFile;


    public TLSServer() throws IOException, CertificateException, NoSuchAlgorithmException, InvalidKeySpecException, SignatureException, InvalidKeyException {
        this.serverNonce = new SecureRandom().generateSeed(32);
        this.serverCert = KeyGeneration.generateCertificate("/Users/ryliebyers/MSDSpring2024/CS6014/TLSlite/TLSlite/src/TLS/CASignedServerCertificate.pem");

        this.DHPrivateKeyServer = new BigInteger( new SecureRandom().generateSeed(32));
        this.DHPublicKeyServer = KeyGeneration.getDHPublicKey(this.DHPrivateKeyServer);

        this.privateKeyFromFile = KeyGeneration.getKeyFromFile("/Users/ryliebyers/MSDSpring2024/CS6014/TLSlite/TLSlite/src/TLS/serverPrivateKey.der");
        this.signedDHPublicKeyServer = KeyGeneration.getSignedKey(this.privateKeyFromFile, this.DHPublicKeyServer);
        this.serverSocket = new ServerSocket(8080);
    }

    public static void makeSecretKeys(byte[] nonce, BigInteger sharedSecretFromDiffieHellman) throws NoSuchAlgorithmException, InvalidKeyException {
        Mac HMAC = Mac.getInstance("HmacSHA256");
        SecretKeySpec secretKeySpec = new SecretKeySpec(nonce, "HmacSHA256");
        HMAC.init(secretKeySpec);
        HMAC.update(sharedSecretFromDiffieHellman.toByteArray());
        byte[] prk = HMAC.doFinal(sharedSecretFromDiffieHellman.toByteArray());
        serverEncrypt = KeyGeneration.hkdfExpand(prk, "server encrypt");
        clientEncrypt = KeyGeneration.hkdfExpand(serverEncrypt, "client encrypt");
        serverMAC = KeyGeneration.hkdfExpand(clientEncrypt, "server MAC");
        clientMAC = KeyGeneration.hkdfExpand(serverMAC, "client MAC");
        serverIV = KeyGeneration.hkdfExpand(clientMAC, "server IV");
        clientIV = KeyGeneration.hkdfExpand(serverIV, "client IV");
    }



    public static void main(String[] args) throws IOException, CertificateException, NoSuchAlgorithmException, InvalidKeySpecException, SignatureException, InvalidKeyException, ClassNotFoundException, InvalidAlgorithmParameterException, NoSuchPaddingException, IllegalBlockSizeException, BadPaddingException {
        TLSServer myServer = new TLSServer();
        System.out.println("initialized server");

        // Load CA certificate
        Certificate caCertificate = KeyGeneration.generateCertificate("src/TLS/CAcertificate.pem");
        PublicKey caCertPublicKey = caCertificate.getPublicKey();

        // Listen for incoming connections
        while (true) {
            try {
                myServer.socket = myServer.serverSocket.accept();
                System.out.println("Server accepted socket connection...");

                // Set up object streams for communication
                ObjectInputStream inputStreamServer = new ObjectInputStream(myServer.socket.getInputStream());
                ObjectOutputStream outputStreamServer = new ObjectOutputStream(myServer.socket.getOutputStream());

                // Initialize message log
                ByteArrayOutputStream messageLog = new ByteArrayOutputStream();

                // Receive client's nonce
                myServer.serverNonce = (byte[]) inputStreamServer.readObject();
                messageLog.write(myServer.serverNonce);

                // Send server's certificate, DH public key, and signed DH public key to client
                outputStreamServer.writeObject(myServer.serverCert);
                outputStreamServer.writeObject(myServer.DHPublicKeyServer);
                outputStreamServer.writeObject(myServer.signedDHPublicKeyServer);

                // Add server's certificate, DH public key, and signed DH public key to message log
                messageLog.write(myServer.serverCert.getEncoded());

                messageLog.write(myServer.DHPublicKeyServer.toByteArray());

                messageLog.write(myServer.signedDHPublicKeyServer.toByteArray());

                // Receive client's certificate, DH public key, and signed DH public key
                Certificate clientCert = (Certificate) inputStreamServer.readObject();
                BigInteger DHPublicKeyClient = (BigInteger) inputStreamServer.readObject();
                BigInteger signedDHPublicKeyClient = (BigInteger) inputStreamServer.readObject();

                // Verify client's certificate
                try {
                    clientCert.verify(caCertPublicKey);
                } catch (NoSuchProviderException e) {
                    throw new RuntimeException(e);
                }

                // Add client's certificate, DH public key, and signed DH public key to message log
                messageLog.write(clientCert.getEncoded());
                messageLog.write(DHPublicKeyClient.toByteArray());
                messageLog.write(signedDHPublicKeyClient.toByteArray());

                // Derive shared secret key from client's DH public key
                myServer.sharedSecretKey = KeyGeneration.getSharedSecretKey(DHPublicKeyClient, myServer.DHPrivateKeyServer);
                makeSecretKeys(myServer.serverNonce, myServer.sharedSecretKey);



                // Compute and send MAC of message log to client
                byte[] macHistory = KeyGeneration.getMessageToCompare(messageLog.toByteArray(), myServer.serverMAC);

                outputStreamServer.writeObject(macHistory);

                messageLog.write(macHistory);







                // Receive and verify MAC from client
                byte[] macClient = (byte[]) inputStreamServer.readObject();
                byte[] macServerToCompare = KeyGeneration.getMessageToCompare(messageLog.toByteArray(), myServer.clientMAC);
                assert Arrays.equals(macClient, macServerToCompare);
                messageLog.write(macClient);

                // Send first message to client
                String msgToClient = "Hello from server";
                System.out.println("The message to encrypt is: " + msgToClient);



                byte[] encryptMsg = KeyGeneration.encrypt(msgToClient.getBytes(), myServer.serverEncrypt, myServer.serverIV, myServer.serverMAC);


                System.out.println("The cipher message is: " + new String(encryptMsg));

                outputStreamServer.writeObject(encryptMsg);

                // Receive acknowledgment from client for the first message
                byte[] ackToReceive = (byte[]) inputStreamServer.readObject();
                byte[] ackOne = KeyGeneration.decrypt(ackToReceive, myServer.clientEncrypt, myServer.clientIV, myServer.clientMAC);
                byte[] noMac = Arrays.copyOf(ackOne, ackOne.length - 32);
                if (KeyGeneration.doMacsMatch(ackOne, myServer.clientMAC)) {
                    System.out.println("First ack from client: " + new String(noMac));
                } else {
                    throw new RuntimeException("MAC verification failed: Message integrity compromised.");
                }

                // Send second message to client
                String msgToClient2 = "Hello from server2";
                System.out.println("The second Encrypted message: " + msgToClient2);
                byte[] encryptMsg2 = KeyGeneration.encrypt(msgToClient2.getBytes(), myServer.serverEncrypt, myServer.serverIV, myServer.serverMAC);
                System.out.println("The cipher message is: " + new String(encryptMsg2));
                outputStreamServer.writeObject(encryptMsg2);

                // Receive acknowledgment from client for the second message
                byte[] ackToReceive2 = (byte[]) inputStreamServer.readObject();
                byte[] ack2 = KeyGeneration.decrypt(ackToReceive2, myServer.clientEncrypt, myServer.clientIV, myServer.clientMAC);
                byte[] noMac2 = Arrays.copyOf(ack2, ack2.length - 32);
                if (KeyGeneration.doMacsMatch(ack2, myServer.clientMAC)) {
                    System.out.println("Ack from client: " + new String(noMac2));
                } else {
                    throw new RuntimeException("MAC verification failed: Message integrity compromised.");
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }
}

