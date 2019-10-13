#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

long long gcd(long long num_1, long long num_2){
    if(num_1<num_2){
        std::swap(num_1, num_2);
    }
    return num_2==0 ? num_1 : gcd(num_2, num_1%num_2);
}

int getFirst(long long a, long long b){
    return static_cast<int>(b/a+1);
}

//在depth相同的情况下还要保证最大分母最小
bool check(vector<long long>& res, vector<long long>& denominators){
    for(int i=res.size()-1;i>=0; --i){
        if(res.at(i)!=denominators.at(i))
            return res.at(i)==0 || res.at(i)>denominators.at(i);
    }
}

bool dfs(vector<long long>& res, vector<long long>& denominators, vector<int>& vis, vector<int>& restricted, long long a, long long b, int depth, int cur, int min){
    //每层都有一个flag来标记此层有没有找完并找到最优解
    bool flag(false);
    if(cur==depth-1){
        if(b%a) return false; //a必须为1
        else{
            if(std::count(vis.begin(), vis.end(), b) || std::count(restricted.begin(), restricted.end(), b)){
                return false;
            }else{
                denominators.at(cur) = b;
                if(check(res, denominators))
                    res = denominators;
                return true;
            }
        }
    }

    for(int i=std::max(min, getFirst(a, b)); ; ++i){
        //只有当用当前i放满还比a/b小的情况才能退出，要找遍某种深度的所有情况来找到此深度的最优解，而不是找到一个解就退出
        if((depth-cur)*b<=a*i) break;
        if(std::count(vis.begin(), vis.end(), i) || std::count(restricted.begin(), restricted.end(), i)) continue;
        denominators.at(cur)=i;
        long long n = a*i-b;
        long long m = b*i;
        long long g = gcd(n, m);
        if(dfs(res, denominators, vis, restricted, n/g, m/g, depth, cur+1, i+1)){
            //虽然flag设为true，但并不退出循环，因为接下来的循环可能找到更优解
            flag = true;
        }
    }
    //break之后return
    return flag;
}

int main(){
    int cases;
    cin >> cases;
    int ca(0);
    while(ca<cases){
        ++ca;
        //load input
        int a, b, k;
        cin >> a >> b >> k;
        vector<int> restricted(k, 0);
        for(int i=0; i<k; ++i){
            cin >> restricted.at(i);
        }

        int depth(1);
        while(depth){
            //虽然最后的结果int就可以存，但中间搜索过程会出现int溢出
            vector<long long> denominators(depth, 0);
            vector<long long> res(depth, 0);
            vector<int> vis;
            if(dfs(res, denominators, vis, restricted, a, b, depth, 0, getFirst(a, b))){
                cout << "Case " << ca << ": " << a << "/" << b << "=";
                for(int i=0; i<res.size();++i){
                    if(i==res.size()-1){
                        cout << "1/" << res.at(i) << "\n";
                    }else{
                        cout << "1/" << res.at(i) << "+";
                    }
                }
                break;
            }
            ++depth;
        }
    }
}
