#include<iostream>
#include<vector>
#include<exception>
#include<unordered_map>
#include<string>
#include"VHDEMM_Util.h"

class TreeInsert{
public:
    TreeInsert(std::unordered_map<std::string, std::vector<std::string>> &_kv,int _num_of_value)
    :kv(_kv),n(_num_of_value)
    {
        assert(init());
    };
    bool insert();
    std::vector<std::vector<std::string>>& get_arry();
    std::vector<std::pair<std::string, std::string>>& get_extra_map();

private:
    // private variable
    std::unordered_map<std::string,std::vector<std::string>> kv; // (key,Value)
    int n;
    int height; // height of each full binary tree
    int num; // number of trees
    int total_num; // length of array
    int each_tree_num; // number of nodes in each tree
    std::vector<std::vector<std::string>> tree; 
    std::vector<std::vector<std::string>> array; 
    std::vector<std::pair<std::string, std::string>> extra_map;

    // private function
    bool init(); // init the tree size
    int insert_b0_or_b1(int b0, int b1, std::string v);
    bool insert_into_extra_map(std::string key, std::string value);
    int convert_sha_to_number(std::string hash, int mod);
};