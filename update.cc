#include<iostream>
#include"update_operation.h"
#include <chrono>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv){
    srand((unsigned)time(NULL));
    if (argc < 8)
    {
        std::cerr<< argc << "参数个数小于8个" << std::endl;
        exit(-1);
    } 

    string MM_st_path = argv[1];
    int m = atoi(argv[2]);
    int l = atoi(argv[8]);
    string keyword_path = argv[3];
    string EMM_path = argv[4];
    string time_record_path = argv[9];

    VHDEMM::update_operation uop(MM_st_path,m,keyword_path,EMM_path,time_record_path);

    string stash_path = argv[5];
    map<string,queue<pair<string,string>>> stash;
    VHDEMM::get_stash(stash_path,stash);
    VHDEMM::Util::clear_txt(stash_path);

    int up_num = atoi(argv[6]);
    string order_MM_path = argv[7];
    cout<< "取update pair!" <<endl;
    vector<pair<string,string>> up_pair(up_num);
    VHDEMM::get_update_pair(order_MM_path,up_pair);

    int m_1 = up_num/l;
    int sum = 0;

    for(auto i : up_pair){
        sum++;
        uop.update_algorithm(i.first,i.second,stash,"0",m_1,sum,up_num);
    }

    VHDEMM::write_stash_txt(stash_path,stash);
    cout<<"update end!"<<endl;
    return 0;
}

/*
    运行update命令：
    ./update $MM_st_path $m $keyword_path $EMM_path $stash_path $up_num $order_MM_path $l
*/