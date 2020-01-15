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

string master;
string driven;

int findShortest() {
    if (master.size() > driven.size())
        std::swap(master, driven);
    int min_len = master.size() + driven.size();

    //master整个在driven当中
    for (int i = 0; i <= driven.size() - master.size(); ++i) {
        bool ok = true;
        for (int j = 0; j < master.size(); ++j) {
            if (master[j] - '0' + driven[j + i] - '0' > 3) {
                ok = false;
                break;
            }
        }
        if (ok) {
            min_len = driven.size();
            return min_len;//最短情况，没有必要继续下去了
        }
    }

    //i代表重合部分的长度，master和driven部分重合
    for (int i = master.size() - 1; i >= 1; --i) {
        bool ok1 = true;//能否咬合
        for (int j = 0; j < i; ++j) {
            if (master[j] - '0' + driven[driven.size() - i + j] - '0' > 3) {
                ok1 = false;
                break;
            }
        }
        if (ok1) {
            min_len = (min_len < master.size() + driven.size() - i) ? min_len : master.size() + driven.size() - i;
            return min_len;
        }

        bool ok2 = true;
        for (int j = 0; j < i; ++j) {
            if (driven[j] - '0' + master[master.size() - i + j] - '0' > 3) {
                ok2 = false;
                break;
            }
        }
        if (ok2) {
            min_len = (min_len < master.size() + driven.size() - i) ? min_len : master.size() + driven.size() - i;
            return min_len;
        }
    }

    return min_len;
}

int main() {
    while (cin >> master >> driven) {
        cout << findShortest() << endl;
    }
}
