#include <iostream>
#include <cstring>
#include <cfloat>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <map>
#include <numeric>
#include <climits>
#include <cstring>
#include <list>
#include <queue>
#include <utility>
#include <functional>
#include <unordered_map>
#include <set>

using std::queue;
using std::pair;
using std::make_pair;
using std::priority_queue;
using std::list;
using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::greater;
using std::unordered_map;
using std::set;
using std::begin;
using std::end;
using std::find;
using std::swap;

const int MAX_M = 55;

int T;//number of test cases
int m;//number of sequences
int n;//length of sequence
string sequences[MAX_M];

string minDisSeq(int &res_dis) {
    string res_seq;
    for (int i = 0; i < n; ++i) {
        map<char, int> count = {{'A', 0},
                                {'C', 0},
                                {'G', 0},
                                {'T', 0}};
        for (int j = 0; j < m; ++j) {
            ++count[sequences[j][i]];
        }

        vector<pair<char, int> > count_vec(count.begin(), count.end());//map不能直接排序

        std::sort(count_vec.begin(), count_vec.end(),
                  [](const pair<char, int> &r1, const pair<char, int> &r2) {
                      return r1.second > r2.second || (r1.second == r2.second && r1.first < r2.first);
                  }
        );
        res_seq += count_vec[0].first;
        res_dis += m - count_vec[0].second;
    }
    return res_seq;
}

int main() {
    cin >> T;
    while (T--) {
        cin >> m >> n;
        for (int i = 0; i < m; ++i) {
            cin >> sequences[i];
        }
        int res_dis = 0;
        cout << minDisSeq(res_dis) << endl;
        cout << res_dis << endl;
    }
}
