#include <iostream>
#include <cstdio>
#include <set>

using std::set;

bool valid(int denominator, int numerator){
	set<int> digits;
	for(int i=0; i<5; ++i){
		digits.insert(denominator%10);
		denominator /= 10;
	}
	for(int i=0; i<5; ++i){
		digits.insert(numerator%10);
		numerator /= 10;
	}
	if(digits.size()<10) return false;
	else return true;
}

int main(){
	int N;
	int blocks(0);
	while(scanf("%d", &N)){
		if(!N){
			break;
		}
		if(blocks){
			printf("\n");
		}
		++blocks;
		bool flag(false);
		for(int denominator=1234; denominator<=98765/N; ++denominator){
			int numerator = N * denominator;
			if(valid(denominator, numerator)){
				flag = true;
				printf("%d / ", numerator);
				if(denominator<10000){
					putchar('0');
				}
				printf("%d = %d\n", denominator, N);
			}
		}
		if(!flag){
			printf("There are no solutions for %d.", N);
			printf("\n");
		}
	}
}
