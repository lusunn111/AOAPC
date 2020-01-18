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

using std::cin;
using std::cout;
using std::endl;

using std::queue;
using std::pair;
using std::priority_queue;
using std::list;
using std::map;
using std::string;
using std::vector;
using std::unordered_map;
using std::set;
using std::stringstream;

using std::min;
using std::max;

/*
 * 这种解法AC了，但是应该是WA，比如以下这个用例，输出True，但是实际上应该是False
 * 此题稍微简便一些的运算应该是模拟旋转过程（六种数字分别朝上，顺垂直轴旋转），不需要暴力枚举24种排序
 * rgbgrbgrgrbb
 */

//观察发现每对平行面的序号和相等
bool valid(string pat1, string pat2) {
    //paint1按123456,123分别是上前左，正好没有平行面
    for (int i = 0; i < 3; ++i) {
        bool vld = false;
        for (int j = 0; j < 6; ++j) {
            //寻找pat2中有没有和pat1中相同的平行面
            if (pat1[i] == pat2[j] && pat1[5 - i] == pat2[5 - j]) {
                vld = true;
                //涂白，防止两次寻找的是同一对
                pat2[j] = pat2[5 - j] = '0';
                break;
            }
        }
        //只要pat1中有一对在pat2找不到对应，不能再找下去，防止下一次vld被覆盖
        if (!vld)
            return vld;
    }
    return true;
}

int main() {
    string line;
    string paint1;
    string paint2;
    while (cin >> line) {
        paint1 = line.substr(0, 6);
        paint2 = line.substr(6, 6);
        if (valid(paint1, paint2))
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;
    }
}
