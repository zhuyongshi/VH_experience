#include"Tree.h"
// #include "VHDEMM_Util.h"
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
using namespace std;
using namespace CryptoPP;

string iv = "0123456789abcdef";
string K_enc = "abcdefghijklmnopq";
string k = "0123456789abcdef";

void encrypt(std::string key, std::string iv,std::string plaintext,std::string &ciphertext){
        try
		{
			CFB_Mode< AES >::Encryption e;
			e.SetKeyWithIV((CryptoPP::byte*) key.c_str(), AES128_KEY_LEN, (CryptoPP::byte*)iv.c_str(), (size_t)AES::BLOCKSIZE); 
            CryptoPP::byte tmp_new_st[AES128_KEY_LEN];
			e.ProcessData(tmp_new_st, (CryptoPP::byte*) plaintext.c_str(), plaintext.length());
		    ciphertext= std::string((const char*)tmp_new_st, plaintext.length());
		}
		catch(const CryptoPP::Exception& e)
		{
            std::cout<<"encrypt有问题"<<std::endl;
			exit(1);
		}
        
}

std::string H_key(const std::string key,const std::string message)
{
    CryptoPP::byte buf[SHA256::DIGESTSIZE];
    std::string salt = key;
    SHA256().CalculateDigest(buf, (CryptoPP::byte *)((message + salt).c_str()), message.length() + salt.length());
    return std::string((const char *)buf, (size_t)SHA256::DIGESTSIZE);
}


int get_MM(std::string path,std::unordered_map<string,vector<std::string>>& MM){
     std::ifstream MM_myfile(path);
     std::string w,line;
     int sum = 0;
     while (getline(MM_myfile, line))								
	{
		std::stringstream input(line);
		std::string out;
        std::vector<std::string> ids;
        input >> out;
        w = out;
		while (input >> out) {
			ids.push_back(out);
            sum++;
             if(sum >= 104857) break;
		}
        MM[w] = ids;
         if(sum >= 104857) break;
	}
    return sum;
}

//patel的更新策略，这里由于要跟VHDEMM方案一样执行实时更新,实时更新就是一次只有一个文档更新的情况
//y的计算是模拟更新次数的，最大为l，所以以l的位数加密就可以
void update(unordered_map<string,vector<string>> &order_map,int l){
    string update_path = "/home/zws/Desktop/VH_experience/patel/update_2_20.txt";
    ofstream	os(update_path,std::ios::app);
    for(auto i : order_map){
       for(auto j : i.second){
            string v = i.first;
            int num = l-1;
            string e_value;
            string x = H_key(k,j+"0");
            string y = H_key(x,"350");
            os<<y<<" ";
            while (num--)
            {
                encrypt(K_enc,iv,"*******",e_value);
                os<<e_value<<" ";
            }
            os<<endl;
       }
    }
}


int main(){
    string path = "/home/zws/Desktop/111/2_20/inverted.txt";
    unordered_map<string,vector<string>> key_values;
    int n = get_MM(path,key_values);

    path = "/home/zws/Desktop/111/2_20/ans.txt";
    unordered_map<string,vector<string>> order_map;
    int o = get_MM(path,order_map);
    int l = 4393;
    cout<<"order = "<<o<<endl;
    update(order_map,l);
 
    cout<<n<<endl;
    TreeInsert tre(key_values,n*2);
    tre.insert();
    std::vector<std::vector<std::string>> res = tre.get_arry();
    string array_path = "/home/zws/Desktop/VH_experience/patel/emm_2_20.txt";
    ofstream	os(array_path,std::ios::app);
    int sum = 0;
    cout<<"Array:\n";
    for(auto &a:res){
        for(auto&b:a){
            string e_value;
            encrypt(K_enc,iv,b,e_value);
            os<<e_value<<" ";
            sum++;
        }
    }
    os.close();
    cout<<sum<<endl;

    cout<<"Array.size() = "<<res.size()<<endl;

           

    cout<<"Extra_map:\n";
    string client_path = "/home/zws/Desktop/VH_experience/patel/client_2_20.txt";
    ofstream	os_1(client_path,std::ios::app);
    std::vector<std::pair<std::string, std::string>> em = tre.get_extra_map();
    for(auto i : em){
        os_1<<i.first<<" "<<i.second<<endl;
    }
    cout<<endl;
    return 1;
}