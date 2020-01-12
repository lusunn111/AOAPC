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

struct rectangular {
    int w;
    int h;
} rect[6];
vector<pair<int, int> > oppos;

void init() {
    oppos.clear();
}

bool isPossible() {
    //check 3 pairs，只有三种面
    bool vis[6] = {false};
    for (int i = 0; i < 6; ++i) {
        if (!vis[i]) {
            for (int j = i + 1; j < 6; ++j) {
                if (!vis[j] && (rect[i].w == rect[j].w && rect[i].h == rect[j].h)) {
                    oppos.emplace_back(i, j);
                    vis[i] = vis[j] = true;
                    break;
                }
            }
        }
    }
    if (oppos.size() != 3)
        return false;

    //边的长短
    if (rect[oppos[0].first].w == rect[oppos[1].first].w) {
        if ((rect[oppos[0].first].h == rect[oppos[2].first].w) && (rect[oppos[1].first].h == rect[oppos[2].first].h))
            return true;
        else if ((rect[oppos[0].first].h == rect[oppos[2].first].h) &&
                 (rect[oppos[1].first].h == rect[oppos[2].first].w))
            return true;
        else
            return false;
    } else if (rect[oppos[0].first].w == rect[oppos[1].first].h) {
        if ((rect[oppos[0].first].h == rect[oppos[2].first].w) && (rect[oppos[1].first].w == rect[oppos[2].first].h))
            return true;
        else if ((rect[oppos[0].first].h == rect[oppos[2].first].h) &&
                 (rect[oppos[1].first].w == rect[oppos[2].first].w))
            return true;
        else
            return false;
    } else if (rect[oppos[0].first].w == rect[oppos[2].first].w) {
        if ((rect[oppos[0].first].h == rect[oppos[1].first].w) && (rect[oppos[1].first].h == rect[oppos[2].first].h))
            return true;
        else if ((rect[oppos[0].first].h == rect[oppos[1].first].h) &&
                 (rect[oppos[1].first].w == rect[oppos[2].first].h))
            return true;
        else
            return false;
    } else if (rect[oppos[0].first].w == rect[oppos[2].first].h) {
        if ((rect[oppos[0].first].h == rect[oppos[1].first].w) && (rect[oppos[1].first].h == rect[oppos[2].first].w))
            return true;
        else if ((rect[oppos[0].first].h == rect[oppos[1].first].h) &&
                 (rect[oppos[1].first].w == rect[oppos[2].first].w))
            return true;
        else
            return false;
    }
}

int main() {
    while (cin >> rect[0].w >> rect[0].h >> rect[1].w >> rect[1].h >> rect[2].w >> rect[2].h
               >> rect[3].w >> rect[3].h >> rect[4].w >> rect[4].h >> rect[5].w >> rect[5].h) {
        init();
        for (int i = 0; i < 6; ++i) {
            if (rect[i].w > rect[i].h)
                swap(rect[i].w, rect[i].h);
        }

        if (isPossible())
            cout << "POSSIBLE" << endl;
        else
            cout << "IMPOSSIBLE" << endl;
    }
}
