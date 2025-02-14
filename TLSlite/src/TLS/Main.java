package TLS;

import java.math.BigInteger;
import java.security.*;



public class Main {


    public static void main(String[] args) {

        // Diffie Hellman 2048 bit hexadecimal value
        String DH2048 = "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA18217C32905E462E36CE3BE39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9DE2BCBF6955817183995497CEA956AE515D2261898FA051015728E5A8AACAA68FFFFFFFFFFFFFFFF";
        BigInteger primeModulus = new BigInteger(DH2048, 16);


        // Generating Diffie-Hellman private key for the server
        byte DHServerPrivateKey[] = new SecureRandom().generateSeed(32);
        BigInteger DHPrivateKeyServer = new BigInteger(DHServerPrivateKey);

        // Generating Diffie-Hellman public key for the server
        BigInteger DHPublicKeyServer = new BigInteger("2").modPow(DHPrivateKeyServer, primeModulus);



        // Generating Diffie-Hellman private key for the client
        byte DHClientPrivateKey[] = new SecureRandom().generateSeed(32);
        BigInteger DHPrivateKeyClient = new BigInteger(DHClientPrivateKey);

        // Generating Diffie-Hellman public key for the client
        BigInteger DHPublicKeyClient = new BigInteger("2").modPow(DHPrivateKeyClient, primeModulus);

        // Computing shared secret keys using the Diffie-Hellman key exchange protocol
        BigInteger sharedClientKey = DHPublicKeyServer.modPow(DHPrivateKeyClient, primeModulus);
        BigInteger sharedServerKey = DHPublicKeyClient.modPow(DHPrivateKeyServer, primeModulus);

        // Printing shared secret keys
        System.out.println("Key from client: " + sharedClientKey);
        System.out.println("key from server: " + sharedServerKey);

    }
}
