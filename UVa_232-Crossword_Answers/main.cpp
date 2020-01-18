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

const int MAX_R = 11, MAX_C = 11;

int r, c;//rows, columns
char matrix[MAX_R][MAX_C];
int num[MAX_R][MAX_C];
int kase = 0;

void init() {
    for (int i = 0; i < MAX_R; ++i) {
        for (int j = 0; j < MAX_C; ++j) {
            matrix[i][j] = '*';
        }
    }
    memset(num, 0, sizeof(num));
}

void number() {
    int count = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if ((i == 0 && matrix[i][j] != '*') || (j == 0 && matrix[i][j] != '*')
                || ((matrix[i - 1][j] == '*' || matrix[i][j - 1] == '*') && matrix[i][j] != '*')) {
                ++count;
                num[i][j] = count;
            }
        }
    }
}

void across() {
    vector<pair<int, string> > words;
    for (int i = 0; i < r; ++i) {
        bool start = false;
        string str;
        int id;
        for (int j = 0; j < c + 1; ++j) {
            if (!start && matrix[i][j] != '*') {
                start = true;
                id = num[i][j];
                str += matrix[i][j];
            } else if (start && matrix[i][j] != '*') {
                str += matrix[i][j];
            } else if (start && matrix[i][j] == '*') {
                start = false;
                words.emplace_back(id, str);
                str.clear();
            }
        }
    }

    for (int i = 0; i < words.size(); ++i) {
        cout << std::setw(3) << words[i].first << '.' << words[i].second << endl;
    }
}

void down() {
    vector<pair<int, string> > words;
    for (int j = 0; j < c; ++j) {
        bool start = false;
        string str;
        int id;
        for (int i = 0; i < r + 1; ++i) {
            if (!start && matrix[i][j] != '*') {
                start = true;
                id = num[i][j];
                str += matrix[i][j];
            } else if (start && matrix[i][j] != '*') {
                str += matrix[i][j];
            } else if (start && matrix[i][j] == '*') {
                start = false;
                words.emplace_back(id, str);
                str.clear();
            }
        }
    }

    std::sort(words.begin(), words.end(),
              [](pair<int, string> r1, pair<int, string> r2) { return r1.first < r2.first; });
    for (int i = 0; i < words.size(); ++i) {
        cout << std::setw(3) << words[i].first << '.' << words[i].second << endl;
    }
}

int main() {
    while (cin >> r && r) {
        ++kase;
        cin >> c;
        init();

        for (int i = 0; i < r; ++i) {
            string str;
            cin >> str;
            for (int j = 0; j < c; ++j) {
                matrix[i][j] = str[j];
            }
        }
        number();

        if (kase != 1)
            cout << endl;//blank line
        cout << "puzzle #" << kase << ":" << endl;
        cout << "Across" << endl;
        across();

        cout << "Down" << endl;
        down();
    }
}
