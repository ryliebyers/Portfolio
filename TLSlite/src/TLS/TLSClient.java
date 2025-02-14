package TLS;


import java.io.IOException;
import java.io.*;
import java.security.*;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;
import javax.crypto.*;
import javax.crypto.spec.SecretKeySpec;
import java.math.BigInteger;
import java.net.Socket;
import java.security.cert.Certificate;
import java.util.Arrays;

public class TLSClient {
    static byte[] serverEncrypt;
    static byte[] clientEncrypt;
    static byte[] serverMAC;
    static byte[] clientMAC;
    static byte[] serverIV;
    static byte[] clientIV;
    static byte[] clientNonce;
    public static Certificate clientCert;
    static BigInteger DHPrivateKeyClient;
    static BigInteger DHPublicKeyClient;
    static BigInteger signedDHPublicKeyClient;

    static BigInteger sharedSecretKey;
    static Socket socketToServer;
    static PublicKey clientCaPublicKey;
    static PrivateKey privateKeyFromFile;


// TODO Need to start server main first then client main
    public TLSClient() throws IOException, CertificateException, NoSuchAlgorithmException, InvalidKeySpecException, SignatureException, InvalidKeyException {
        // initialize nonce
        clientNonce = new SecureRandom().generateSeed(32);
        // get signed ca client cert
        clientCert = KeyGeneration.generateCertificate("/Users/ryliebyers/MSDSpring2024/CS6014/TLSlite/TLSlite/src/TLS/CASignedClientCertificate.pem");
        clientCaPublicKey = clientCert.getPublicKey();

        // generate private key to get DH public key
        DHPrivateKeyClient = new BigInteger( new SecureRandom().generateSeed(32));
        DHPublicKeyClient = KeyGeneration.getDHPublicKey(DHPrivateKeyClient);

        // now get signed DHPublicKeyClient
        privateKeyFromFile = KeyGeneration.getKeyFromFile("src/TLS/clientPrivateKey.der");
        signedDHPublicKeyClient = KeyGeneration.getSignedKey(privateKeyFromFile, DHPublicKeyClient);
        socketToServer = new Socket("127.0.0.1", 8080);
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

    public static void main(String[] args) throws IOException, CertificateException, ClassNotFoundException, NoSuchAlgorithmException, InvalidKeySpecException, SignatureException, InvalidKeyException, InvalidAlgorithmParameterException, NoSuchPaddingException, IllegalBlockSizeException, BadPaddingException {
        TLSClient myClient = new TLSClient();
        System.out.println("initialized client");
        // Generate a CA certificate
        Certificate caCertificate = KeyGeneration.generateCertificate("src/TLS/CAcertificate.pem");
        PublicKey caCertPublicKey = caCertificate.getPublicKey();
        System.out.println("Initializing I/O streams for client communication with CA public key: " + caCertPublicKey);
        // Set up object streams for communication
        ObjectOutputStream clientOutputStream = new ObjectOutputStream(myClient.socketToServer.getOutputStream());
        ObjectInputStream clientInputStream = new ObjectInputStream(myClient.socketToServer.getInputStream());

        ByteArrayOutputStream messageLog = new ByteArrayOutputStream();

        // Send client nonce
        clientOutputStream.flush();
        clientOutputStream.writeObject(myClient.clientNonce);
        messageLog.write(myClient.clientNonce);


        // Receive server certificate, DH public key, and signed DH public key
        Certificate serverCert = (Certificate) clientInputStream.readObject();
        BigInteger DHPublicKeyServer = (BigInteger) clientInputStream.readObject();
        BigInteger signedDHPublicKeyServer = (BigInteger) clientInputStream.readObject();


        // Verify server certificate using CA public key
        try {
            serverCert.verify(caCertPublicKey);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        } catch (InvalidKeyException e) {
            throw new RuntimeException(e);
        } catch (NoSuchProviderException e) {
            throw new RuntimeException(e);
        } catch (SignatureException e) {
            throw new RuntimeException(e);
        }


        // Add received data to message log
        messageLog.write(serverCert.getEncoded());
        messageLog.write(DHPublicKeyServer.toByteArray());
        messageLog.write(signedDHPublicKeyServer.toByteArray());
        // Send client certificate, DH public key, and signed DH public key
        clientOutputStream.writeObject(myClient.clientCert);
        clientOutputStream.writeObject(myClient.DHPublicKeyClient);
        clientOutputStream.writeObject(myClient.signedDHPublicKeyClient);
        // Add sent data to message log
        messageLog.write(myClient.clientCert.getEncoded());
        messageLog.write(myClient.DHPublicKeyClient.toByteArray());
        messageLog.write(myClient.signedDHPublicKeyClient.toByteArray());
        // Derive shared secret key from server's DH public key
        myClient.sharedSecretKey = KeyGeneration.getSharedSecretKey(DHPublicKeyServer, myClient.DHPrivateKeyClient);
        System.out.println("Shared secret key derived from server's Diffie-Hellman public key and client's private key.");
        // Generate message authentication codes (MACs) using shared secret key
        makeSecretKeys(myClient.clientNonce, myClient.sharedSecretKey);



        byte[] Server = (byte[]) clientInputStream.readObject();
        byte[] macClientToCompare = KeyGeneration.getMessageToCompare(messageLog.toByteArray(), myClient.serverMAC);

        assert Arrays.equals(Server, macClientToCompare);
        messageLog.write(Server);
        byte[] clientSendBack = KeyGeneration.getMessageToCompare(messageLog.toByteArray(), myClient.clientMAC);
        clientOutputStream.writeObject(clientSendBack);

        byte[] encryptedMsg = (byte[]) clientInputStream.readObject();
        System.out.println("The encrypted message is: " + Arrays.toString(encryptedMsg));






        byte[] decrypted = KeyGeneration.decrypt(encryptedMsg, TLSClient.serverEncrypt, serverIV, TLSClient.serverMAC);


        // -32 bytes bc a mac is a 256 bit
        byte[] noMac = Arrays.copyOf(decrypted, decrypted.length - 32);

        if (KeyGeneration.doMacsMatch(decrypted, myClient.serverMAC)) {

            System.out.println("Decrypted message verified successfully: " +  new String(noMac));

        } else {
            throw new RuntimeException("MAC verification failed: Message integrity compromised.");
        }

        // Send acknowledgement  to server after successful message decryption
        byte[] encryptAck = KeyGeneration.encrypt("ack1".getBytes(), myClient.clientEncrypt, myClient.clientIV, myClient.clientMAC);
        clientOutputStream.writeObject(encryptAck);
        // Receive second encrypted message from server
        byte[] encryptedMsg2 = (byte[]) clientInputStream.readObject();
        System.out.println("The encrypted message2 is: " + Arrays.toString(encryptedMsg2));

        // Decrypt the second message
        byte[] decrypted2 = KeyGeneration.decrypt(encryptedMsg2, myClient.serverEncrypt, myClient.serverIV, myClient.serverMAC);
        byte[] noMac2 = Arrays.copyOf(decrypted2, decrypted2.length - 32);
        if (KeyGeneration.doMacsMatch(decrypted2, myClient.serverMAC)) {
            System.out.println("Decrypted message verified successfully: " +  new String(noMac2));
        } else {
            throw new RuntimeException("MAC verification failed: Message integrity compromised.");
        }

        // Send acknowledgement  to server after successful decryption
        byte[] encryptAck2 = KeyGeneration.encrypt("ack2".getBytes(), myClient.clientEncrypt, myClient.clientIV, myClient.clientMAC);
        clientOutputStream.writeObject(encryptAck2);
    }
}

