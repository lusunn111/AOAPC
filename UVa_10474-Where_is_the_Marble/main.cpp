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

int kases = 0;

int main() {
    int N, Q;
    while (cin >> N >> Q && N && Q) {
        ++kases;
        vector<int> marbles;
        for (int i = 0; i < N; ++i) {
            int n;
            cin >> n;
            marbles.push_back(n);
        }
        std::sort(marbles.begin(), marbles.end());
        cout << "CASE# " << kases << ":" << endl;
        for (int i = 0; i < Q; ++i) {
            int q;
            cin >> q;
            int flag = std::lower_bound(marbles.begin(), marbles.end(), q) - marbles.begin();
            if(marbles[flag] != q){
                cout << q << " not found" << endl;
            }else{
                cout << q << " found at " << flag+1 << endl;
            }
        }
    }
}