#include <queue>
#include <iostream>
#include "RSA.h"



int main(int argc, const char *argv[])
{
   
    //The scheme can be briefly stated as:
    // 
    //To implement the sending and receiving, you may use whatever method you choose, you can use files, pipes or just pass it through functions, or through global memory. Ensure that the random number is around 16 bits long for the program to work correctly.
    RSAUtil::RSA alice(30011, 30013);
    RSAUtil::RSA bob(30029, 30047);

    //a.       Alice obtains the public key and Modulus N of the person (Bob) who is to sign the message
    auto bobs_modulus = bob.getModulus();
    auto bobs_public_key = bob.getPublicKey();
    //b.      Obtain a random number and its inverse with respect to the Modulus [Not phi] of Bob
    RSAUtil::BigInt random_num(13);
    auto random_num_inverse = modInverse(random_num, bobs_modulus);
    //c.       Alice obtains/generates a message to be signed.
    RSAUtil::BigInt alices_message(0x7FFF);
    std::cout << alices_message.toString() << '\n';
    //d.      Alice encrypts the random number with the public key.
    auto cipher_random_num = bob.encrypt(random_num);
    //e.       Alice multiplies this value by the message
    auto mul = alices_message * cipher_random_num;
    //f.       Alice then takes a modulus over N
    auto modded = mul % bobs_modulus;
    //g.      Alice sends it to Bob
    //h.      Bob simply decrypts the received value with the private key
    auto bob_decrypted = bob.decrypt(modded);
    //i.        Bob sends it back to Alice
    //j.        Alice then multiplied the received value with the inverse and takes a modulus over N.
    auto signed_message = (bob_decrypted * random_num_inverse) % bobs_modulus;
    //k.      The value obtained above is the signed message. To obtain the original message from it, again encrypt it with Bob’s Public Key.
    auto clear_text = bob.encrypt(signed_message);

    if(alices_message == clear_text)
        std::cout << "Success.\n";
    else
        std::cout << "I'm sad.\n";
    std::cout << clear_text.toString() << '\n';



    return 0;
}
