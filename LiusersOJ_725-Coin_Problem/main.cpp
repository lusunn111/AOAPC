#include <iostream>
#include <cmath>
#include <climits>

using std::cin;
using std::cout;
using std::endl;

int V[101] = {0};
int max_coins[10001] =  {0};
int min_coins[10001] = {0};
int n;

//打印组成硬币的索引
void print(int* coins, int S){
    for(int i=0; i<n; ++i){
        if(S>=V[i] && coins[S]==coins[S-V[i]]+1){
            cout << i << " ";
            print(coins, S-V[i]);
            break;
        }
    }
}

int main() {
    int S;

    cin >> n >> S;
    for(int i=1; i<=n; ++i){
        cin >> V[i];
    }


    for(int i=1; i<=S; ++i){
        min_coins[i] = INT_MAX;
        max_coins[i] = INT_MIN;
    }
    for(int i=1; i<=S; ++i){
        for(int j=1; j<=n; ++j){
            if(i>=V[j]){
                if(min_coins[i] > min_coins[i-V[j]]+1){
                    min_coins[i] = min_coins[i-V[j]] + 1;
                }
                if(max_coins[i] < max_coins[i-V[j]]+1){
                    max_coins[i] = max_coins[i-V[j]] + 1;
                }
            }
        }
    }

    cout << min_coins[S] << ' ' << max_coins[S];
}
