#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>

using std::vector;
using std::multimap;
using std::make_pair;
using std::sort;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main(){
	multimap<string, string> dictionary;
	string word;
	//form the dictionary, whose key is sorted word.
	while(cin >> word){
		if(word == "XXXXXX"){
			break;
		}
		string word_sorted = word;
		sort(word_sorted.begin(), word_sorted.end());
		dictionary.insert(make_pair(word_sorted, word));
	}
	//find sorted word in the keys of the dictionary
	vector<string> words;
	while(cin >> word){
		if(word == "XXXXXX"){
			break;
		}
		sort(word.begin(), word.end());
		words.push_back(word);
	}
	for(string w : words){
		/* C++14
		auto beg = dictionary.lower_bound(word);
		auto end = dictionary.upper_bound(word);
		if(beg == end){
			cout << "NOT A VALID WORD" << "\n******" << endl;
		}else{
			for(auto i = beg; i != end; ++i){
				cout << i->second << '\n';
			}
			cout << "******" << endl;
		}
		*/
		//C++11
		auto beg = dictionary.find(w);
		int count = dictionary.count(w);
		if(count == 0){
			cout << "NOT A VALID WORD" << "\n******" << endl;
		}
		else{
			vector<string> res;
			for(int i = 0; i != count; ++i, ++beg){
				res.push_back(beg->second);
			}
			sort(res.begin(), res.end());
			for(auto s : res){
				cout << s << '\n';
			}
			cout << "******" << endl;
		}
	}
}
