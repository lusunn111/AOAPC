#include <iostream>
#include <vector>
#include <climits>

using std::cin;
using std::cout;
using std::endl;

int max_sum;
int min_index;
int max_index;
std::vector<int> nums;

//暴力，O(n^3)
void maxSum_1(){
    for(int i=0; i<nums.size(); ++i){
        for(int j=i; j<nums.size(); ++j){
            int sum(0);
            for(int k=i; k<=j; ++k){
                sum += nums[k];
            }
            if(sum > max_sum){
                max_sum = sum;
                min_index = i+1;
                max_index = j+1;
            }
        }
    }
}

//连续子序列和等于两个前缀和之差S_i~S_j = S_0~S_j-S_0~S_i，O(n^2)
void maxSum_2(){
    std::vector<int> S;
    int sum_i(0);
    S.push_back(0);
    for(int i=0; i<nums.size(); ++i){
        sum_i+=nums.at(i);
        S.push_back(sum_i);
    }
    int sum_j(0);
    for(int j=0; j<nums.size(); ++j){
        sum_j+=nums.at(j);
        for(int i=0; i<=j; ++i){
            if(sum_j-S.at(i)>max_sum){
                max_sum = sum_j - S.at(i);
                min_index = i+1;
                max_index = j+1;
            }
        }
    }
}

//分治法，分治法接口稍为复杂,[l,r)的最大和
int maxSum_3(int l, int r, int& min_ind, int& max_ind){
    if(l==r-1){
        min_ind = l;
        max_ind = l;
        return nums.at(l);
    }
    int m = (l+r)/2;

    int min_ind_L, max_ind_L;
    int sum_L = maxSum_3(l, m, min_ind_L, max_ind_L);
    int min_ind_R, max_ind_R;
    int sum_R = maxSum_3(m, r, min_ind_R, max_ind_R);
    if(sum_L>=sum_R){
        max_sum = sum_L;
        min_ind = min_ind_L;
        max_ind = max_ind_L;
    }else{
        max_sum = sum_R;
        min_ind = min_ind_R;
        max_ind = max_ind_R;
    }

    //横跨中间的最大和
    int L = nums.at(m-1);
    int s_L(0);
    int ind_L;
    for(int i=m-1; i>=0; --i){
        s_L += nums.at(i);
        if(s_L>=L){
            L = s_L;
            ind_L = i;
        }
    }
    int R = nums.at(m);
    int s_R(0);
    int ind_R;
    for(int i=m; i<nums.size(); ++i){
        s_R += nums.at(i);
        if(s_R>R){
            R = s_R;
            ind_R = i;
        }
    }
    if(L+R>max_sum){
        max_sum = L+R;
        min_ind = ind_L;
        max_ind = ind_R;
    }
    return max_sum;
}

//动态规划,O(n)
void maxSum_4(){
    int sum(0);
    int min_ind = 1;
    for(int i=0;i<nums.size();++i){
        if(sum>=0){
            sum += nums.at(i);
        }else{
            sum = nums.at(i);
            min_ind = i+1;
        }
        if(sum > max_sum){
            max_sum = sum;
            min_index = min_ind;
            max_index = i+1;
        }
    }
}

//维护一个到nums[0]~nums[n]的最小连续和, O(n)
void maxSum_5(){
    int min_sum(0);
    int min_ind = 1;
    int sum(0);
    for(int i=0; i<nums.size(); ++i){
        if(sum < min_sum){
            min_sum = sum;
            min_ind = i+1;
        }
        sum += nums.at(i);
        if(sum-min_sum > max_sum){
            max_sum = sum-min_sum;
            min_index = min_ind;
            max_index = i+1;
        }
    }
}

int main(){
    int cases;
    int cnt(0);
    cin >> cases;
    while(++cnt <= cases){
        //清除上次的遗留
        nums.clear();
        max_sum = INT_MIN;
        min_index = 0;
        max_index = 0;

        int N;
        cin >> N;
        for(int i=0; i<N; ++i){
            int temp;
            cin >> temp;
            nums.push_back(temp);
        }
        maxSum_4();
        //max_sum = maxSum_3(0, nums.size()-1, min_index, max_index);
        cout << "Case " << cnt << ":\n" << max_sum << ' ' << min_index << ' ' << max_index << endl;
        if(cnt != cases){
            cout << endl;
        }
    }
}
