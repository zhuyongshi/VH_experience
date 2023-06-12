
#include <bits/stdc++.h>
#include "VH_Util.h"
#include <cryptopp/randpool.h>
using namespace std;
using namespace VH;

string k = "0123456789abcdef";
string iv = "0123456789abcdef";
string K_enc = "abcdefghijklmnopq";

namespace VHDEMM{
    struct st{
        int cnt_q;  //查询次数
        int cnt; //当前版本下的更新次数
    };

    class update_operation{
        private:
            map<string, st> MM_st;             // client存的状态表
            string MM_st_txt_path;             // 状态表的文件路径
            vector<string>  keyword;          // 键集合
            int m_k;                          // 键集合的个数
            int up_num;                       // 更新一次上传的键值对个数
            map<string, string> EMM;          // 密文
            string EMM_txt_path;             // 状态表的文件路径
        
        public:
        update_operation(string MM_st_path,int m,string keyword_path,string EMM_path){
            m_k = m;
            srand(time(0));
            up_num = 1;
            MM_st_txt_path = MM_st_path; 
            EMM_txt_path = EMM_path;

            //读入关键字列表
            if(Util::file_exist(keyword_path)){
                cout<<"keyword_path exist"<<endl;
                get_w_array(keyword_path,keyword);
            }else{
                cout<<"The keyword_path don't exist "<<endl;
            }

            //读入状态表
            if(Util::file_exist(MM_st_txt_path)){
                cout<<"MM_st_txt exist"<<endl;
                get_MM_st(MM_st_txt_path);
                Util::clear_txt(MM_st_txt_path);
            }else{
                cout<<"MM_st_txt init"<<endl;
                init_MM_st();
            }
           

        }

        ~update_operation()
        {
            std::cout<<"update_operation 的析构函数"<<std::endl;
            //将MM_st写回到文档里
            std::ofstream	os(MM_st_txt_path,std::ios::app);
            for(auto i : MM_st){
                os<<i.first<<" "<<i.second.cnt_q<<" "<<i.second.cnt<<"\n";
             }
            os.close();
            //将密文写回文档里
            std::ofstream	os(EMM_txt_path,std::ios::app);
            for(auto i : EMM){
                os<<i.first<<" "<<i.second<<"\n";
            }
        }

        void update_algorithm(std::string label,std::string v,map<string,queue<pair<string,string>>> &stash,
                              std::string op,int sum)
        {
            std::cout<<"update start"<<std::endl;
            struct timeval t1, t2;
            string random_label;
            gettimeofday(&t1, NULL);
            random_label = gen_random_label();
            vector<pair<string,string>> up(up_num);
            write_stash_and_gen_up(random_label,label,v,op,stash,up);
            
            int num = up_num;
            while(num--){
                string x = Util::H_key(k,random_label+to_string(MM_st[random_label].cnt_q)); 
                string y = Util::H_key(x,to_string(MM_st[random_label].cnt));  
                string e_value;
                Util::encrypt(K_enc,iv,up[num-1].first+','+up[num-1].second,e_value);
                EMM[y] = e_value;
                MM_st[random_label].cnt++;
            }
            
            std::cout<<MM_st[random_label].cnt<<std::endl;
           
            gettimeofday(&t2, NULL);
            std::cout<<"client_update time:"<<((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0<< " ms" << std::endl;

            std::cout<<"update finished"<<std::endl;
        }

        void write_stash_and_gen_up(string random_label,string label,string v,string op, 
                                    map<string,queue<pair<string,string>>> &stash,
                                    vector<pair<string,string>>& up)
        {   
            
            pair<string,string> temp_1;
            temp_1.first = op;temp_1.second = v;

            //如果抽取的键和更新的键不相等，就要将更新的键缓存起来
            if(random_label != label){
                //先检查一下stash中是否有关于更新的键的内容
                if(stash[label].empty()){
                    queue<pair<string,string>> temp;
                    temp.push(temp_1);
                    stash[label] = temp;
                }else{
                    stash[label].push(temp_1);
                }
            }

            //需要更新的内容
            int num = up_num;
            while(num--){
                if(!stash[random_label].empty())
                    up[num - 1] = stash[random_label].front();
                else{
                    up[num - 1].first = "*";
                    up[num - 1].second = "*";
                }   
            }
            
        } 

        string gen_random_label(){
            int temp = rand() % m_k;
            return keyword[temp];
        }
       

        void get_MM_st(string path){
            ifstream MM_myfile(path);
            string w,line;
            cout<<"open file success"<<endl;
            while (getline(MM_myfile, line))								
            {
                stringstream input(line);
                string out;
                input >> out;
                w = out;
                input >> out;
                MM_st[w].cnt_q = stoi(out);
                input >> out;
                MM_st[w].cnt=stoi(out);
            }
            MM_myfile.close();

        }

        void get_w_array(string path, vector<std::string>& kw_set){
            std::ifstream key_myfile(path);
            std::string w;
            while (getline(key_myfile, w))								
            {
                std::stringstream input(w);
                std::string out;
                while (input >> out) {
                    kw_set.push_back(out);
                }
            }
            key_myfile.close();
        }

        void init_MM_st(){
            for(int i=0;i<=m_k;i++){
                MM_st[keyword[i]].cnt_q = 0;
                MM_st[keyword[i]].cnt = 0;
            }
        }
    };

};