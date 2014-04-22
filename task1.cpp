#include <vector>
#include <cstdint>
#include "RSA.h"
#include <iostream>
#include <algorithm>

int main(int argc, const char *argv[])
{
    //Primes take from http://en.wikipedia.org/wiki/List_of_prime_numbers
    std::vector<uint32_t> primes{30023, 
        30041, 
        30043, 
        30047, 
        30079, 
        30089, 
        30097, 
        30103, 
        30107, 
        30113, 
        30119, 
        30133, 
        30139, 
        30157, 
        30161, 
        30163, 
        30181, 
        30191, 
        30199, 
        30209, 
        30217, 
        30227, 
        30229, 
        30233, 
        30239, 
        30241, 
        30251, 
        30293, 
        30301, 
        30313, 
        30317, 
        30323, 
        30341, 
        30343, 
        30359, 
        30367, 
        30371, 
        30373, 
        30383, 
        30397, 
        30409, 
        30419, 
        30439, 
        30443, 
        30451, 
        30461, 
        30499, 
        30503, 
        30509, 
        30511, 
        30521, 
        30541, 
        30551, 
        30563, 
        30569, 
        30581, 
        30607, 
        30619, 
        30623, 
        30631, 
        30659, 
        30667, 
        30671, 
        30679, 
        30703, 
        30709, 
        30719, 
        30727, 
        30733, 
        30749, 
        30761, 
        30769, 
        30779, 
        30791, 
        30799, 
        30821, 
        30827, 
        30829, 
        30839, 
        30841, 
        30847, 
        30857, 
        30863, 
        30869, 
        30877, 
        30883, 
        30887, 
        30901, 
        30929, 
        30937, 
        30953, 
        30971, 
        30979, 
        30983, 
        30989};

    std::vector<uint64_t> five_primes(std::begin(primes), std::begin(primes)+5);
    
    std::vector<std::pair<uint64_t, uint64_t>> five_prime_pairs{
        {primes[0], primes[1]}, 
        {primes[2], primes[3]}, 
        {primes[4], primes[5]}, 
        {primes[6], primes[7]}, 
        {primes[8], primes[9]}};


    std::vector<std::pair<uint64_t, uint64_t>> ten_composite_pairs{
        {primes[0]+1, primes[1]+1}, 
        {primes[2]+1, primes[3]+1}, 
        {primes[4]+1, primes[5]+1}, 
        {primes[6]+1, primes[7]+1}, 
        {primes[8]+1, primes[9]+1},
        {primes[10]+1, primes[11]+1}, 
        {primes[12]+1, primes[13]+1}, 
        {primes[14]+1, primes[15]+1}, 
        {primes[16]+1, primes[17]+1}, 
        {primes[18]+1, primes[19]+1}
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
