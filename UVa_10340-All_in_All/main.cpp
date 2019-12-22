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

string s, t;

bool isSubsequence() {
    int start = 0;
    for (int i = 0; i < s.size(); ++i) {
        for (int j = start; j < t.size(); ++j) {
            if (s[i] == t[j]) {
                start = j + 1;
                break;
            }
            if (j == t.size() - 1 && s[i] != t[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    while (cin >> s >> t) {
        if (isSubsequence())
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}
