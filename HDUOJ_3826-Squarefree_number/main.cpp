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
#include <unordered_set>

using std::unordered_set;
using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

vector<int> prime;
vector<int> vis(1000010, 0);

//根据唯一分解定理我们可以知道，任何整数都可以分解成多个质数的乘积。本题也就成了求一个数 n 是否是 p*p 的倍数，
//其中 p 是质数（非质数的平方可以分解为质数的平方）。由于 n 的范围，所以 p 最大是 10e9，这个范围太大，我们是无法通过筛选法打表的。

//将n分解，如果有幂为2的，结果出来了，如果没有，那么再看
//如果分解的结果都是10e6范围内的质数，那么结果出来了，如果有大于10e6的数，那么它不能分解为10e6范围内的质数之积
//它的因子一定比10e6大（因为它不能分解为10e6以内的质数的积），且不超过两个，因为10e18，所以它要么是两个大于10e6的素因子的乘积，要么是一个大于10e6的素因子的平方

void genPrime(){
    for(long long i=2; i<1000000; ++i){
        if(!vis[i]) prime.emplace_back(i);
        for(long long j=i*i; j<=1000000; j+=i){
            if(!vis[j]){
                vis[j] = 1;
            }
        }
    }
}

int main() {
    int T;
    int cnt(0);
    genPrime();
    cin >> T;
    while(cnt++!=T){
        long long N;
        cin >> N;

        bool flag=true;

        for(int i=0; i<prime.size(); ++i){
            if(prime[i] > N) break;
            int num = 0;
            while(N%prime[i]==0){
                N /= prime[i];
                ++num;
            }
            if(num>=2){
                flag = false;
                break;
            }
        }

        if(N!=1){
            auto x = static_cast<long long>(std::sqrt(static_cast<double>(N)));
            if(x*x==N){
                flag = false;
            }
        }

        cout << "Case " << cnt << ": ";
        if(flag) cout << "Yes";
        else cout << "No";
        cout << endl;
    }
}
