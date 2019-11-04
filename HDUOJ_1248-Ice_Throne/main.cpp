#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <climits>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int V[3] = {150, 200, 350};
int dp[10001] = {0};

int main() {
    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        for(int i=1; i<=N; ++i){
            for(int j=0; j<3; ++j){
                if(i>=V[j]){
                    if(dp[i-V[j]]+V[j]>dp[i]){
                        dp[i] = dp[i-V[j]]+V[j];
                    }
                }
            }
        }
        cout << N-dp[N] << endl;
    }
}
