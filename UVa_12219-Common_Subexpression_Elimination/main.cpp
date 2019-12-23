#include <iostream>
#include <cstring>
#include <cfloat>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <map>
#include <numeric>
#include <climits>
#include <cstring>
#include <list>
#include <queue>
#include <utility>
#include <functional>
#include <unordered_map>
#include <set>

using std::queue;
using std::pair;
using std::make_pair;
using std::priority_queue;
using std::list;
using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::greater;
using std::unordered_map;
using std::set;


/* TLE 此代码没有用到树的概念
const int MAX_N = 50010;
int ncount;
string str;
unordered_map<string, char> nodes;


void dfs(int beg, int end){
    string node = str.substr(beg, end-beg);
    if(nodes.count(node)){
        //不能用1个字符来替代，会导致str的长度变化，beg，end失效
        str.replace(str.begin()+beg, str.begin()+end, end-beg, nodes[node]);
    }else{
        ++ncount;
        nodes.emplace(node, static_cast<char>('0'+ncount));
    }


    int index = 0;//存放第一个左括号的ind
    for(int i=beg; i!=end; ++i){
        if(str[i]=='('){
            index = i;
            break;
        }
    }

    //没有括号，不用再分
    if(!index){
        return;
    }else{
        //寻找分界的逗号
        int flag = 0;
        for(int i=index+1; i!=end-1; ++i){
            if(str[i]=='(')
                ++flag;
            else if(str[i]==')')
                --flag;
            else if(str[i]==','){
                //找到分界逗号
                if(!flag){
                    dfs(index+1, i);
                    dfs(i+1, end-1);
                    return;
                }
            }
        }

    }
}

void elliminate_duplicate(){
     //消除多余数字
    for(int i=0; i<str.size(); ++i){
        if(str[i]>='0' && str[i] <='9'){
            int last = i+1;
            while(str[last]>='0' && str[last] <='9'){
                ++last;
            }
            str.replace(str.begin()+i, str.begin()+last, 1, str[i]);
        }
    }
}
 */

string str;
int ncount;
int pos;
const int MAX_N = 50010;

struct SubTree{
    string s;
    int l, r;
    SubTree():s(""), l(0), r(0) { }

    bool operator < (const SubTree & rhs) const {
        return s < rhs.s
               || (s == rhs.s && l < rhs.l)
               || (s == rhs.s && l == rhs.l && r < rhs.r);
    }
}sub_trees[MAX_N];

map<SubTree, int> ID;

int buildTree(){
    SubTree st;

    while(isalpha(str[pos])){
        st.s.push_back(str[pos]);
        ++pos;
    }
    if(str[pos]=='('){
        ++pos;
        st.l = buildTree();
        st.r = buildTree();
    }
    ++pos;
    if(!ID.count(st)){
    	//使用ID是因为map检索方便
        ID[st] = ++ncount;
        //使用sub_trees是因为print时根据root号打印节点方便
        sub_trees[ncount] = st;
    }
    return ID[st];
}

map<SubTree, int> new_ID;
int new_ncount;

void print(int root){
    if(!new_ID.count(sub_trees[root])){
        ++new_ncount;
        new_ID.emplace(sub_trees[root], new_ncount);
        cout << sub_trees[root].s;
        if(sub_trees[root].l==0 && sub_trees[root].r==0) return;
        putchar('(');
        print(sub_trees[root].l);
        putchar(',');
        print(sub_trees[root].r);
        putchar(')');
    }else{
        cout << new_ID[sub_trees[root]];
        return;
    }
}

int main() {
    int c;
    cin >> c;
    cin.get();
    while (c--) {
        std::getline(cin, str);

        ncount = 0;
        pos = 0;
        ID.clear();
        int root = buildTree();
        new_ncount = 0;
        new_ID.clear();
        print(root);
        cout << endl;
    }
}
