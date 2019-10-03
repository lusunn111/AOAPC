#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

//TLE
//nums不能动
int kthMin(vector<int>& nums, int i, int j, int k){
    vector<int> nums_sec(j-i+1);
    std::copy(nums.begin()+i-1, nums.begin()+j, nums_sec.begin());
    //挖坑填数版快速排序
    int l=0, r=nums_sec.size()-1;
    int x = nums_sec.at(0);
    while(l<r){
        while(l<r && nums_sec.at(r)>x){
            --r;
        }
        if(l<r){
            nums_sec.at(l) = nums_sec.at(r);
            ++l;
        }
        //l<r不能少，因为之前的操作可能导致l已经等于r了，下面再++l就会导致l，r错位，x放错位置。
        while(l<r && nums_sec.at(l)<x){
            ++l;
        }
        if(l<r){
            nums_sec.at(r) = nums_sec.at(l);
            --r;
        }
    }
    nums_sec.at(l) = x;
    if(l+1==k){
        return nums_sec.at(l);
    }else if(l+1<k){
        return kthMin(nums_sec, l+2, nums_sec.size(), k-l-1);
    }else{
        return kthMin(nums_sec, 1, l+1, k);
    }
}

int main(){
    int n, m, i, j, k;
    cin >> n >> m;
    vector<int> nums(n);
    for(int i=0; i<n; ++i){
        cin >> nums.at(i);
    }
    while(m--){
        //这个i，j是[i,j]，且是现实意义的i，j，没有第0的
        cin >> i >> j >> k;
        int res = kthMin(nums, i, j, k);
        cout << res << endl;
    }
}
