#include <vector>
#include <cstdint>
#include "RSA.h"
#include <iostream>
#include <algorithm>
#include <primesieve.hpp>

int main(int argc, const char *argv[])
{
    std::vector<uint64_t> primes;            
    primesieve::generate_n_primes(30, 30000, &primes);

    auto p = std::begin(primes);
    std::vector<uint64_t> five_primes(p, p+5);

    std::vector<std::pair<uint64_t, uint64_t>> five_prime_pairs;
    for(int i = 0; i < 5; ++i)
    {
        five_prime_pairs.emplace_back(*p, *(p++));
    }

    std::vector<std::pair<uint64_t, uint64_t>> ten_composite_pairs;
    for(int i = 0; i < 10; ++i)
    {
        ten_composite_pairs.emplace_back((*p)+1, (*(p++))+1);
    };

    std::cout << "========= Default Constructor ===========\n";
    //do some asserts here to show correctness to TA.
    std::vector<int> ns(10);
    std::iota(std::begin(ns), std::end(ns), 0);
    for(auto& n : ns)
    {
        RSAUtil::RSA r;
        RSAUtil::BigInt m(123456);
        auto ciphertext = r.encrypt(m);
        auto cleartext = r.decrypt(ciphertext);
        if(m == cleartext)
            std::cout << n << ": Correct decrypt\n";
    }
    
    std::cout << "========= Single Constructor ===========\n";
    for(auto& n : five_primes)
    {
        RSAUtil::RSA r(n);
        RSAUtil::BigInt m(123456);
        auto ciphertext = r.encrypt(m);
        auto cleartext = r.decrypt(ciphertext);
        if(m == cleartext)
            std::cout << n << ": Correct decrypt\n";
        else
            std::cout << n << ": Bad decrypt\n";

    }
    
    std::cout << "========= Prime Pairs Constructor ===========\n";
    for(auto& n : five_prime_pairs)
    {
        RSAUtil::RSA r(n.first, n.second);
        RSAUtil::BigInt m(123456);
        auto ciphertext = r.encrypt(m);
        auto cleartext = r.decrypt(ciphertext);
        if(m == cleartext)
            std::cout << n.first << ": Correct decrypt\n";
        else
            std::cout << n.first << ": Bad decrypt\n";

    }
    
    std::cout << "========= Composite Pair Constructor ===========\n";
    for(auto& n : ten_composite_pairs)
    {
        RSAUtil::RSA r(n.first, n.second);
        RSAUtil::BigInt m(123456);
        auto ciphertext = r.encrypt(m);
        auto cleartext = r.decrypt(ciphertext);
        if(m == cleartext)
            std::cout << n.first << ": Correct decrypt\n";
        else
            std::cout << n.first << ": Bad decrypt\n";

    }


    std::cout << "========= Challenge Response ===========\n";
    RSAUtil::RSA rsa1;
    RSAUtil::RSA rsa2;
    auto pub = rsa1.getPublicKey();
    auto mod = rsa1.getModulus();
    rsa2.setPublicKey(pub);
    rsa2.setN(mod);

    RSAUtil::BigInt m(123);
    auto c = rsa1.decrypt(rsa2.encrypt(m));
    if(c == m)
        std::cout << "Successful!\n";
    


    return 0;
}