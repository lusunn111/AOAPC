#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    /**
     * @param nums: An integer array sorted in ascending order
     * @param target: An integer
     * @return: An integer
     */
    int findPosition(vector<int> &nums, int target) {
        //左开右闭搜索
        int i=0, j=nums.size();
        while(i<j){
            int m = (i+j)/2;
            if(nums.at(m)==target){
                return m;
            }else if(nums.at(m)>target){
                j=m;
            }else{
                i=m+1;
            }
        }
        return -1;
    }

    int lowerBound(vector<int>& nums, int target){
        int i=0, j=nums.size();
        while(i<j){
            int m=(i+j)/2;
            //若nums.at(m)==target，继续往前找，若nums.at(m)>target，也是继续往前找
            if(nums.at(m)>=target){
                j = m;
            }else{
                i = m+1;
            }
        }
        return i;
    }

    //upperBound找到的是尾后指针，与STL保持一致
    int upperBound(vector<int>& nums, int target){
        int i=0, j=nums.size();
        while(i<j){
            int m=(i+j)/2;
            if(nums.at(m)<=target){
                i = m+1;
            }else{
                j = m;
            }
        }
        return i;
    }
};

int main(){
    vector<int> nums = {1, 2, 2, 4, 5, 5};
    int target = 5;
    Solution s;
    cout << s.findPosition(nums, target) << endl;
    cout << s.lowerBound(nums, target) << endl;
    cout << s.upperBound(nums, target) << endl;
}
