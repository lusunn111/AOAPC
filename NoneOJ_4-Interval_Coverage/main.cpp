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
    if(o1.first!=o2.first)
        return o1.first < o2.first;
    else
        return o1.second-o1.first > o2.second-o1.second;//左坐标相同按长度排序，优先选长的
}

void solve(vector<pair<int, int> >& intervals, int start, int left, int right, int& res){
    while(start<intervals.size() && intervals[start].second<left){
        ++start;
    }
    if(intervals[start].first>left || (start>=intervals.size()&&left<right)){
        res = -1;
        return;
    }else if(intervals[start].second>=right){
        ++res;
        return;
    }{
        ++res;
        left = intervals[start].second;
        ++start;
        solve(intervals, start, left, right, res);
    }
}

int main() {
    int s, t;
    cin >> s >> t;
    vector<pair<int, int> > intervals;
    int l, r;
    while(cin >> l >> r){
        if(l==0&&r==0) break;
        intervals.emplace_back(std::make_pair(l, r));
    }
    std::sort(intervals.begin(), intervals.end(), cmp);
    int res(0);
    solve(intervals, 0, s, t, res);
    cout << res << endl;
}
