#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

class Solution {
public:
    /**
     * @param A: an integer array
     * @return: nothing
     */
    void sortIntegers(vector<int> &A) {
        vector<int> T(A.size(), 0);
        mergeSort(A, 0, A.size(), T);
    }
    
    void mergeSort(vector<int>& A, int l, int r, vector<int>& T){
    	if(r-l>1){
    		int m = (l+r)/2;
    		//sort [l,m)
    		mergeSort(A, l, m, T);
    		//sort [m, r)
    		mergeSort(A, m, r, T);
    		int p = l, q = m, i = l;
    		//merge [l,m) [m,r)
    		//任意一个非空
    		while(p<m || q<r){
    			//一个空了或者都没空
    			if(q>=r || p<m && A.at(p)<A.at(q)){
    				T.at(i++) = A.at(p++);
    			}else{
    				T.at(i++) = A.at(q++);
    			}
    		}
    		for(int k=l; k<r; k++){
    			A.at(k) = T.at(k);
    		}
    	}
    }
};

int main(){
	Solution s;
	vector<int> A = {3,4,8,7};
	s.sortIntegers(A);
	for(int i: A){
		cout << i << ' ';
	}
	cout << endl;
}
