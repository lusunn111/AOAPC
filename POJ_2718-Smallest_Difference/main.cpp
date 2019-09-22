#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdio>

using std::next_permutation;
using std::reverse;
using std::count;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

//增量构造法生成子集
vector<vector<int> > subsetGenerating_1(vector<int> digits){
    vector<vector<int> > subsets;
    if(digits.size()==0) return subsets;
    vector<int> subset;
    subset.push_back(digits.at(0));
    subsets.push_back(subset);
    vector<int> digits_copy(digits.begin()+1, digits.end());
    vector<vector<int> > ans = subsetGenerating_1(digits_copy);
    for(int i=0; i<ans.size(); ++i){
        subsets.push_back(ans.at(i));
        ans.at(i).push_back(digits.at(0));
        subsets.push_back(ans.at(i));
    }
    return subsets;
}

class Solution{
public:
    vector<vector<int> > subsetGenerating_2(vector<int> digits){
        vector<int> mask(digits.size(), 0);
        //vector<vector<int> > masks = maskGenerating_1(mask, 0);
        vector<vector<int> > masks = maskGenerating_2(digits.size());
        vector<vector<int> > subsets;
        for(int i=0; i<masks.size(); ++i){
            if(masks.at(i)==mask) continue;
            vector<int> subset;
            for(int j=0; j<masks.at(i).size(); ++j){
                if(masks.at(i).at(j)){
                    subset.push_back(digits.at(j));
                }
            }
            subsets.push_back(subset);
        }
        return subsets;
    }
    //二进制法生成子集，二进制法和位向量法本质上是一样的，都是创造了一个位掩膜
    vector<vector<int> > maskGenerating_2(int n){
        vector<vector<int> > masks;
        for(int i=0; i<(1<<n);++i){
            vector<int> mask;
            int i_copy(i);
            for(int j=0; j<n; ++j){
                mask.push_back(i_copy%2);
                i_copy/=2;
            }
            masks.push_back(mask);
        }
        return masks;
    }
    //位向量法生成子集
    vector<vector<int> > maskGenerating_1(vector<int> mask, int cur){
        vector<vector<int> > res;
        if(cur==mask.size()){
            res.push_back(mask);
            return res;
        }
        vector<vector<int> > masks;
        vector<int> mask_0 = mask;
        vector<int> mask_1 = mask;
        mask_1.at(cur) = 1;
        vector<vector<int> > ans1 = maskGenerating_1(mask_0, cur+1);
        vector<vector<int> > ans2 = maskGenerating_1(mask_1, cur+1);
        for(int i=0; i<ans1.size(); ++i){
            res.push_back(ans1.at(i));
        }
        for(int i=0; i<ans2.size(); ++i){
            res.push_back(ans2.at(i));
        }
        return res;
    }
};


int formNum(vector<int>& s){
    int num(0);
    for(int i=0; i<s.size(); ++i){
        num *= 10;
        num += s.at(i);
    }
    return num;
}

vector<vector<int> > permutation(vector<int> v){
    vector<vector<int> > res;
    for(int i=0; i<v.size(); ++i){
        //摒弃重复元素 法1,较为省时
        if(!i || v.at(i)!=v.at(i-1)) {
            vector<int> permu;
            permu.push_back(v.at(i));
            //不能破坏str
            vector<int> v_copy = v;
            v_copy.erase(v_copy.begin()+i);
            vector<vector<int> > ans = permutation(v_copy);
            if (ans.empty()) {
                res.push_back(permu);
            } else {
                for (int i=0; i<ans.size(); ++i) {
                    vector<int> permu_copy = permu;
                    for(int j=0; j<ans.at(i).size(); ++j){
                        permu_copy.push_back(ans.at(i).at(j));
                    }
                    res.push_back(permu_copy);
                }
            }
        }
    }
    return res;
}

//传入的s， digits都是顺序的
int diff(vector<int> s, vector<int> digits){
    vector<int> s_completed;
    for(int i=0; i<digits.size(); ++i){
        if(count(s.begin(), s.end(), digits.at(i))) continue;
        s_completed.push_back(digits.at(i));
    }
    vector<vector<int> > s_permu = permutation(s);
    vector<vector<int> > s_completed_permu = permutation(s_completed);
    int min_diff = INT_MAX;
    for(int i=0; i<s_permu.size(); ++i){
        if(s_permu.at(i).at(0)==0) continue;
        int num1 = formNum(s_permu.at(i));
        for(int j=0; j<s_completed_permu.size(); ++j){
            if(s_completed_permu.at(j).at(0)==0) continue;
            int num2 = formNum(s_completed_permu.at(j));
            min_diff = abs(num1-num2)<min_diff ? abs(num1-num2) : min_diff;
        }
    }
    return min_diff;
}

/*
//POJ2718如果采用这种方法是会TLE的，为什么？？
//1、将整个S，分为两个subset，再做permutation，再对S1,S2遍历来求差。遍历次数：C_n^{n/2}*A_{n/2}^{n/2}*A_{n/2}^{n/2} == A_n^n
//2、直接对整个S做permutation，再通过前半与后半部分的做差得到结果。遍历次数：A_n^n
//两种方法的遍历次数一样啊。
//这边写这么一个方法是因为为了演示刘汝佳书上7.3节的三种子集生成方法，实在没有找到其他与7.3节内容相似的题目。
int main(){
    int n;
    cin>>n;
    cin.get();
    while(n--){
        vector<int> digits;
        char digit;
        //此题输入的digit是顺序的，即digits顺序
        while(digit=cin.get()){
            if(digit==' ') continue;
            if(digit=='\n') break;
            digits.push_back(digit-48);
        }
        if(digits.size()==1){
            cout << digits.at(0) << endl;
        }else{
            //得到的每一个subset都是顺序的
            vector<vector<int> > subsets = subsetGenerating_1(digits);
            int min_diff = INT_MAX;
            for(int i=0; i<subsets.size(); ++i){
                if(subsets.at(i).size()==digits.size()/2){
                    reverse(subsets.at(i).begin(), subsets.at(i).end());
                    int difference = diff(subsets.at(i), digits);
                    min_diff = difference<min_diff ? difference : min_diff;
                }
            }
            cout << min_diff << endl;
        }
    }
}
*/

int cnt;
int a[15];

void solve()
{
    while (a[0]==0)
        next_permutation(a,a+cnt);
    int ans = 9999999;
    int mid = cnt / 2;
    do {
        if (a[mid]) {
            int ma = a[0], mb = a[mid];
            for (int i = 1; i < mid;i++)
                ma = ma * 10 + a[i];
            for (int i = mid + 1; i < cnt;i++)
                mb = mb * 10 + a[i];
            if (ans>abs(ma-mb))
                ans = abs(ma - mb);
        }
    } while (next_permutation(a, a + cnt));
    printf("%d\n", ans);
}

int main(){
    int n;
    scanf("%d",&n);
    getchar();
    while (n--) {
        char ch;
        cnt = 0;
        while ((ch=getchar())!='\n') {
            if (ch!=' ')
                a[cnt++] = ch-'0';
        }
        if (cnt==1)
            printf("%d\n", a[0]);
        else if (cnt==2)
            printf("%d\n", abs(a[0] - a[1]));
        else
            solve();
    }
}
