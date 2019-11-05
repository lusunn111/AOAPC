#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

int Volume[1010];
int Value[1010];
int dp[1010][1010] = {0};
//int dp[1010];

int main() {
    int T;
    cin >> T;
    while(T--){
        int N, V;
        cin >> N >> V;
        for(int i=1; i<=N; ++i){
            cin >> Value[i];
        }
        for(int i=1; i<=N; ++i){
            cin >> Volume[i];
        }
        memset(dp,0,sizeof(dp)); //非常重要！！！

        //逆序，dp[i][j]表示用j的背包装i之后的物品最多装多少价值
        for(int i=N; i>=1; --i){
            for(int j=0; j<=V; ++j){
                if(j>=Volume[i])
                    dp[i][j] = dp[i+1][j]>dp[i+1][j-Volume[i]]+Value[i] ? dp[i+1][j] : dp[i+1][j-Volume[i]]+Value[i];
                else {
                    dp[i][j] = dp[i + 1][j];
                }
            }
        }
        cout << dp[1][V] << endl;


        //法2：顺序，dp[i][j]表示用j的背包装i之前的物品最多装多少价值
//        for(int i=1; i<=N; ++i){
//            for(int j=0; j<=V; ++j){
//                if(j>=Volume[i])
//                    dp[i][j] = dp[i-1][j]>dp[i-1][j-Volume[i]]+Value[i] ? dp[i-1][j] : dp[i-1][j-Volume[i]]+Value[i];
//                else{
//                    dp[i][j] = dp[i-1][j];
//                }
//            }
//        }
//        cout << dp[N][V] << endl;

        //法3：精简
//        for(int i=1;i<=N;i++) {
//            for (int j = V; j >= Volume[i]; j--) {
//                dp[j] = max(dp[j], dp[j - Volume[i]] + Value[i]);
//            }
//        }
//        cout << dp[V] << endl;
    }
}
