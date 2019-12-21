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

int Bellman_Ford(vector<list<pair<int, int>>>& roads, int N){
    vector<int> d(N+1, INT_MAX);
    d[1] = 0;
    //不含环的最短路径最多包含N-1个节点（不含起点）
    //首先算出到每个点的不含环的最短路径
    vector<bool> inq(N+1, false);
    vector<int> inq_times(N+1, 0);
    std::queue<int> q;
    q.push(1);
    inq[1] = true;
    inq_times[1] += 1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        inq[u] = false;
        for(list<pair<int, int>>::iterator iter=roads[u].begin(); iter!=roads[u].end(); ++iter){
            if(d[u]!=INT_MAX && d[u]+iter->second < d[iter->first]){
                d[iter->first] = d[u]+iter->second;
                if(!inq[iter->first]){
                    q.push(iter->first);
                    inq[iter->first] = true;
                    inq_times[iter->first] += 1;
                    //入队次数超限，存在负环
                    if(inq_times[iter->first] > N){
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

int main(){
    int F;
    cin >> F;
    while(F--){
        //建边
        int N, M, W;
        cin >> N >> M >> W;
        int S, E, T;
        vector<list<pair<int, int>>> roads(N+1);
        for(int i=0; i<M; ++i){
            cin >> S >> E >> T;
            roads[S].push_back(make_pair(E, T));
            roads[E].push_back(make_pair(S, T));
        }
        for(int i=0; i<W; ++i){
            cin >> S >> E >> T;
            roads[S].push_back(make_pair(E, -1*T));
        }

        int flag = Bellman_Ford(roads, N);
        if(flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
