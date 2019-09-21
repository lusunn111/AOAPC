#include <cstdio>
#include <vector>
#include <algorithm>

using std::reverse;
using std::vector;

bool binaryConversion(int n, int binary){
    vector<int> n_converted;
    do{
        int remainder = n % binary;
        n_converted.push_back(remainder);
        n /= binary;
    }while(n);
    if(n_converted.at(0)==0 || n_converted.at(n_converted.size()-1)==0)
        return false;
    vector<int> n_converted_reversed(n_converted);
    reverse(n_converted_reversed.begin(), n_converted_reversed.end());
    if(n_converted == n_converted_reversed)
        return true;
    return false;
}

int main(){
    int n;
    while(scanf("%d", &n) != EOF){
        int ans;
        for(int i=n+1; ; ++i){
            int count(0);
            for(int j=2; j<=10; ++j){
                if(binaryConversion(i, j))
                    ++count;
            }
            if(count>1){
                ans = i;
                break;
            }
        }
        printf("%d\n", ans);
    }
}
