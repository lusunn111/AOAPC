#include <iostream>
#include <string>

int main(){
	char c;
	bool q = true;
	while((c=std::cin.get()) != EOF){
		if(c=='"'){
			std::string str = q ? "``" : "''";
			std::cout << str;
			q = !q;
		}
		else std::cout.put(c);
	}
}
