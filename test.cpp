#include<bits/stdc++.h>
using namespace std;

struct st{
        int cnt_q;  //查询次数
        int cnt; //当前版本下的更新次数
    };
map<string, st> MM_st;



int sum;

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
                sum = sum + MM_st[w].cnt;
            }
            MM_myfile.close();

        }

int main(){
    sum = 0;
    string filename = "/home/zws/Desktop/VH_experience/client/MM_st.txt";
    get_MM_st(filename);
    cout<<sum<<endl;
   
    return 0;
}
