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
#include <sstream>

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
using std::pow;
using std::log10;
using std::stringstream;
using std::fabs;

int N, k, m;

void selectAndOutput() {
    vector<int> circle(N);
    for (int i = 0; i < N; ++i) {
        circle[i] = i + 1;
    }

    int i = 0, j = N - 1;
    int r = circle.size();
    while (0 != circle.size()) {
        i = (i + k - 1) % r;
        j = (j - m + 1) % r;//如果直接用circle.size()，是size_t类型，导致结果非负
        while (i < 0) i += r;
        while (j < 0) j += r;
        if (i == j) {
            cout << std::setw(3) << circle[i] << std::flush;
            circle.erase(circle.begin() + i);
            r = circle.size();
            if (circle.size() != 0) {
                cout << ",";
                i = (i + r) % r;
                j = (j - 1 + r) % r;
            }
        } else if (i < j) {
            cout << std::setw(3) << circle[i] << std::setw(3) << circle[j] << std::flush;
            circle.erase(circle.begin() + j);//先删后面的再删前面的才不会影响
            circle.erase(circle.begin() + i);
            r = circle.size();
            if (circle.size() != 0) {
                cout << ",";
                i = (i + r) % circle.size();
                j = (j - 2 + r) % circle.size();
            }
        } else {
            cout << std::setw(3) << circle[i] << std::setw(3) << circle[j] << std::flush;
            circle.erase(circle.begin() + i);
            circle.erase(circle.begin() + j);
            r = circle.size();
            if (circle.size() != 0) {
                cout << ",";
                i = (i - 1 + r) % circle.size();
                j = (j - 1 + r) % circle.size();
            }
        }
    }
    cout << endl;
}

int main() {
    while (cin >> N >> k >> m && N && k && m) {
        selectAndOutput();
    }
}
