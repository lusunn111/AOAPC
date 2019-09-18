#include <iostream>
#include <string>
#include <algorithm>

using std::find;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Solution{
public:
    //n记录的是中间结点要插入的位置
	void reconstruct(int n, string preord, string inord, string& postord){
		//中间结点
		if(preord.size()==0) return;
		char node = preord[0];
		//区别左子树与右子树的位置
		auto iter = find(inord.begin(), inord.end(), node);
		int l_tree_len = iter - inord.begin();
		int r_tree_len = preord.size() - l_tree_len - 1;
		reconstruct(n-1, preord.substr(l_tree_len+1, r_tree_len), inord.substr(l_tree_len+1, r_tree_len), postord);
		reconstruct(n-1-r_tree_len, preord.substr(1, l_tree_len), inord.substr(0, l_tree_len), postord);
		postord[n-1] = node;
	}
};

int main(){
	string preord, inord;
	Solution s;
	while(cin >> preord >> inord){
		string postord(preord.size(), ' ');
		s.reconstruct(preord.size(), preord, inord, postord);
		cout << postord << endl;
	}
}

