#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using std::make_pair;
using std::pair;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::min;
using std::max;

class Solution{
public:
	bool ok(vector<int>& degree, int num_of_junc){
		for(int i=1; i<=num_of_junc; ++i){
			if(degree.at(i)%2){
				return false;
			}
		}
		return true;
	}
	void euler(vector<int>& ans, const vector<pair<int, int> >&roads, vector<int>& vis, const int start, const int num_of_road){
		for(int r=1; r<=num_of_road; ++r){
			if(!vis.at(r) && (roads.at(r).first==start || roads.at(r).second==start)){
				vis.at(r) = 1;
				euler(ans, roads, vis, (roads.at(r).first+roads.at(r).second-start), num_of_road);
				/*
				 * 如果是先序输出，那么针对
				 * 1 2 1
				   2 3 2
				   3 1 3
				   3 4 4
				   4 3 5
				   0 0
				   当经过路1->2->3回到点1，点1的所有路都visit过了，会回到上一级即点3继续循环，就会把4—>5添在后面，很显然是错的
				   正确的做法是后序，当回到点1，即原点，则把最后的路3压入栈，再回到上一级点3继续循环，点3作为新的起点循环完会压入最后的路5
				 */
                ans.push_back(r); //每次回到此级再添加路，回到此级了说明下一级start节点（1号节点）的路遍历完了，此级start（3号）到下一级start（1号）的路（3号路）可以添加了。
			}
		}
	}
};

int main(){
    int junction_1, junction_2, road;
	while(cin>>junction_1>>junction_2 && junction_1){
        vector<pair<int, int> > roads(2000, make_pair(0, 0));
        vector<int> degree(50, 0);
        vector<int> vis(2000, 0);
		int home = min(junction_1, junction_2);
		int num_of_road(0);
		int num_of_junc(0);
		do{
		    cin >> road;
			roads.at(road).first = junction_1;
			roads.at(road).second = junction_2;
			++degree.at(junction_1);
			++degree.at(junction_2);
			num_of_road = max(num_of_road, road);
			num_of_junc = max(num_of_junc, max(junction_1, junction_2));
		}while(cin>>junction_1>>junction_2 && junction_1);
		Solution s;
		if(!s.ok(degree, num_of_junc)){
			cout << "Round trip does not exist." << endl;
            continue;
		}
		vector<int> ans;
		s.euler(ans, roads, vis, home, num_of_road);
		for(int i=ans.size()-1; i>0; --i){
			cout << ans.at(i) << ' ';
		}
		cout << ans.at(0) << endl;
	}
}
