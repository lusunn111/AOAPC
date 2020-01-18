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

string line;
string paint1;
string paint2;

/*
 * 方块的遍历顺序123456=上前左右后下，将方块旋转后按这个顺序输出序号
 *              90度         180度        270度
 * 1朝上      123456      135246      142536      154326
 * 2朝上      263415      231645      214365      246135
 * 3朝上      326154      365214      312564      351624
 * 4朝上      421653      415263      456123      462513
 * 5朝上      513462      541632      564312      536142
 * 6朝上      653421      624351      645231      632541
 */
int rearr[24][6] = {{1, 2, 3, 4, 5, 6}, {1, 3, 5, 2, 4, 6}, {1, 5, 4, 3, 2, 6}, {1, 4, 2, 5, 3, 6},
                  {2, 6, 3, 4, 1, 5}, {2, 3, 1, 6, 4, 5}, {2, 1, 4, 3, 6, 5}, {2, 4, 6, 1, 3, 5},
                  {3, 2, 6, 1, 5, 4}, {3, 6, 5, 2, 1, 4}, {3, 1, 2, 5, 6, 4}, {3, 5, 1, 6, 2, 4},
                  {4, 2, 1, 6, 5, 3}, {4, 1, 5, 2, 6, 3}, {4, 5, 6, 1, 2, 3}, {4, 6, 2, 5, 1, 3},
                  {5, 1, 3, 4, 6, 2}, {5, 4, 1, 6, 3, 2}, {5, 6, 4, 3, 1, 2}, {5, 3, 6, 1, 4, 2},
                  {6, 5, 3, 4, 2, 1}, {6, 2, 4, 3, 5, 1}, {6, 4, 5, 2, 3, 1}, {6, 3, 2, 5, 4, 1}};

vector<string> rearrange() {
    vector<string> res;
    for (int i = 0; i < 24; ++i) {
        string s = "";
        for (int j = 0; j < 6; ++j) {
            s += paint1[rearr[i][j] - 1];
        }
        res.push_back(s);
    }
    return res;
}

int main() {
    while (cin >> line) {
        paint1 = line.substr(0, 6);
        paint2 = line.substr(6, 6);
        vector<string> paint1_rearr = rearrange();
        if (std::find(paint1_rearr.begin(), paint1_rearr.end(), paint2) != paint1_rearr.end())
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;
    }
}
