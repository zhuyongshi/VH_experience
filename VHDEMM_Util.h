/*
 * Created by yongshu zhu  on 12/11/2022
 * Email: 993015403@qq.com
 * 
 */

#include <sys/time.h>
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
#include <fstream>
#include <iostream>
using namespace CryptoPP;

#include <thread>
#define MAX_W_LEN 16
#define MAX_OP_LEN 3
#define MAX_IND_LEN 20
#define MAX_NODE_LEN 4
#define MAX_UPDATE_LEN 6
#define MAX_ST_LEN 32 //ST = W||NODE||UPDATE = 26 < 32
#define AES128_KEY_LEN 16
#define LABEL_LEN 48 //(MAX_IND_LEN + MAX_W_LEN)  LABEL = IND||W = 36 < 48
#define UT_LEN 32
#define VALUE_LEN (MAX_IND_LEN + MAX_OP_LEN + MAX_ST_LEN) // VALUE = IND||OP||ST = 55

#define random(x) (rand() % x)



namespace VHDEMM
{

    class Util
    {

    public:
        static std::string H1(const std::string message);  //sha256  盐01

        static std::string H_key(const std::string key,const std::string message);

        static std::string padding(const std::string str);  //填充到16位byte

        static std::string padding(const std::string str, size_t len);

        static std::string Id_padding(const std::string str);  //id-padding 到8位Byte

        static std::string remove_Id_padding(const std::string str); //Id 移除填充

        static std::string remove_padding(const std::string str); //移除填充到16byte的字符串

        static std::string Xor(const std::string s1, const std::string s2);

        static std::string str2hex(const std::string &input);

        static std::string hex2str(const std::string &input);

        static void descrypt(std::string key, std::string iv,std::string ciphertext, std::string &plaintext); //AES解密

        static void encrypt(std::string key, std::string iv,std::string plaintext,std::string &ciphertext);  //AES加密

        static void print(std::string str);   //加密后debug工具

        static bool file_exist (const std::string& path);

        static void clear_txt(std::string path);
    };

} 
