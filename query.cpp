#include<iostream>
#include <chrono>
#include <crypto++/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include<cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#include<cryptopp/files.h>
#include <bits/stdc++.h>
#include<sys/time.h>
using namespace std;
using namespace CryptoPP;

string k = "0123456789abcdef";

std::string H_key(const std::string key,const std::string message)
{
    CryptoPP::byte buf[SHA256::DIGESTSIZE];
    std::string salt = key;
    SHA256().CalculateDigest(buf, (CryptoPP::byte *)((message + salt).c_str()), message.length() + salt.length());
    return std::string((const char *)buf, (size_t)SHA256::DIGESTSIZE);
}


int main(int argc, char **argv){
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    //sum是要查询的数目，模拟查询。
    int sum = 1692;
    while (sum--)
    {
      string x = H_key(k,"0"); 
      string y = H_key(x,to_string(sum));
    }
    gettimeofday(&t2, NULL);
    cout<<((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0<<" ms"<<endl;
   
    return 0;
}
