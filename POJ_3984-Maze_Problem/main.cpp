#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>

using std::pair;
using std::make_pair;
using std::stack;
using std::queue;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

class Solution{
public:
	void bfs(vector<vector<int> >& maze, vector<vector<pair<int, int> > >& father, vector<vector<bool> >& vis){
		queue<pair<int, int> > q;
		q.push(make_pair(0, 0));
		father.at(0).at(0) = make_pair(-1, -1);
		vis.at(0).at(0) = true;
		//哪条路径最先把end的vis改为true，那么在输出时向father追溯就走的哪条路径。
		while(!q.empty()){
			int row = q.front().first;
			int col = q.front().second;
			q.pop();
			int row_up = row - 1;
			int row_down = row + 1;
			int col_left = col - 1;
			int col_right = col + 1;
			//由于保证只有一条最优解，所以先向下还是先向右并无区别。
			if(row_down>=0 && row_down<5 && !vis.at(row_down).at(col) && !maze.at(row_down).at(col)){
				q.push(make_pair(row_down, col));
				father.at(row_down).at(col) = make_pair(row, col);
				vis.at(row_down).at(col) = true;
			}
            if(col_right>=0 && col_right<5 && !vis.at(row).at(col_right) && !maze.at(row).at(col_right)){
                q.push(make_pair(row, col_right));
                father.at(row).at(col_right) = make_pair(row, col);
                vis.at(row).at(col_right) = true;
            }
            if(row_up>=0 && row_up<5 && !vis.at(row_up).at(col) && !maze.at(row_up).at(col)){
                q.push(make_pair(row_up, col));
                father.at(row_up).at(col) = make_pair(row, col);
                vis.at(row_up).at(col) = true;
            }
            if(col_left>=0 && col_left<5 && !vis.at(row).at(col_left) && !maze.at(row).at(col_left)){
                q.push(make_pair(row, col_left));
                father.at(row).at(col_left) = make_pair(row, col);
                vis.at(row).at(col_left) = true;
            }

		}
	}
};

int main(){
    Solution s;
    vector<vector<int> > maze;
    vector<vector<bool> > vis;
    for(int i=0; i<5; ++i){
        vector<int> m;
        vector<bool> v;
        for(int j=0; j<5; ++j){
            int block;
            cin >> block;
            m.push_back(block);
            v.push_back(false);
        }
        maze.push_back(m);
        vis.push_back(v);
    }
    vector<vector<pair<int, int> > > father(5, vector<pair<int, int> >(5, make_pair(0, 0)));
    s.bfs(maze, father, vis);
    stack<pair<int, int> > ans;
    pair<int, int> end = make_pair(4, 4);
    ans.push(end);
    while(father.at(end.first).at(end.second) != make_pair(-1, -1)){
        end = father.at(end.first).at(end.second);
        ans.push(end);
    }
    while(!ans.empty()){
        cout << "(" << ans.top().first << ", " << ans.top().second  << ")" << endl;
        ans.pop();
    }
}
