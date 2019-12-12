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

int dijkstra(vector<list<pair<int, int>> >& roads, int N){
    vector<int> d(N+1, INT_MAX);
    d[1] = 0;

    priority_queue<pair<int, int>, std::vector<pair<int, int>>, greater<pair<int, int>> > q;
    q.push(make_pair(d[1], 1));
    while(!q.empty()){
        auto u = q.top();
        q.pop();
        int min_ind = u.second;
        //消除重复？貌似这种情况不会出现啊，从push语句来看
        if(d[min_ind] != u.first) continue;

        for(auto iter=roads[min_ind].begin(); iter!=roads[min_ind].end(); ++iter){
            if(d[min_ind]+iter->second < d[iter->first]){
                d[iter->first] = d[min_ind]+iter->second;
                q.push(make_pair(d[iter->first], iter->first));
            }
        }

    }

    return d[N];
}

int main(){
    int N, M;
    while(cin>>N>>M && N!=0 && M!=0){
        //没有0号路口
        vector<list<pair<int, int>> > roads(N+1);
        int A, B, C;
        for(int i=0; i<M; ++i){
            cin >> A >> B >> C;
            roads[A].emplace_back(make_pair(B, C));
            roads[B].emplace_back(make_pair(A, C));
        }

        cout << dijkstra(roads, N) << endl;
    }
}
