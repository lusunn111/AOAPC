#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

struct rect{
    int length;
    int width;
};

int maxRects(vector<struct rect>& rects, vector<vector<int> >& graph, vector<int>& max_rects, int start){
    if(max_rects[start]>0) return max_rects[start];
    else{
        int sub_max = 0;
        for(int j=0; j<max_rects.size(); ++j){
            if(graph[start][j]){
                if(maxRects(rects, graph, max_rects, j)>sub_max){
                    sub_max = maxRects(rects, graph, max_rects, j);
                }
            }
        }
        return sub_max+1;
    }
}

int main() {
    int N;
    cin >> N;
    while(N--){
        int n;
        cin >> n;
        vector<struct rect> rects(n);
        for(int i=0; i<n; ++i){
            int length, width;
            cin >> length >> width;
            if(length>width){
                rects[i].length = length;
                rects[i].width = width;
            }else{
                rects[i].width = length;
                rects[i].length = width;
            }
        }

        vector<vector<int>> graph(n, vector<int>(n, 0));
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                if(rects[i].length < rects[j].length && rects[i].width < rects[j].width){
                    graph[i][j] = 1;
                }else{
                    graph[i][j] = 0;
                }
            }
        }

        vector<int> max_rects(n, 0);
        for(int i=0; i<n; ++i){
            max_rects[i] = maxRects(rects, graph, max_rects, i);
        }

        cout << *std::max_element(max_rects.begin(), max_rects.end()) << endl;
    }
}
