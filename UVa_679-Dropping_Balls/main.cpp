#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Solution{
public:
	int numOfIthBall(int D, int I){
		int k(1);
		for(int i(0); i<D-1; ++i){
			//奇数走左子树，偶数走右子树
			if(I%2){
				k=2*k;
				I=I/2+1;
			}else{
				k=2*k+1;
				I=I/2;
			}
		}
		return k;
	}
};

int main(){
	int l;
	cin >> l;
	Solution s;
	while(l--){
		int D, I;
		cin >> D >> I;
		if(D==-1) break;
		cout << s.numOfIthBall(D, I) << endl;
	}
}
