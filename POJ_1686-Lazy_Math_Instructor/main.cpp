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

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

constexpr int MAX_N = 80;
//l存放节点左节点编号，r存放右节点编号，op存放当前节点
int l[MAX_N], r[MAX_N], op[MAX_N];
int ncount;

int buildTree(string& s, int beg, int end){
    int u;
    int c1=-1, c2=-1, p=0;
    if(beg+1 == end){
        u = ++ncount;
        l[u]=0;
        r[u]=0;
        op[u]=s[beg];
        return u;
    }
    for(int i=beg; i<end; ++i){
        switch(s[i]){
            case '(':
                ++p;
                break;
            case ')':
                --p;
                break;
            case '+': case '-':
                if(!p)
                    c1=i;
                break;
            case '*':
                if(!p)
                    c2=i;
                break;
        }
    }
    //先处理+、-
    if(c1<0) c1=c2; //没有括号外的+或-
    //且没有括号外的乘除
    if(c1<0){
    	//整个式子被括号包围
        return buildTree(s, beg+1, end-1);
    }
    u = ++ncount;
    l[u] = buildTree(s, beg, c1);
    r[u] = buildTree(s, c1+1, end);
    op[u] = s[c1];
    return u;
}

int Count(int s){
    switch (op[s]){
        case '+':
            return Count(l[s]) + Count(r[s]);
        case '-':
            return Count(l[s]) - Count(r[s]);
        case '*':
            return Count(l[s]) * Count(r[s]);
        default:
            return op[s] >= '0' && op[s] <='9' ? op[s]-48: op[s];
    }
}

int main(){
    int N;
    cin >> N;
    cin.get();
    while(N--){
        string s1;
        string s2;
        std::getline(cin, s1);
        std::getline(cin, s2);
        //清除表达式中的空格符
        int index=0;
        while((index=s1.find(' ', index))!=string::npos){
            s1.erase(index, 1);
        }
        index=0;
        while((index=s2.find(' ', index))!=string::npos){
            s2.erase(index, 1);
        }

        ncount=0;//节点号清零
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        memset(op, 0, sizeof(op));
        buildTree(s1, 0, s1.size());
        int res1 = Count(1);

        ncount=0;//节点号清零
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        memset(op, 0, sizeof(op));
        buildTree(s2, 0, s2.size());
        int res2 = Count(1);

        if(res1==res2)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}
