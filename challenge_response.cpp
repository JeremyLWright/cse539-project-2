
#include "RSA.h"
#include "BigInt.h"
#include <iostream>

int main(int argc, const char *argv[])
{
    
    std::cout << "========= Challenge Response ===========\n";
    RSAUtil::RSA rsa1;
    RSAUtil::RSA rsa2;
    RSAUtil::BigInt pub = rsa1.getPublicKey();
    RSAUtil::BigInt mod = rsa1.getModulus();
    rsa2.setPublicKey(pub);
    rsa2.setN(mod);

    RSAUtil::BigInt m(123);
    RSAUtil::BigInt c = rsa1.decrypt(rsa2.encrypt(m));
    if(c == m)
        std::cout << "Challenge-Response Match Successful!\n";
    return 0;
}
