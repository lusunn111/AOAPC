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

//将所有点从0开始编号，转换成图，用邻接矩阵存储边
int matrix[100][100];
int n;
int m;
int kase = 0;

void init() {
    memset(matrix, 0, sizeof(matrix));
}

void readBoard() {
    char c;
    int i, j;
    for (int k = 0; k < m; ++k) {
        cin >> c >> i >> j;
        int beg, end;
        if (c == 'H') {//水平边
            beg = (i - 1) * n + j - 1;
            end = beg + 1;//计算点的编号
        } else if (c == 'V') {//垂直边
            beg = (j - 1) * n + i - 1;
            end = beg + n;
        }
        matrix[beg][end] = 1;
        matrix[end][beg] = 1;//无向图
    }
}

//判断由编号beg做左上角顶点的边为e的正方形
bool isSquare(int left_up, int e) {
    int beg, end;
    //上边
    for (int i = 0; i < e; ++i) {
        beg = left_up + i;
        end = beg + 1;
        if (!matrix[beg][end])
            return false;
    }
    //右边
    for (int i = 0; i < e; ++i) {
        beg = left_up + e + i * n;
        end = beg + n;
        if (!matrix[beg][end])
            return false;
    }
    //下边
    for (int i = 0; i < e; ++i) {
        beg = left_up + e * n + i;
        end = beg + 1;
        if (!matrix[beg][end])
            return false;
    }
    //左边
    for (int i = 0; i < e; ++i) {
        beg = left_up + i * n;
        end = beg + n;
        if (!matrix[beg][end])
            return false;
    }

    return true;
}

//计算边长为e的边数量
int countSquare(int e) {
    int cnt = 0;
    for (int i = 0; i < n * n - e * n - e; ++i) {
        if (n - i % n <= e) {//点太靠右
            continue;
        }
        if (isSquare(i, e)) {
            ++cnt;
        }
    }

    return cnt;
}

int main() {
    while (cin >> n >> m) {
        init();
        ++kase;
        if (kase != 1)
            cout << "\n**********************************\n" << endl;
        readBoard();

        cout << "Problem #" << kase << '\n' << endl;

        bool no_square = true;
        for (int e = 1; e < n; ++e) {
            int cnt = countSquare(e);
            if (cnt) {
                no_square = false;
                cout << cnt << " square (s) of size " << e << endl;
            }
        }
        if (no_square) {
            cout << "No completed squares can be found." << endl;
        }
    }
}
