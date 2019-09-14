#include <iostream>
#include <vector>
#include <algorithm>

using std::min;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

/*
class Solution{
public:
	vector<int> factorial(const int num){
		vector<int> res{1};
		int m(2);
		//three loops, TLE
		while(m<=num){
			vector<int> fac1;
			int m_copy = m;
			while(m_copy){
				fac1.push_back(m_copy%10);
				m_copy /= 10;
			}
			vector<int> fac2 = res;
			res.clear();
			int len1 = fac1.size();
			int len2 = fac2.size();
            int carry(0);
            //merge this two loops
			for(int i=0;i<len1+len2-1;++i){
			    int sum(0);
			    for(int j=0;j<len1;++j){
			        if(i-j>=0&&i-j<len2){
                        sum += fac1[j] * fac2[i-j];
                    }
			    }
			    sum += carry;
                res.push_back(sum%10);
			    carry = sum/10;
			}
			if(carry){
			    res.push_back(carry);
			}
			++m;
		}
        return res;
	}
};
*/

class Solution{
public:
    vector<int> factorial(int num){
        vector<int> res{1};
        int m(2);
        while(m<=num){
            int carry(0);
            vector<int> fac = res;
            res.clear();
            for(int i=0; i<fac.size(); ++i){
                res.push_back((fac[i]*m+carry)%10);
                carry = (fac[i]*m+carry) / 10;
            }
            while(carry>=10){
                res.push_back(carry%10);
                carry /= 10;
            }
            if(carry){
                res.push_back(carry);
            }
            ++m;
        }
        return res;
    }
};

int main(){
    int num;
    Solution s;
    while(cin >> num){
        vector<int> res = s.factorial(num);
        cout << num << "!" << endl;
        for(auto it=res.rbegin();it!=res.rend();++it){
            cout << *it;
        }
        cout << endl;
    }
}
