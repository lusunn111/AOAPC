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

int findRoot(vector<int>& father, int x){
	while(fa[x]!=x){
		x = fa[x];
	}
	return x;
	/*
    if(father[x]==x){
        return x;
    }else{
        return findRoot(father, father[x]);
    }
    */
}

struct edge{
    int start;
    int end;
    int weight;
    edge(int s, int e, int w): start(s), end(e), weight(w) {}
    bool operator < (const edge& e){
        return this->weight < e.weight;
    }
};

int kruskal(vector<edge>& edges, int num_of_points){
    vector<int> father(num_of_points, 0);
    for(int i=0; i<num_of_points; ++i) {
        father[i] = i;
    }

    int weights(0);
    vector<edge> res;
    for(int i=0; i<edges.size(); ++i){
        edge e = edges[i];
        int m = findRoot(father, e.start);
        int n = findRoot(father, e.end);
        if(m!=n){
            weights += e.weight;
            res.push_back(e);
            father[m] = n; //将两棵树连接，如此连接则看出树根root的father是等于它本身没有变过，findRoot找的就是这个没有变过的条件
        }
    }
    if(res.size()!=num_of_points-1)
        return -1;
    return weights;
}

int main(){
    int N, M;//道路条数，村庄数目
    while(cin>>N>>M && N!=0){
        vector<edge> edges;
        int i, j, weight;
        for(int k=0; k<N; ++k){
            cin >> i >> j >> weight;
            edges.emplace_back(i-1, j-1, weight);
        }
        std::sort(edges.begin(), edges.end());

        int res = kruskal(edges, M);
        if(res==-1)
            cout << "?" << endl;
        else
            cout << res << endl;
    }
}
