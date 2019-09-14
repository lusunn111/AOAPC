#include <iostream>
#include <string>

std::string str = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

int main(){
	int i;
	char c;
	while((c=std::cin.get()) != EOF){
		for(i=1; str[i]&&c!=str[i]; ++i);
		if(str[i]) std::cout.put(str[i-1]);
		else std::cout.put(c);
	}
}