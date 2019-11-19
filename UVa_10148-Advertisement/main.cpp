#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>
#include <numeric>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::pair;

bool cmp(pair<int, int> o1, pair<int, int> o2){
    if(o1.second!=o2.second){
        return o1.second < o2.second;
    }else{
        return o1.first > o2.first;
    }

}

int main() {
    int cases;
    cin >> cases;
    while(cases--){
        int K, N;
        //cin.get(); //输入用例之间加入空格对数据读取没有影响，cin会跳过回车
        cin >> K >> N;
        vector<pair<int, int> > intervals;
        int l, r;
        while(N--){
            cin >> l >> r;
            if(l<r){
                intervals.emplace_back(std::make_pair(l, r));
            }else{
                intervals.emplace_back(std::make_pair(r, l));
            }
        }

        std::sort(intervals.begin(), intervals.end(), cmp);

        int min_l = intervals[0].first;
        int max_r = intervals[intervals.size()-1].second;
        for(int i=0; i<intervals.size(); ++i){
            if(intervals[i].first<min_l){
                min_l = intervals[i].first;
            }
        }
        vector<int> advertisements(max_r-min_l+1, 0);

        for(int i=0; i<intervals.size(); ++i){
            int l=intervals[i].first-min_l, r=intervals[i].second-min_l;
            if(r-l+1<=K){
                for(int j=l; j<=r; ++j){
                    advertisements[j] = 1;
                }
            }else{
                int count = 0;
                for(int j=l; j<=r; ++j){
                    if(advertisements[j]) ++count;
                }
                while(count<K){
                    if(advertisements[r] == 0){
                        advertisements[r] = 1;
                        ++count;
                    }
                    --r;
                }
            }

        }
        cout << std::accumulate(advertisements.begin(), advertisements.end(), 0) << '\n';
        for(int i=0; i<advertisements.size(); ++i){
            if(advertisements[i]) cout << i+min_l << '\n';
        }
        if(cases) cout << endl; //最后一个用例之后不输出空格，否则出错
    }
}
