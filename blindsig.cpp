#include <queue>
#include "RSA.h"



int main(int argc, const char *argv[])
{
   
    //The scheme can be briefly stated as:
    //a.       Alice obtains the public key and Modulus N of the person (Bob) who is to sign the message
    //b.      Obtain a random number and its inverse with respect to the Modulus [Not phi] of Bob
    //c.       Alice obtains/generates a message to be signed.
    //d.      Alice encrypts the random number with the public key.
    //e.       Alice multiplies this value by the message
    //f.       Alice then takes a modulus over N
    //g.      Alice sends it to Bob
    //h.      Bob simply decrypts the received value with the private key
    //i.        Bob sends it back to Alice
    //j.        Alice then multiplied the received value with the inverse and takes a modulus over N.
    //k.      The value obtained above is the signed message. To obtain the original message from it, again encrypt it with Bob’s Public Key.
    // 
    //To implement the sending and receiving, you may use whatever method you choose, you can use files, pipes or just pass it through functions, or through global memory. Ensure that the random number is around 16 bits long for the program to work correctly.
    RSAUtil::RSA alice;
    RSAUtil::RSA bob;

    RSAUtil::BitInt alices_message(48);
    RSAUtil::BitInt random_num(13);
    auto cipher_random_num = bob.encrypt(random_num);
    auto mul = alices_message * cipher_random_num;
    auto modded = mul % alice.getModulus();
    auto bob_decrypted = bob.decrypt(modded);
    auto signed_message = modInverse(bob_decrypted, bob.getModulus());
    auto clear_text = bob.encrypt(signed_message);



    return 0;
}
