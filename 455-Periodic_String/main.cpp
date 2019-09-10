#include <iostream>
#include <string>
#include <vector>

class Solution{
public:
	int min_cycle(const std::string& str){
		size_t len = str.size();
		for(int i=1; i<=len; ++i){
			if(len%i == 0){
				bool ok = true;
				for(int j=i; j<len; ++j){
					if(str[j] != str[j%i]){
						ok = false;
						break;
					}
				}
				if(ok) return i;
			}
		}
	}
};

int main(){
	std::string str;
	std::vector<std::string> vec;
	int n;
	Solution s;
	std::cin >> n;
	while(n){
		std::cin >> str;
		vec.push_back(str);
		n--;
	}
	for(int i=0; i<vec.size(); ++i){
		std::cout << s.min_cycle(vec[i])  << std::endl;
		if(i != vec.size()-1)//the last output should not be followed by a blank line.
		    std::cout << '\n';
	}
}