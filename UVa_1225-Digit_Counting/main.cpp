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

int kases;
int N;
int count[10];

void init(){
    memset(count, 0, sizeof(count));
}

//暴力法
void digitCount() {
    //O(n^2)
    for (int i = 1; i <= N; ++i){
        int i_copy = i;
        while(i_copy){
            ++count[i_copy%10];
            i_copy /= 10;
        }
    }
}

int main() {
    cin >> kases;
    while (kases--) {
        cin >> N;
        init();
        digitCount();
        for (int i = 0; i < 9; ++i) {
            cout << count[i] << " ";
        }
        cout << count[9] << endl;
    }
}