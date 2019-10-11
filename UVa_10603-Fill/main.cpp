#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

class state{
public:
    std::array<int, 3> fill;
    int poured;
    bool operator < (const state& p) const{
        //poured小的在队列前面
        //为什么要先处理pour小的呢？如果使用普通队列，得到的错误结果是1899 49，正确结果是1860 49,显然，为了到达49,错误结果多倒了水，而题目要求输出最少要倒的水
        //先处理小的可以保证输出最小，倒的少的状态放在queue的前面，所以如果两个状态都到达了target，那么前面的那个倒的少的肯定先处理，那么到了它程序就会break
        //而如果到不了target，closed的pour最小是通过updateAns来保证的，因为这种情况一定是处理完queue再退出
        //所以如果用普通queue，closed的情况不会出错，能到target的情况会出错
        return poured > p.poured;
    }
};

void updateAns(vector<int>& ans, const state& s){
    for(int i=0; i<3; ++i){
        int d = s.fill.at(i);
        if(ans.at(d)<0 || s.poured < ans.at(d)){
            ans.at(d) = s.poured;
        }
    }
}

void bfs(vector<vector<int> >& vis, vector<int>& ans, int a, int b, int c, int target){
    std::array<int, 3> cup = {a, b, c};
    std::priority_queue<state> q;
    state start;
    start.fill = {0, 0, c};
    start.poured = 0;
    q.push(start);
    while(!q.empty()){
        state s = q.top();
        q.pop();
        updateAns(ans, s);
        //如果达不到target，会遍历所有状态后退出
        //不会出现某到达target的状态已处理完，而后出现pour更小的到达target的状态，因为到达target的状态之后的状态的pour都是大于它的，对之处理不可能pour更小。这就是使用优先队列而不使用普通队列的原因。
        if(ans.at(target)>0) {
            break;
        }
        for(int i=0; i<3; ++i){
            for(int j=0; j<3; ++j){
                if(i==j) continue;
                if(s.fill.at(i)==0 || s.fill.at(j)==cup.at(j)) continue;
                int pour = std::min(s.fill.at(i), cup.at(j)-s.fill.at(j));
                state next=s;
                next.poured = s.poured + pour;
                next.fill.at(i) = s.fill.at(i) - pour;
                next.fill.at(j) = s.fill.at(j) + pour;
                if(!vis.at(next.fill.at(0)).at(next.fill.at(1))){
                    q.push(next);
                    vis.at(next.fill.at(0)).at(next.fill.at(1)) = 1;
                }
            }
        }
    }
    while(target>=0)
    {
        if(ans[target]>=0)
        {
            printf("%d %d\n",ans[target],target);
            return;
        }
        --target;
    }
}

int main(){
    int n;
    cin >> n;
    while(n--){
        int a, b, c, target;
        //a,b,c是容量
        cin >> a >> b >> c >> target;
        vector<vector<int> > vis(205, vector<int>(205, 0));
        vector<int> ans(205, -1);
        bfs(vis, ans, a, b, c, target);
    }
}
