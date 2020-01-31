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

int rod;
int hangman;
string solution;
string guess;
set<char> solution_set;
set<char> guess_set;

void init() {
    hangman = 0;
    solution_set.clear();
    guess_set.clear();
}

bool winOrLose() {
    //put solution into set
    for (int i = 0; i < solution.size(); ++i) {
        solution_set.insert(solution[i]);
    }

    int solution_nums = 0;
    //不能将guess放入set再遍历，因为此题必须顺序遍历guess
    for (string::iterator iter = guess.begin(); iter != guess.end(); ++iter) {
        if (guess_set.count(*iter)) {
            continue;
        }
        guess_set.insert(*iter);
        if (solution_set.count(*iter)) {
            ++solution_nums;
            if (solution_nums == solution_set.size()) {
                return true;
            }
        } else {
            ++hangman;
            if (hangman == 7) {
                return false;
            }
        }
    }
    return false;
}

int main() {
    while (cin >> rod && rod != -1) {
        cin >> solution >> guess;
        init();
        if (winOrLose()) {
            cout << "Round " << rod << "\n";
            cout << "You win." << endl;
        } else {
            if (hangman == 7) {
                cout << "Round " << rod << "\n";
                cout << "You lose." << endl;
            } else {
                cout << "Round " << rod << "\n";
                cout << "You chickened out." << endl;
            }
        }
    }
}
