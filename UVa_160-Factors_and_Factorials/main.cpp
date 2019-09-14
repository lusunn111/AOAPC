#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using std::for_each;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::setw;

class Solution{
public:
    vector<int> factorsOfFactorials(int N, const vector<int>& prime_nums){
        vector<int> res(prime_nums.size(), 0);
        for(int i=1; i<=N; ++i){
            int i_copy(i);
            int j(0);
            while(j<prime_nums.size()){
                if(!(i_copy%prime_nums.at(j))){
                    ++res.at(j);
                    i_copy /= prime_nums.at(j);
                }
                if(!(i_copy%prime_nums.at(j))){
                    continue;
                }else{
                    ++j;
                }
            }
        }
        for(auto it = res.end()-1; it != res.begin(); --it){
            if(!(*it)){
                res.erase(it);
            }else{
                break;
            }
        }
        return res;
    }
    bool isPrime(const int num){
        for(int i = 2; i<num; ++i){
            if(!(num%i)){
                return false;
            }
        }
        return true;
    }
};

int main(){
    Solution s;
    int N;
    vector<int> prime_nums;
    for(int i=2; i<100; ++i){
        if(s.isPrime(i)){
            prime_nums.push_back(i);
        }
    }
    while(cin>>N){
        if(0==N){
            break;
        }else{
            vector<int> factors = s.factorsOfFactorials(N, prime_nums);
            cout << setw(3) << N << "! =";
            for(int i=0;i<factors.size();++i){
                cout << setw(3) << factors.at(i);
                //maybe there's no numbers after factors.at(14)...
                if(0==(i+1)%15 && factors.size()>15){
                    cout << "\n" << "      ";
                }
            }
            cout << endl;
        }
    }
}

