#include <cstdio>
#include <vector>
#include <iostream>

using std::cin;
using std::vector;

long long maxProduct(vector<int>& S){
    long long max_product(0);
    for(int i=0; i<S.size(); ++i){
        long long product(1);
        for(int j=i; j<S.size(); ++j){
            product *= S.at(j);
            max_product = max_product>product ? max_product : product;
        }
    }
    return max_product;
}

int main(){
    int N;
    int M(1);
    //注意此题的退出条件是EOF
    while(scanf("%d", &N) != EOF){
        vector<int> S(N, 0);
        for(int i(0); i<N; ++i){
            cin >> S.at(i);
        }
        long long ans = maxProduct(S);
        printf("Case #%d: The maximum product is %lld.\n\n", M, ans);
        ++M;
    }
}
