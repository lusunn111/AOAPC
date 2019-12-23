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

string AeB;
double A;
int B;
double A_s[10][31];
int B_s[10][31];

void genTable() {
    //m*2^e = A*10^B
    //log10(m)+log10(2)*e = log10(A)+B
    //如果AeB是科学计数法，那么0<=log10(A)<1，则B就是整数部分
    for (int i = 0; i <= 9; ++i) {
        for (int j = 1; j <= 30; ++j) {
            double m = 1 - pow(2, -i - 1);
            long long e = pow(2, j) - 1;
            double t = log10(m) + log10(2.0) * e;
            B_s[i][j] = floor(t);
            A_s[i][j] = pow(10, t - B_s[i][j]);
        }
    }
}

int main() {
    genTable();
    while (cin >> AeB && AeB != "0e0") {
        for (auto iter = AeB.begin(); iter != AeB.end(); ++iter) {
            if (*iter == 'e') {
                *iter = ' ';
            }
        }
        stringstream ss(AeB);
        ss >> A >> B;
        if (A < 1) {
            A *= 10;
            B -= 1;
        }
        for (int i = 0; i <= 9; ++i) {
            for (int j = 1; j <= 30; ++j) {
                //精度不能太高，否则A和A_s匹配不了
                if (B == B_s[i][j] && fabs(A - A_s[i][j]) < 1e-4) {
                    cout << i << ' ' << j << endl;
                    break;
                }
            }
        }
    }
}
