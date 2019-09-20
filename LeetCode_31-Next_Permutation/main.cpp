#include <iostream>
#include <algorithm>
#include <vector>

using std::sort;
using std::vector;
using std::next_permutation;
using std::cout;
using std::cin;
using std::endl;

class Solution{
public:
    /* STL
    void nextPermutation(vector<int>& nums) {
        next_permutation(nums.begin(), nums.end());
    }
    */
    //从后向前找非降序
    void nextPermutation(vector<int>& nums){
        bool flag(false);
        for(int i=nums.size()-1; i>=0; --i){
            for(int j=i-1; j>=0; --j){
                if(nums.at(j) < nums.at(i)){
                    nums.at(i) = nums.at(i) ^ nums.at(j);
                    nums.at(j) = nums.at(i) ^ nums.at(j);
                    nums.at(i) = nums.at(i) ^ nums.at(j);
                    sort(nums.begin()+j+1, nums.end());
                    flag = true;
                    break;
                }
            }
            if(flag) break;
        }
        if(!flag) sort(nums.begin(), nums.end());
    }
};

int main(){
    vector<int> nums{1, 5, 1};
    Solution s;
    s.nextPermutation(nums);
    for(int i: nums){
        cout << i << ' ';
    }
    cout << endl;
}
