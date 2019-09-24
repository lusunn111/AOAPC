#include <cstdio>
#include <vector>
#include <cmath>

using std::vector;
using std::floor;

int main(){
	int k;
	while(scanf("%d", &k) != EOF){
		int count(0);
		vector<int> xs;
		vector<int> ys;
		for(double y=k+1; y<=2*k; ++y){
			double x = k*y/(y-k);
			if(x-floor(x) < 1e-6){
				++count;
				xs.push_back(static_cast<int>(x));
				ys.push_back(static_cast<int>(y));
			}
		}
		printf("%d\n", count);
		for(int i=0; i<count; ++i){
			printf("1/%d = 1/%d + 1/%d\n", k, xs.at(i), ys.at(i));
		}
	}
}
