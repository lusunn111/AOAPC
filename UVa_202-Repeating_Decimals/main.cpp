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

//观察竖式除法就可以得出此题的解法，当出现重复出现的余数时说明出现了循环

int numerator, denominator;
map<int, int> remainders;//存放已经出现过的余数，及其在decimals中的坐标
vector<int> decimals;//存放小数部分
int cnt;
int kase = 0;

void init() {
    remainders.clear();
    decimals.clear();
    cnt = 0;
}

int main() {
    while (cin >> numerator >> denominator) {
        init();
        ++kase;
        ++cnt;
        int numerator_c = numerator;
        remainders.emplace(numerator % denominator, cnt);
        decimals.emplace_back(numerator / denominator);
        numerator = numerator % denominator * 10;
        while (!remainders.count(numerator % denominator)) {//尚未出现重复
            ++cnt;
            remainders.emplace(numerator % denominator, cnt);
            decimals.emplace_back(numerator / denominator);
            numerator = numerator % denominator * 10;
        }
        //出现了重复，寻找重复的index
        decimals.emplace_back(numerator / denominator);
        int start = remainders[numerator % denominator];
        int count = decimals.size() - start;

//        if (kase != 1)
//            cout << endl;//如果只有两两结果之间输出空行而最后一个案例之后不输出空行就这么做
        cout << numerator_c << '/' << denominator << " = " << decimals[0] << '.';
        for (int i = 1; i != start; ++i) {
            cout << decimals[i];
        }
        cout << '(';
        if (decimals.size() - 1 <= 50) {
            for (int i = start; i != decimals.size(); ++i) {
                cout << decimals[i];
            }
            cout << ')' << endl;
        } else {
            for (int i = start; i != 51; ++i) {
                cout << decimals[i];
            }
            cout << "...)" << endl;
        }
        cout << "   " << count << " = number of digits in repeating cycle" << endl;
        cout << endl;//blank line，傻吊，最后一行之后还要输出空行，生怕我不PE是吧
    }
}
