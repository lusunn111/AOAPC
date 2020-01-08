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

map<char, double> atomic_weight{{'C', 12.01},
                                {'H', 1.008},
                                {'O', 16.00},
                                {'N', 14.01}};

double molarMass() {
    double molar_mass = 0.0;
    int pos = 0;
    int subscipt = 0;
    for (int i = 0; i < str.size(); ++i) {
        //到达末尾
        if (i == str.size() - 1 && isalpha(str[i])) {
            molar_mass += atomic_weight[str[i]];
            break;
        } else if (i == str.size() - 1 && isdigit(str[i])) {
            molar_mass += atomic_weight[str[pos]] * subscipt;
            break;
        }

        //未到达末尾，四种情况
        if (isalpha(str[i]) && isalpha(str[i + 1])) {
        //字母字母，省略数字的情况，更新molar_mass
            molar_mass += atomic_weight[str[i]];
            subscipt = 0;
        } else if (isalpha(str[i]) && isdigit(str[i + 1])) {
        //字母数字，更新最新字母位置，更新subscript
            pos = i;
            subscipt = str[i + 1] - '0';
        } else if (isdigit(str[i]) && isdigit(str[i + 1])) {
        //数字数字，更新subscript
            subscipt *= 10;
            subscipt += str[i + 1] - '0';
        } else if (isdigit(str[i]) && isalpha(str[i + 1])) {
        //数字字母，前一字母结束，结算，更新molar_mass
            molar_mass += atomic_weight[str[pos]] * subscipt;
        }
    }
    return molar_mass;
}

int main() {
    cin >> T;
    while (T--) {
        cin >> str;
        cout << std::fixed << std::setprecision(3) << molarMass() << endl;
    }
}
