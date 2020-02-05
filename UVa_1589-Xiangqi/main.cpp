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

//代码量太大，复杂度倒不高
//改进：只要用一个二维数组列出红方能到达的位置就可以了，而且只要能到达黑方的上下左右就行

vector<vector<char> > r_checkboard(11, vector<char>(10));//棋盘
pair<int, int> black_general;
map<char, vector<pair<int, int> > > r_pieces;
int N;//num of red pieces

void init() {
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 10; ++j) {
            r_checkboard[i][j] = ' ';
        }
    }
    r_pieces.clear();
}

void readRedPieces() {
    char piece;
    int row, col;
    for (int i = 0; i < N; ++i) {
        cin >> piece >> row >> col;
        if ('G' == piece) {
            r_pieces['G'].emplace_back(row, col);
            r_checkboard[row][col] = 'G';
        } else if ('R' == piece) {//chariot
            r_pieces['R'].emplace_back(row, col);
            r_checkboard[row][col] = 'R';
        } else if ('H' == piece) {//horse
            r_pieces['H'].emplace_back(row, col);
            r_checkboard[row][col] = 'H';
        } else if ('C' == piece) {//cannon
            r_pieces['C'].emplace_back(row, col);
            r_checkboard[row][col] = 'C';
        }
    }
}

void capture() {
    char p = r_checkboard[black_general.first][black_general.second];//被吃掉的棋子
    for (int i = 0; i < r_pieces[p].size(); ++i) {
        if (r_pieces[p][i] == black_general) {
            r_pieces[p].erase(r_pieces[p].begin() + i);
            r_checkboard[black_general.first][black_general.second] = ' ';//黑将不放在红色棋盘上不影响结果
        }
    }
}

bool isFlyingGeneral(int row, int col) {
    if (col != r_pieces['G'][0].second) {
        return false;
    } else {
        for (int i = row + 1; i < r_pieces['G'][0].first; ++i) {
            if (r_checkboard[i][col] != ' ')//这条线上有其他棋子
                return false;
        }
    }

    return true;
}

bool moveBGeneral(char direction) {
    switch (direction) {
        case 'U':
            if (black_general.first == 1)//出界
                return false;
            else {
                //更新black_general坐标
                black_general.first -= 1;
                //向上一步的情况不可能出现双将碰面

                //上面有红色棋子，则被吃掉
                if (r_checkboard[black_general.first][black_general.second] != ' ')
                    capture();

                return true;
            }
        case 'D':
            if (black_general.first == 3)
                return false;
            else {
                //向下走可能导致双将碰面，这种情况要在更新位置之前检查
                if (isFlyingGeneral(black_general.first + 1, black_general.second))
                    return false;

                black_general.first += 1;

                if (r_checkboard[black_general.first][black_general.second] != ' ')
                    capture();

                return true;
            }
        case 'L':
            if (black_general.second == 4)
                return false;
            else {
                if (isFlyingGeneral(black_general.first, black_general.second - 1))
                    return false;

                black_general.second -= 1;
                if (r_checkboard[black_general.first][black_general.second] != ' ')
                    capture();

                return true;
            }
        case 'R':
            if (black_general.second == 6)
                return false;
            else {
                if (isFlyingGeneral(black_general.first, black_general.second + 1))
                    return false;

                black_general.second += 1;
                if (r_checkboard[black_general.first][black_general.second] != ' ')
                    capture();

                return true;
            }
    }
}

//红车能不能一步吃将
bool isRRDead() {
    for (int i = 0; i < r_pieces['R'].size(); ++i) {
        //红车与黑将在同一行
        if (r_pieces['R'][i].first == black_general.first) {
            int col1 = r_pieces['R'][i].second;
            int col2 = black_general.second;
            bool noblock = true;//之间没有阻碍
            for (int j = min(col1, col2) + 1; j < max(col1, col2); ++j) {
                if (r_checkboard[black_general.first][j] != ' ') {
                    noblock = false;
                    break;
                }
            }
            //没阻碍，能一步吃掉将
            if (noblock)
                return true;
        } else if (r_pieces['R'][i].second == black_general.second) {//红车与黑将在同一列
            int row1 = r_pieces['R'][i].first;
            int row2 = black_general.first;
            bool noblock = true;//之间没有阻碍
            for (int j = min(row1, row2) + 1; j < max(row1, row2); ++j) {
                if (r_checkboard[j][black_general.second] != ' ') {
                    noblock = false;
                    break;
                }
            }
            //没阻碍，能一步吃掉将
            if (noblock)
                return true;
        }
    }

    return false;
}

//红马能不能一步吃将
bool isRHDead() {
    vector<pair<int, int> > dx = {{-1, -2},
                                  {-2, -1},
                                  {1,  -2},
                                  {2,  -1},
                                  {-1, 2},
                                  {-2, 1},
                                  {1,  2},
                                  {2,  1}};
    //别马腿的向量，和dx要一一对应
    vector<pair<int, int> > dxx = {{0,  -1},
                                   {-1, 0},
                                   {0,  -1},
                                   {1,  0},
                                   {0,  1},
                                   {-1, 0},
                                   {0,  1},
                                   {1,  0}};
    vector<pair<int, int> > targets;//所有马的所有一步可能终点
    for (int i = 0; i < r_pieces['H'].size(); ++i) {
        for (int j = 0; j < dx.size(); ++j) {
            int row1 = r_pieces['H'][i].first + dx[j].first;
            int col1 = r_pieces['H'][i].second + dx[j].second;
            int row2 = r_pieces['H'][i].first + dxx[j].first;
            int col2 = r_pieces['H'][i].second + dxx[j].second;
            //终点在棋盘内
            if (row1 >= 1 && row1 <= 10 && col1 >= 1 && col1 <= 9) {
                //没有棋子别马腿
                if (r_checkboard[row2][col2] == ' ')
                    targets.emplace_back(row1, col1);
            }
        }
    }
    for (int i = 0; i < targets.size(); ++i) {
        if (targets[i].first == black_general.first && targets[i].second == black_general.second)
            return true;
    }

    return false;
}

//红炮能不能一步吃将
bool isRCDead() {
    for (int i = 0; i < r_pieces['C'].size(); ++i) {
        //红炮与黑将在同一行
        if (r_pieces['C'][i].first == black_general.first) {
            int col1 = r_pieces['C'][i].second;
            int col2 = black_general.second;
            int count = 0; //之间有几个棋子
            for (int j = min(col1, col2) + 1; j < max(col1, col2); ++j) {
                if (r_checkboard[black_general.first][j] != ' ') {
                    ++count;
                }
            }
            //没阻碍，能一步吃掉将
            if (1 == count)
                return true;
        } else if (r_pieces['C'][i].second == black_general.second) {//红炮与黑将在同一列
            int row1 = r_pieces['C'][i].first;
            int row2 = black_general.first;
            int count = 0; //之间有几个棋子
            for (int j = min(row1, row2) + 1; j < max(row1, row2); ++j) {
                if (r_checkboard[j][black_general.second] != ' ') {
                    ++count;
                }
            }
            //没阻碍，能一步吃掉将
            if (1 == count)
                return true;
        }
    }

    return false;
}

//红方送死
bool courtDeath() {
    if (black_general.second != r_pieces['G'][0].second) {
        return false;
    } else {
        int row1 = black_general.first;
        int row2 = r_pieces['G'][0].first;
        for (int i = row1 + 1; i < row2; ++i) {
            if (r_checkboard[i][black_general.second] != ' ')
                return false;
        }
    }

    return true;
}

bool isCheckMate() {
    if (courtDeath()) {
        return false;
    }

    char directions[4] = {'U', 'D', 'L', 'R'};
    pair<int, int> black_general_copy = black_general;
    map<char, vector<pair<int, int> > > r_pieces_copy = r_pieces;
    vector<vector<char> > r_checkboard_copy(r_checkboard);
    for (int i = 0; i < 4; ++i) {
        //moveBGeneral内更新的东西都要在这恢复
        black_general = black_general_copy;
        r_pieces = r_pieces_copy;
        r_checkboard = r_checkboard_copy;
        //黑棋成功走完一步且没死,
        if (moveBGeneral(directions[i]) && !isRHDead() && !isRRDead() && !isRCDead())
            return false;
    }

    return true;
}

int main() {
    int i = 0;
    while (cin >> N && N) {
        ++i;
        init();
        cin >> black_general.first >> black_general.second;
        readRedPieces();
        if (isCheckMate())
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}
