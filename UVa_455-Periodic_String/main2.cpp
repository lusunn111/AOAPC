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

bool isPeriodic(int len) {
    if (str.size() % len)
        return false;
    else {
        int count = str.size() / len;//count代表多少个小段
        for (int i = 1; i < count; ++i) {
            for (int j = 0; j < len; ++j) {
                if (str[j] != str[i * len + j])
                    return false;
            }
        }
        return true;
    }
}

int main() {
    cin >> T;
    while (T--) {
        cin.get();//blank line
        cin >> str;
        //这边可以减少复杂度，将上限变为str.size()/2，但是要添加一个flag判断是否出现了小于此上限的周期，如果没有，则输出str.size()
        for (int i = 1; i <= str.size(); ++i) {
            if (isPeriodic(i)) {
                cout << i << endl;
                if (T != 0) {//
                    cout << endl;
                }
                break;
            }
        }
    }
}
