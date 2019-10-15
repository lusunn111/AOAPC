#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

//cnt一定要是引用类型，否则退回上一层cnt会变化，每一层都有一个拷贝的cnt
bool searchKthHard(vector<char>& hard, int cur, int& cnt, int n, int L){
    //cur是当前字符串的长度
    if(cnt==n){
    	//已经找到第cnt个解，返回true
        return true;
    }
    for(char c='A'; c<'A'+L; ++c){
        hard.push_back(c);
        int ok = true;
        for(int j=1; j*2<cur+1; ++j){
            int equal = true;
            //从后往前检查，因为cur前的子串已经检查过了，不用再次检查，j为待测是否重复字符串的长度
            for(int k=0; k<j; ++k){
                if(hard.at(cur-1-k) != hard.at(cur-1-j-k)){
                    equal = false;
                    break;
                }
            }
            if(equal==true){
                ok=false;
                break;
            }
        }
        if(ok){
            ++cnt;
            //已经找到第cnt个解，不断返回true
            if(searchKthHard(hard, cur+1, cnt, n, L))
                return true;
        }else{
        	//ok为false，即此层添加的字符不对，删除，继续添加下一个字符
            hard.erase(hard.end()-1);
        }
    }
    //本层无论添什么字符都不对，返回上一级之前一定要erase
    hard.erase(hard.end()-1);
    return false;
}

int main(){
    int n, L;
    while(cin >> n >> L){
        if(!n && !L) break;
        vector<char> hard;
        int cnt = 0;
        bool flag = searchKthHard(hard, 1, cnt, n, L);
        int num_chars = 0;
        for(int i=0; i<hard.size(); ++i){
            ++num_chars;
            cout << hard.at(i);
            //最后一个字符后不输任何符号，每4个字符输出' '，每64个字符输出'\n'
            if(num_chars==hard.size()) {
                break;
            }else if(0==num_chars%64){
                cout << '\n';
            }else if(0==num_chars%4){
                cout << ' ';
            }
        }
        cout << '\n' << hard.size();
        cout << endl;
    }
}
