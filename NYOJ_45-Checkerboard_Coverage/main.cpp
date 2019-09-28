#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int lNeeded(int k){
	if(k==1){
		return 1;
	}else{
		return 4 * lNeeded(k-1) + 1;
	}
}

int main(){
	int m;
	cin >> m;
	while(m--){
		int k;
		cin >> k;
		cout << lNeeded(k) << endl;
	}
}
