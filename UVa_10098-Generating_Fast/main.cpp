#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::sort;
using std::unique;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

vector<string> permutation(string str){
    vector<string> res;
    for(int i=0; i<str.size(); ++i){
        //摒弃重复元素 法1,较为省时
        if(!i || str.at(i)!=str.at(i-1)) {
            string permu;
            permu.push_back(str.at(i));
            //不能破坏str
            string str_copy = str;
            vector<string> ans = permutation(str_copy.erase(i, 1));
            if (ans.empty()) {
                res.push_back(permu);
            } else {
                for (string s: ans) {
                    res.push_back(permu + s);
                }
            }
        }
    }
    return res;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        string str;
        cin >> str;
        sort(str.begin(), str.end());
        vector<string> res = permutation(str);
        /*
        //删除重复元素 法2：较耗时
        sort(res.begin(), res.end());
        auto last = unique(res.begin(), res.end());
        res.erase(last, res.end());
        */
         for(string s: res){
            cout << s << endl;
        }
        cout << endl;
    }
}
