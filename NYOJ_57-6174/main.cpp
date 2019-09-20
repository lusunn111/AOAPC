#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using std::stoi;
using std::to_string;
using std::sort;
using std::reverse;
using std::string;
using std::stringstream;
using std::cout;
using std::cin;
using std::endl;

class Solution{
public:
	int cycleTimes(int num){
		int count(1);
		int num_minus = cycle(num);
		if(num==num_minus){
		    return 0;
		}
		while(num!=num_minus){
		    num = num_minus;
			num_minus = cycle(num_minus);
		    ++count;
		}
		return count;
	}
	int cycle(int num){
		string str = to_string(num);
		string str_min = str;
		sort(str_min.begin(), str_min.end());
		string str_max = str_min;
		reverse(str_max.begin(), str_max.end());
		int min = stoi(str_min);
		int max = stoi(str_max);

		return (max-min);
	}
};

int main(){
	int n;
	cin >> n;
	while(n){
		int num;
		Solution s;
		cin >> num;
		cout << s.cycleTimes(num) << endl;
		--n;
	}
}
