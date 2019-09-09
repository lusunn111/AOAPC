#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(){
	int a, b;
	while(cin >> a >> b){
		if(!a && !b) break;
		int carries = 0;
		int carry = 0;
		while(a||b){
			carry = (a%10 + b%10 + carry) / 10;
			carries += carry;
			a /= 10;
			b /= 10;
		}
		if(!carries){
			cout << "No carry operation." << endl;
		}
		else if(carries==1){
			cout << "1 carry operation." << endl;
		}
		else{
			cout << carries << " carry operations." << endl;
		}
	}
}
