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
#include <pthread.h>

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

constexpr double INF = DBL_MAX;

//prime算法：选择一个起始点，每次从所有已选点的一步可达点中选择最短的路
double prim(vector<vector<double> >& matrix, int num_of_points){
    vector<int> res;
    double weight(0);
    //weights[i]表示的是从已经选择了的任一个点到第i号点的最小距离
    vector<double> weights(num_of_points, -1.0);

    int start=0;
    //选择第一个点
    res.emplace_back(0);
    //初始化权重
    for(int i=0; i<num_of_points; ++i){
        weights[i] = matrix[start][i];
    }

    for(int i=0; i<num_of_points; ++i){
        if(i==start) continue;

        double min_weight(INF);
        int min_index;
        for(int j=0; j<num_of_points; ++j){
            if(!(weights[j]<1e-9) && weights[j]<min_weight){
                min_weight = weights[j];
                min_index = j;
            }
        }

        //找过的点置零，下一个点不再连到这个点
        weights[min_index] = 0;
        weight+=min_weight;
        res.emplace_back(min_index);

        //更新权重
        for(int j=0; j<num_of_points; ++j){
            if(!(weights[j]<1e-9) && matrix[min_index][j]<weights[j]){
                weights[j] = matrix[min_index][j];
            }
        }
    }
    return weight;
}

struct edge{
    int start;
    int end;
    double length;
    edge(int s, int e, double l): start(s), end(e), length(l){}
    bool operator <(const edge& e2){
        return this->length < e2.length;
    }
};

int getEnd(vector<int>& vends, int i){
    while(vends[i]!=0){
        i = vends[i];
    }
    return i;
}

//kruskal算法：每次选择所有边中的最短边，判断有没有回路
double kruskal(vector<vector<double> >& matrix, int num_of_points){
    vector<edge> edges;
    for(int i=0; i<num_of_points; ++i){
        for(int j=i+1; j<num_of_points;++j){
            edges.emplace_back(i, j, matrix[i][j]);
        }
    }
    std::sort(edges.begin(), edges.end());

    double weight;
    vector<int> vends(num_of_points, 0);//保存某个点在该最小生成树的终点
    vector<edge> res;
    for(int i=0; i<edges.size(); ++i){
        edge e = edges[i];
        int m = getEnd(vends, e.start);
        int n = getEnd(vends, e.end);
        if(m!=n){
            res.push_back(e);
            weight += e.length;
            vends[m] = n;//将两个终点连接
        }
    }
    return weight;
}

int main(){
    int T;//测试用例数
    cin >> T;
    while(T--){
        cin.get();
        int num_of_points;
        cin >> num_of_points;

        vector<double> x(num_of_points, 0.0);
        vector<double> y(num_of_points, 0.0);
        //邻接矩阵
        vector<vector<double> > matrix(num_of_points, vector<double>(num_of_points, INF));

        //读取坐标
        for(int i=0; i<num_of_points; ++i){
            cin >> x[i] >> y[i];
        }

        //建邻接矩阵
        for(int i=0; i<num_of_points; ++i){
            for(int j=0; j<num_of_points; ++j){
                matrix[i][j] = std::sqrt(std::pow((x[i]-x[j]),2)+std::pow((y[i]-y[j]), 2));
            }
        }

        //double res = prim(matrix, num_of_points);
        double res = kruskal(matrix, num_of_points);
        cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) << res << endl;
        if(T!=0){
            cout << endl;
        }
    }
}
