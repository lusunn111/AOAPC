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

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

constexpr int MAX_N = 100005;
vector<int> G[MAX_N];//邻接表
int p[MAX_N];//存放到达某城市要经过的上一城市

void clear(){
    for(int i=0; i<MAX_N; ++i){
        G[i].clear();
    }
}

//建图
void readTree(int N){
    for(int i=0; i<N-1; ++i){
        int a, b;//a,b间有路
        cin >> a >> b;
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }
}

//dfs建树
void buildTree(int S, int fa){
    int d = G[S].size();//S的相邻节点数量
    for(int i=0; i<d; ++i){
        int v = G[S][i];
        if(v!=fa){
            p[v]=S;
            buildTree(v, S);
        }
    }
}

int main(){
    int M;//用例数量
    cin >> M;
    while(M--){
        clear();
        int N, S;//城市数量，参观者所在城市编号
        cin >> N >> S;
        readTree(N);
        p[S] = -1;//起点
        buildTree(S, p[S]);
        for(int i=1; i<=N; ++i){
            cout << p[i] << ' ';
        }
        cout << endl;
    }
}
