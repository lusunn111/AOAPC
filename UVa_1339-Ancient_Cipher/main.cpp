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

string encrypted_msg;
string original_msg;

map<char, int> encrypted;
map<char, int> original;


void init() {
    encrypted.clear();
    original.clear();
}

bool isPossible() {
    if (encrypted_msg.size() != original_msg.size())
        return false;
    for (int i = 0; i < encrypted_msg.size(); ++i) {
        ++encrypted[encrypted_msg[i]];
    }
    for (int i = 0; i < original_msg.size(); ++i) {
        ++original[original_msg[i]];
    }
    if (encrypted.size() != original.size())
        return false;
    vector<int> encrypt;
    for (auto iter = encrypted.begin(); iter != encrypted.end(); ++iter)
        encrypt.emplace_back(iter->second);
    vector<int> origin;
    for (auto iter = original.begin(); iter != original.end(); ++iter)
        origin.emplace_back(iter->second);
    std::sort(encrypt.begin(), encrypt.end());
    std::sort(origin.begin(), origin.end());
    if (encrypt != origin)
        return false;
    return true;
}

int main() {
    while (cin >> encrypted_msg >> original_msg) {
        init();
        if (isPossible())
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}
