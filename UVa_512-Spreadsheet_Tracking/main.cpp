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

//先将所有命令按顺序存好，再按输入的位置来扫描每一条命令，看命令对此位置有无影响
//如果先存好所有位置的坐标，再根据每一个命令更新所有位置的坐标，复杂度太高，每一条命令要更新的单元太多
int R, C;
int num_oper;
int num_query;
int dc_count, dr_count, ic_count, ir_count, ex_count;
int kase = 0;

vector<string> opers;
vector<vector<int> > dc;
vector<vector<int> > dr;
vector<vector<int> > ic;
vector<vector<int> > ir;
vector<vector<int> > ex;

void init() {
    opers.clear();
    dc_count = 0;
    dr_count = 0;
    ic_count = 0;
    ir_count = 0;
    ex_count = 0;
    dc.clear();
    dr.clear();
    ic.clear();
    ir.clear();
    ex.clear();
}

int main() {
    while (cin >> R >> C && R && C) {
        init();
        ++kase;
        cin >> num_oper;
        for (int j = 0; j < num_oper; ++j) {
            string oper;
            cin >> oper;
            if (oper == "EX") {
                opers.emplace_back(oper);
                int r1, c1, r2, c2;
                cin >> r1 >> c1 >> r2 >> c2;
                vector<int> e = {r1, c1, r2, c2};
                ex.push_back(e);
            } else if (oper == "DC") {
                opers.emplace_back(oper);
                int c; //num of columns to delete
                cin >> c;
                vector<int> cols; //index of columns to delete
                for (int i = 0; i < c; ++i) {
                    int col;
                    cin >> col;
                    cols.emplace_back(col);
                }
                dc.push_back(cols);
                ++dc_count;
            } else if (oper == "DR") {
                opers.emplace_back(oper);
                int r; //num of rows to delete
                cin >> r;
                vector<int> rows; //index of rows to delete
                for (int i = 0; i < r; ++i) {
                    int row;
                    cin >> row;
                    rows.emplace_back(row);
                }
                dr.push_back(rows);
                ++dr_count;
            } else if (oper == "IC") {
                opers.emplace_back(oper);
                int c;
                cin >> c;
                vector<int> cols;
                for (int i = 0; i < c; ++i) {
                    int col;
                    cin >> col;
                    cols.emplace_back(col);
                }
                ic.push_back(cols);
                ++ic_count;
            } else if (oper == "IR") {
                opers.emplace_back(oper);
                int r;
                cin >> r;
                vector<int> rows;
                for (int i = 0; i < r; ++i) {
                    int row;
                    cin >> row;
                    rows.emplace_back(row);
                }
                ir.push_back(rows);
                ++ir_count;
            }
        }
        if (kase != 1) cout << endl;
        cout << "Spreadsheet #" << kase << endl;
        cin >> num_query;
        for (int i = 0; i < num_query; ++i) {
            bool gone = false;
            int q_r, q_c;
            int dc_c = 0, dr_c = 0, ic_c = 0, ir_c = 0, ex_c = 0;
            cin >> q_r >> q_c;
            cout << "Cell data in (" << q_r << ',' << q_c << ") ";
            for (int j = 0; j < opers.size(); ++j) {
                if (opers[j] == "EX") {
                    if (q_r == ex[ex_c][0] && q_c == ex[ex_c][1]) {
                        q_r = ex[ex_c][2];
                        q_c = ex[ex_c][3];
                    } else if (q_r == ex[ex_c][2] && q_c == ex[ex_c][3]) {
                        q_r = ex[ex_c][0];
                        q_c = ex[ex_c][1];
                    }
                    ++ex_c;
                } else if (opers[j] == "DR") {
                    int num_del = 0;

                    for (int k = 0; k < dr[dr_c].size(); ++k) {
                        if (dr[dr_c][k] < q_r) {
                            ++num_del;
                        } else if (dr[dr_c][k] == q_r) {
                            gone = true;
                        }
                    }
                    q_r -= num_del;
                    ++dr_c;
                } else if (opers[j] == "DC") {
                    int num_del = 0;

                    for (int k = 0; k < dc[dc_c].size(); ++k) {
                        if (dc[dc_c][k] < q_c) {
                            ++num_del;
                        } else if (dc[dc_c][k] == q_c) {
                            gone = true;
                        }
                    }
                    q_c -= num_del;
                    ++dc_c;
                } else if (opers[j] == "IR") {
                    int num_ins = 0;
                    for (int k = 0; k < ir[ir_c].size(); ++k) {
                        if (ir[ir_c][k] <= q_r) {
                            ++num_ins;
                        }
                    }
                    q_r += num_ins;
                    ++ir_c;
                } else if (opers[j] == "IC") {
                    int num_ins = 0;
                    for (int k = 0; k < ic[ic_c].size(); ++k) {
                        if (ic[ic_c][k] <= q_c) {
                            ++num_ins;
                        }
                    }
                    q_c += num_ins;
                    ++ic_c;
                }
            }

            if (gone) {
                cout << "GONE" << endl;
            } else {
                cout << "moved to (" << q_r << ',' << q_c << ')' << endl;
            }
        }
    }
}
