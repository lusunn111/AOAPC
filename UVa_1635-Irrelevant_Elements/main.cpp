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

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

int n, m;
map<int, int> fac_m;
map<int, int> fac_Cni;

//获取质因子不需要先算素数
void getFactor(){
    for(int i=2; i*i<=m; ++i){
        while(m%i==0){
            ++fac_m[i];
            m /= i;
        }
    }
    if(m!=1){
        ++fac_m[m];
    }
}

bool check(int i){
    int numerator = n-1-i+1;
    int denominator = i;
    for(map<int, int>::iterator it=fac_m.begin(); it!=fac_m.end(); ++it){
        //只需要处理fac_m的素因子，其他的素因子不用处理，与最终结果无关
        while(numerator%(it->first)==0){
            fac_Cni[it->first] += 1;
            numerator /= it->first;
        }
        while(denominator%(it->first)==0){
            fac_Cni[it->first] -= 1;
            denominator /= it->first;
        }
    }

    for(map<int, int>::iterator it=fac_m.begin(); it!=fac_m.end(); ++it){
        if(it->second>fac_Cni[it->first]) //与此项有关
            return false;
    }

    return true;
}

int main() {
    while(cin>>n>>m){
        fac_m.clear();
        fac_Cni.clear();
        getFactor();
        vector<int> res;
        for(int i=1; i<n-1; ++i){
            if(check(i))
                res.emplace_back(i+1);
        }//首尾项都为1,跳过
        if(res.size()==0)
            cout << 0 << '\n' << endl;
        else{
            cout << res.size() << endl;
            for(int i=0; i<res.size()-1; ++i)
                cout << res[i] << " ";
            cout << res[res.size()-1] << endl;
        }

    }
}
