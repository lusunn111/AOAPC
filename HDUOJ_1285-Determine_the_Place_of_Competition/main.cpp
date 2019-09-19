#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using std::greater;//<functional>
using std::priority_queue;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

class Solution{
public:
    /*
    //直接法：由前向后每次输出一个入度为0的点
	vector<int> topSort(vector<vector<int> >& adjac_list, vector<int>& in_degree){
		vector<int> ans;
        for(int i=1; i<in_degree.size(); ++i){
            int k = 1;
            while(in_degree[k] != 0) ++k;
            in_degree.at(k) = -1;
            ans.push_back(k);
            for(int j=1; j<adjac_list.at(k).size(); ++j){
                if(adjac_list.at(k).at(j)){
                    --in_degree.at(j);
                }
            }
        }
		return ans;
	}
    */
    //优先队列法
    //用queue处理保证了正确的一种顺序，用priority又保证了字典序
	vector<int> topSort(vector<vector<int> >& adjac_list, vector<int>& in_degree){
        priority_queue<int, vector<int>, greater<int> > q;
        for(int i=1; i<in_degree.size(); ++i){
            if(in_degree.at(i) == 0){
                q.push(i);
            }
        }
        vector<int> ans;
        while(!q.empty()){
            int i =q.top();
            ans.push_back(i);
            q.pop();
            for(int j=1; j<adjac_list.at(i).size(); ++j){
                if(adjac_list.at(i).at(j)){
                    --in_degree.at(j);
                    //虽然j是在后面插入的，但是如果j比q中已有的小，那么就插到了它的前面，被先处理
                    if(0==in_degree.at(j)){
                        q.push(j);
                    }
                }
            }
        }
        return ans;
	}
};

int main(){
	int N, M;
	while(cin >> N >> M){
        vector<vector<int> > adjac_list(N+1, vector<int>(N+1, 0));
        vector<int> in_degree(N+1, 0);
        while(M--){
            int P1, P2;
            cin >> P1 >> P2;
            //重复边不能重复加入度（我他娘就没见过这么傻逼的，输入还有重复？题目不提醒？Debug半天）
            if(adjac_list.at(P1).at(P2))
                continue;
            adjac_list.at(P1).at(P2) = 1;
            ++in_degree.at(P2);
        }
        Solution s;
        vector<int> ans = s.topSort(adjac_list, in_degree);
        cout << ans.at(0);
        for(int i=1; i<ans.size(); ++i){
            cout <<  ' ' << ans.at(i);
        }
        cout << endl;
	}
}
