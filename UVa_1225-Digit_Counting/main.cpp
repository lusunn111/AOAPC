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
int N;
int count[10];

void digitCount(int num) {
    while (num) {
        ++count[num % 10];
        num /= 10;
    }
}

int main() {
    cin >> T;
    while (T--) {
        cin >> N;
        memset(count, 0, sizeof(count));

        for (int i = 1; i <= N; ++i) {
            digitCount(i);
        }

        for (int i = 0; i < 9; ++i) {
            cout << count[i] << ' ';
        }
        cout << count[9] << endl;
    }
}
