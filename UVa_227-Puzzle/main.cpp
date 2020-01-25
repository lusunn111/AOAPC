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

int kcase = 0;
char c;
char puzzle[5][5];
string command;
int x, y;//index of blank
bool illegal = false;

void move() {
    for (int i = 0; i < command.size() - 1; ++i) {
        switch (command[i]) {
            case 'A':
                if (x == 0) {
                    illegal = true;
                    return;
                }
                swap(puzzle[x][y], puzzle[x - 1][y]);
                x = x - 1;
                break;
            case 'B':
                if (x == 4) {
                    illegal = true;
                    return;
                }
                swap(puzzle[x][y], puzzle[x + 1][y]);
                x = x + 1;
                break;
            case 'L':
                if (y == 0) {
                    illegal = true;
                    return;
                }
                swap(puzzle[x][y], puzzle[x][y - 1]);
                y = y - 1;
                break;
            case 'R':
                if (y == 4) {
                    illegal = true;
                    return;
                }
                swap(puzzle[x][y], puzzle[x][y + 1]);
                y = y + 1;
                break;
            default:
                //command not in "ABLR"
                illegal = true;
        }
    }
}

int main() {
    while ((c = cin.get()) != 'Z') {
        ++kcase;
        cin.putback(c);
        //不能整行读入，因为整行读入会忽略首尾空白符
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                puzzle[i][j] = cin.get();
                if (puzzle[i][j] == ' ') {
                    x = i;
                    y = j;
                }
            }
            cin.get();//读入回车
        }

        command.clear();
        string comm;
        do {
            cin >> comm;
            command += comm;
        } while (*(comm.end() - 1) != '0');

        illegal = false;
        move();

        if (kcase != 1)
            cout << endl;//blank line between cases
        cout << "Puzzle #" << kcase << ':' << endl;
        if (illegal)
            cout << "This puzzle has no final configuration." << endl;
        else {
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    cout << puzzle[i][j];
                    if (j != 4)
                        cout << ' ';
                }
                cout << '\n';
            }
        }
        cin.get();
    }
}
