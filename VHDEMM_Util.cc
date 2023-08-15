/*
 * Created by yongshi zhu on 12/11/2022
 * Email: 993015403@qq.com
 * 
 */

#include"VHDEMM_Util.h"
using namespace CryptoPP;


namespace VHDEMM
{
    std::string Util::H1(const std::string message)
    {
        byte buf[SHA256::DIGESTSIZE];
        std::string salt = "01";
        SHA256().CalculateDigest(buf, (byte *)((message + salt).c_str()), message.length() + salt.length());
        return std::string((const char *)buf, (size_t)SHA256::DIGESTSIZE);
    } 

    std::string Util::H_key(const std::string key,const std::string message)
    {
        byte buf[SHA256::DIGESTSIZE];
        std::string salt = key;
        SHA256().CalculateDigest(buf, (byte *)((message + salt).c_str()), message.length() + salt.length());
        return std::string((const char *)buf, (size_t)SHA256::DIGESTSIZE);
    }

    std::string Util::padding(const std::string str)
    {
        size_t BS = (size_t)AES::BLOCKSIZE;
        size_t pad_len = BS - str.length() % BS;
        return str + std::string(char(pad_len), pad_len);
    }

    std::string Util::remove_padding(const std::string str)
    {
        int len = str.length();
        int pad_len = int(str[len - 1]);
        bool flag = false;
        for (int i = len - pad_len; i < len; i++)
        {
            if (int(str[i]) != pad_len)
            {
                flag = true;
                break;
            }
        }
        if (flag){
            std::cout << "wrong padding" << std::endl;
            return "";
        }
        else
            return std::string(str, 0, len - pad_len);
    }

    std::string Util::Id_padding(const std::string str){
        //填充id到8byte 
        size_t BS = (size_t)AES::BLOCKSIZE/2;
        size_t pad_len = BS - str.length()%BS;
        return str + std::string(char(pad_len), pad_len);
    }

    std::string Util::remove_Id_padding(const std::string str){
        int len = str.length();
        int pad_len = int(str[len - 1]);
        bool flag = false;
        for (int i = len - pad_len; i < len; i++)
        {
            if (int(str[i]) != pad_len)
            {
                flag = true;
                break;
            }
        }
        if (flag){
            std::cout << "wrong padding" << std::endl;
            return "";
        }
        else
            return std::string(str, 0, len - pad_len);
    }
    
    std::string Util::Xor(const std::string s1, const std::string s2)
    {
        // std::cout<< "in len = "<< s1.length()<<", s1 = "<<s1<<std::endl;
        std::string result = s1;
        if (s1.length() > s2.length())
        {
            //ERROR
            std::cout << "not sufficient size: " << s1.length() << ", " << s2.length() << std::endl;
            return "";
        }

        for (int i = 0; i < result.length(); i++)
        {
            result[i] ^= s2[i];
        }
        return result;
    }
    //AES解密函数
    void Util::descrypt(std::string key,std::string iv, std::string ciphertext,std::string &plaintext){
		try
		{
			CFB_Mode< AES >::Decryption d;
			d.SetKeyWithIV((byte*) key.c_str(), AES128_KEY_LEN, (byte*)iv.c_str(), (size_t)AES::BLOCKSIZE); 
			byte tmp_new_st[AES128_KEY_LEN];
			d.ProcessData(tmp_new_st, (byte*) ciphertext.c_str(), ciphertext.length());
		    plaintext= std::string((const char*)tmp_new_st, ciphertext.length());
		}
		catch(const CryptoPP::Exception& e)
		{
			std::cerr << "in descrypt()解密出问题 " << e.what()<< std::endl;
			exit(1);
		}
        //return plaintext;
    }

    //AES加密函数
    void Util::encrypt(std::string key, std::string iv,std::string plaintext,std::string &ciphertext){
        try
		{
			CFB_Mode< AES >::Encryption e;
			e.SetKeyWithIV((byte*) key.c_str(), AES128_KEY_LEN, (byte*)iv.c_str(), (size_t)AES::BLOCKSIZE); 
            byte tmp_new_st[AES128_KEY_LEN];
			e.ProcessData(tmp_new_st, (byte*) plaintext.c_str(), plaintext.length());
		    ciphertext= std::string((const char*)tmp_new_st, plaintext.length());
		}
		catch(const CryptoPP::Exception& e)
		{
            std::cout<<"encrypt有问题"<<std::endl;
			exit(1);
		}
        
    }

    void Util::print(std::string str){
        for(int i =0;i<str.size();i++){
            int c = (unsigned char)str[i];
            std::cout << c << " ";
        }
        std::cout<<std::endl;
    }



    std::string Util::str2hex(const std::string &input)
    {
        static const char *const lut = "0123456789ABCDEF";
        size_t len = input.length();

        std::string output;
        output.reserve(2 * len);
        for (size_t i = 0; i < len; ++i)
        {
            const unsigned char c = input[i];
            output.push_back(lut[c >> 4]);
            output.push_back(lut[c & 15]);
        }
        return output;
    }

    std::string Util::hex2str(const std::string &input)
    {
        static const char *const lut = "0123456789ABCDEF";
        size_t len = input.length();
        if (len & 1)
            throw std::invalid_argument("odd length");

        std::string output;
        output.reserve(len / 2);
        for (size_t i = 0; i < len; i += 2)
        {
            char a = input[i];
            const char *p = std::lower_bound(lut, lut + 16, a);
            if (*p != a)
                throw std::invalid_argument("not a hex digit");

            char b = input[i + 1];
            const char *q = std::lower_bound(lut, lut + 16, b);
            if (*q != b)
                throw std::invalid_argument("not a hex digit");

            output.push_back(((p - lut) << 4) | (q - lut));
        }
        return output;
    }


    
    bool Util::file_exist (const std::string& path) {
        return ( access( path.c_str(), F_OK ) != -1 );
    }

    void Util::clear_txt(std::string path){
        std::ofstream clear;
        clear.open(path,std::ios::out);
        clear.close();
    }

} // namespace VH
