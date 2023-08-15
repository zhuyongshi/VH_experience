#include"Tree.h"

/* public funciton implementation*/

bool TreeInsert::insert(){
    using f1 = std::string(*)(std::string);
    using f2 = std::string(*)(std::string, std::string);
    f1 H1 = VHDEMM::Util::H1;
    f2 H2 = VHDEMM::Util::H_key;

    // insert [K,V]
    for(auto &[k,V] : kv){
        for(int j = 0; j < V.size(); ++ j){
            auto v = V[j];
            auto b0 = convert_sha_to_number(H2(H1(k), std::to_string(j) + "0"), total_num);
            auto b1 = convert_sha_to_number(H2(H1(k), std::to_string(j) + "1"), total_num);
            auto index = insert_b0_or_b1(b0,b1,v);
            if(index==-1){
                assert(insert_into_extra_map(k,v));
            }
        }
    }

    // generate the array
    array.resize(total_num);
    std::vector<std::string> path;
    std::function<void(int, int)> dfs = [&](int t, int x){
        path.push_back(tree[t][x]);

        if(x * 2 + 1 < each_tree_num) // node x has children
        {
            dfs(t, x * 2 + 1);
            dfs(t, x * 2 + 2);
        }
        else // node x do not have children
        {
            int tmp = t * (1<<height) + (x - (1<<height) + 1);
            array[tmp] = path;
        }
        path.pop_back();
    };

    for(int i = 0; i < num; ++ i)
    {
        path.clear();
        dfs(i, 0);
    }

    return true;
}

std::vector<std::vector<std::string>> &TreeInsert::get_arry()
{
    return array;
}

std::vector<std::pair<std::string, std::string>> &TreeInsert::get_extra_map()
{
    return extra_map;
}

/* private funciton implementation*/

bool TreeInsert::init()
{
    try
    {
        // int n  = 0;
        
        num = ceil(n / log2(n));
        height = ceil(log2(log2(n)));
        total_num = (1<<height) * num;
        std::cout<<"num = "<<num<<" height = "<<height<<" total_num = "<<total_num<<std::endl;
        each_tree_num = ((1<<(height+1))-1);
        tree = std::vector<std::vector<std::string>>(num, std::vector<std::string>((1<<(height+1))-1, std::string("*******")));
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool TreeInsert::insert_into_extra_map(std::string key, std::string value)
{
    extra_map.push_back({key,value});
    return true;
}

int TreeInsert::convert_sha_to_number(std::string hash, int mod)
{
    // define a rule for converting sha to number with mod 
    int res = 0;
    for(char &c:hash){
        res = ((res * 256) + static_cast<unsigned char>(c)) % mod;
    }
    return res;
}


int TreeInsert::insert_b0_or_b1(int b0, int b1, std::string v)
{
    try
    {
        // ti represent the index of tree for bi
        int t0 = b0 / (1 << height), t1 = b1 / (1 << height); 
        // di represent the index in ti-tree for bi
        int d0 = ((1 << height) - 1) + b0 % (1 << height),
            d1 = ((1 << height) - 1) + b1 % (1 << height);
        int h0 = height, h1 = height;
        std::string s = "*******";// represent empty
        if(tree[t0][d0] != s) h0++;
        if(tree[t1][d1] != s) h1++;
        while(h0>0 && h0 <= height)
        {
            int parent = (d0 - 1) / 2;
            if(tree[t0][parent] == s) 
            {
                d0 = parent;
                h0--;
            }
            else break;
        }
        while(h1>0 && h1 <= height)
        {
            int parent = (d1 - 1) / 2;
            if(tree[t1][parent] == s) 
            {
                d1 = parent;
                h1--;
            }
            else break;
        }
        
        if(h0 < h1)
        {
            tree[t0][d0] = v;
            return b0;
        }
        else if(h0 > h1)
        {
            tree[t1][d1] = v;
            return b1;
        }
        else if(h0 <= height)
        {
            tree[t0][d0] = v;
            return b0;
        }
        return -1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    
}