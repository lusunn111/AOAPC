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

int T;//number of test cases
string str;

int computeScore() {
    int score = 0;
    int consecutive_O = 0;//连续O的数量
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == 'O') {
            ++consecutive_O;
            score += consecutive_O;
        } else {
            consecutive_O = 0;//遇X复位
        }
    }
    return score;
}

int main() {
    cin >> T;
    while (T--) {
        cin >> str;
        cout << computeScore() << endl;
    }
}
