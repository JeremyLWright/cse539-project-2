#include <iostream>
#include "RSA.h"
using namespace RSAUtil;

struct Alice {
    Alice():
        message(0x7FFF),
        //c.       Alice obtains/generates a message to be signed.
        random_num(13)
    {
        std::cout << "[Alice] Creating Message: " << message.toHexString() << '\n';
        std::cout << "[Alice] Creating Random Number: " << random_num.toHexString() << '\n';
    }

    void receive_bobs_public_key(BigInt key)
    {
        std::cout << "[Alice] Receiving public key from Bob\n";
        bobs_public_key = key;
        //d.      Alice encrypts the random number with the public key.
        encrypting_key.setN(bobs_modulus);
        encrypting_key.setPublicKey(bobs_public_key);
        cipher_random_num = encrypting_key.encrypt(random_num);
        
        //e.       Alice multiplies this value by the message
        auto mul = message * cipher_random_num;
        //f.       Alice then takes a modulus over N
        modded = mul % bobs_modulus;
    }

    void receive_bobs_modulus(BigInt n)
    {
        std::cout << "[Alice] Receiving Bob's modulus\n";
        //b.      Obtain a random number and its inverse with respect to the Modulus [Not phi] of Bob
        bobs_modulus = n;
        random_num_inverse = modInverse(random_num, bobs_modulus);
    }

    void receive_decrypted_value(BigInt d)
    {
        std::cout << "[Alice] Receiving decrypted value from Bob.\n";
        //j.        Alice then multiplied the received value with the inverse and takes a modulus over N.
        auto signed_message = (d * random_num_inverse) % bobs_modulus;
        //k.      The value obtained above is the signed message. To obtain the original message from it, again encrypt it with Bob’s Public Key.
        auto clear_text = encrypting_key.encrypt(signed_message);
        std::cout << "[Alice] Clear Text: " << clear_text.toHexString() << '\n';
    }

    RSA key;
    RSA encrypting_key;
    BigInt message;
    BigInt random_num;
    BigInt random_num_inverse;

    BigInt bobs_modulus;
    BigInt bobs_public_key;

    BigInt cipher_random_num;

    BigInt modded;
};

struct Bob {
    RSA key;

    void receive_modded_value_from_alice(BigInt modded)
    {
        //h.      Bob simply decrypts the received value with the private key
        std::cout << "[Bob] Decrypting value from alice.\n";
        bob_decrypted = key.decrypt(modded);
    }

    BigInt bob_decrypted;
};




int main(int argc, const char *argv[])
{
    Alice alice;
    Bob bob;

    //a.       Alice obtains the public key and Modulus N of the person (Bob) who is to sign the message
    alice.receive_bobs_modulus(bob.key.getModulus());
    alice.receive_bobs_public_key(bob.key.getPublicKey());

    //g.      Alice sends it to Bob
    bob.receive_modded_value_from_alice(alice.modded);

    //i.        Bob sends it back to Alice
    alice.receive_decrypted_value(bob.bob_decrypted);

    return 0;
}
