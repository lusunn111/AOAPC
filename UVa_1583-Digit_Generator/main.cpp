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

int N;//1<=N<=100000
int T;//T represent the number of test cases

int digitSum(int num) {
    int sum = num;
    while (num) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int minGenerator(int N) {
    int start = N - 5 * 9;//N最大是5位数，也就是各位相加最多是5个9
    if (start < 0)
        start = 1;
    for (int i = start; i < N; ++i) {
        if (digitSum(i) == N)
            return i;
    }
    return 0;
}

int main() {
    cin >> T;
    while (T--) {
        cin >> N;
        cout << minGenerator(N) << endl;
    }
}
