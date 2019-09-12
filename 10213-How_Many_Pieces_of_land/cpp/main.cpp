#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Solution{
public:
	unsigned long long maxLands(int N){
		unsigned long long V(0), E(0);
		unsigned long long sumV(0), sumE(0);
		for(int i=0; i<=N-2; ++i){
			sumV += i*(N-2-i);
			sumE += i*(N-2-i)+1;
		}
		V = N + N*sumV/4;
		E = N + N*sumE/2;
		//欧拉公式 V-E+F=2，V（点）E（边）F（面）
		return 1+E-V;
	}
};

int main(){
	int N(0);
	int S(0);
	cin >> S;
	Solution s;
	while(S){
		cin >> N;
		cout << s.maxLands(N) << endl;
		--S;
	}
}
