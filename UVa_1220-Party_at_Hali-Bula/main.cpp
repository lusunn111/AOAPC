#include <iostream>
#include <cstring>
#include <cfloat>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <map>
#include <jmorecfg.h>
#include <numeric>

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

int n;
constexpr int MAX_N = 205;
map<string, int> dict;
int cnt;
vector<int> sons[MAX_N];
int d[MAX_N][2];
int f[MAX_N][2];

int id(string s){
    if(dict.count(s)) return dict[s];
    else{
        ++cnt;
        dict.emplace(s, cnt);
        return cnt;
    }
}

//f如何从底层向上层传比较难理解
int dp(int i){
    if(d[i][0]!=0 || d[i][1]!=0) return max(d[i][0], d[i][1]);
    if(sons[i].empty()){
        d[i][0] = 0;
        d[i][1] = 1;
    }else{
        for(int j: sons[i]){
            d[i][0] += dp(j);
            if(d[j][0]==d[j][1]){
                f[i][0] = 1;
            }
            if(d[j][0]>d[j][1] && f[j][0]){
                f[i][0] = 1;
            }
            if(d[j][0]<d[j][1] && f[j][1]){
                f[i][0] = 1;
            }
        }
        for(int j: sons[i]){
            if(sons[j].empty()) continue;
            for(int k: sons[j]){
                d[i][1] += dp(k);
                if(d[k][0]==d[k][1]){
                    f[i][1] = 1;
                }
            }
        }
        d[i][1] += 1;
    }

    return max(d[i][0], d[i][1]);
}

int main() {
    int a(0);
    while(cin>>n && n!=0){
        ++a;
        dict.clear();
        for(int i=0; i<MAX_N; ++i){
            sons[i].clear();
        }
        memset(d, 0, sizeof(d));
        memset(f, 0, sizeof(f));
        cnt = -1;
        string big_boss;
        cin >> big_boss;
        id(big_boss);
        string employee, boss;
        for(int i=0; i<n-1; ++i){
            cin >> employee >> boss;
            sons[id(boss)].push_back(id(employee));
        }

        dp(0);
        if(d[0][0]>d[0][1]){
            cout << d[0][0] << ' ';
            if(f[0][0]){
                cout << "No";
            }else{
                cout << "Yes";
            }
            cout << endl;
        }else if(d[0][0]<d[0][1]) {
            cout << d[0][1] << ' ';
            if (f[0][1]) {
                cout << "No";
            } else {
                cout << "Yes";
            }
            cout << endl;
        }else{
            cout << d[0][0] << ' ' << "No" << endl;
        }
    }

}

