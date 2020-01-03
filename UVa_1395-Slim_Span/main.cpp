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

const int MAX_N = 110;
const int MAX_M = (MAX_N - 1)*MAX_N / 2;

struct edge{
    int from, to , weight;
    bool operator < (const edge& rhs) const {
        return weight < rhs.weight;
    }
}edges[MAX_M];

int n, m;//num of vertices, num of edges
int a, b, w;
int fa[MAX_N];
int e_count;
int min_weight;
int max_weight;
int min_slimness;

void buildEdges(){
    for(int e=0; e<m; ++e){
        cin >> a >> b >> w;
        edges[e].from = a;
        edges[e].to = b;
        edges[e].weight = w;
    }
}

int findRoot(int x){
    while(fa[x]!=x){
        x = fa[x];
    }
    return x;
}

void kruskal(int start_edge){
    //initial,节点号[1,n]
    for(int i=1; i<=n; ++i){
        fa[i] = i;
    }

    for(int e=start_edge; e<m; ++e){
        int s = findRoot(edges[e].from);
        int t = findRoot(edges[e].to);
        //添加边e后没有形成环
        if(s!=t){
            fa[s] = t;
            ++e_count;
            max_weight = std::max(max_weight, edges[e].weight);
        }
    }
}

int main(){
    int k=0;
    while(cin >> n >> m && (n || m)){
        ++k;
        memset(edges, 0, sizeof(edges));
        buildEdges();
        std::sort(std::begin(edges), std::begin(edges)+m);

        min_slimness = INT_MAX;

        for(int e=0; e<m; ++e){
            min_weight = edges[e].weight;
            max_weight = 0;
            e_count = 0;
            kruskal(e);
            if(e_count==n-1)
                min_slimness = std::min(min_slimness, max_weight-min_weight);
        }

        if(min_slimness==INT_MAX) cout << -1 << endl;
        else cout << min_slimness << endl;
    }
}
