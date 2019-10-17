#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>

using std::max;
using std::min;
using std::sort;
using std::stringstream;
using std::string;
using std::getline;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

//一开始没有考虑C:Z这种空缺某些字母的情况，导致graph等等的空间都是26的，大大浪费时间和空间。
void searchBW(string& res, string& permutation, vector<vector<bool> >& graph, vector<bool>& vis, vector<bool>& exist, int num_nodes, int cur, int& bw){
    //此题其实就是对每个permutation算BW，只不过在寻找permutation的过程中可以剪枝
    //此题就是全排列，只不过不需要将所有排列放入一个vector，而是找出符合题目要求的那个排列
    if(cur==num_nodes){
        int cur_bw(0);
        for(int i=0; i<permutation.size(); ++i){
            //对每一个节点的neighbor
            int max_distance(0);
            for(int j=0; j<26; ++j){
                if(exist.at(j) && graph.at(permutation.at(i)-'A').at(j)){
                    int k = find(permutation.begin(), permutation.end(), 'A'+j) - permutation.begin();
                    max_distance = max(max_distance, abs(i-k));
                }
            }
            cur_bw = max(max_distance, cur_bw);
        }
        if(cur_bw < bw){
            res = permutation;
            bw = cur_bw;
        }
        return;
        //完成之后怎么办？
    }
    for(int i=0; i<26; ++i) {
        if(exist.at(i) && !vis.at(i)){
            permutation.at(cur) = 'A'+i;
            vis.at(i) = true;

            //如果当前串的最小带宽已经大于之前找到的最小带宽，则把当前枝剪掉。
            //只需要检测最近添加的那个点与其他点的距离，因为更前面的点在此层递归之上已经检测过了。
            int cur_distance(INT_MIN);
            for(int j=0; j<26; ++j){
                if(graph.at(i).at(j) && (find(permutation.begin(), permutation.end(), 'A'+j)!=permutation.end())){
                    int k = find(permutation.begin(), permutation.end(), 'A'+j) - permutation.begin();
                    cur_distance = max(cur_distance, abs(cur-k));
                }
            }
            if(cur_distance>bw) {
                vis.at(permutation.at(cur)-'A') = false;
                permutation.at(cur) = ' ';
                //换一个当前字符，而不是return到上一层
                continue;
            }

            //如果最近添加的节点的所有未定义位置的neighbor节点数量大于min_bw，当前枝也要剪掉。
            //因为未定义的neighbor全部紧跟当前节点是最理想情况，如果它都大于min_bw，那当前枝就没什么意义了。
            int undefined_neighbor(0);
            for(int j=0; j<26; ++j){
                if(exist.at(i) && graph.at(i).at(j) && !vis.at(j)){
                    ++undefined_neighbor;
                }
            }
            if(undefined_neighbor>=bw) {
                vis.at(permutation.at(cur)-'A') = false;
                permutation.at(cur) = ' ';
                continue;
            }

            searchBW(res, permutation, graph, vis, exist, num_nodes, cur+1, bw);
            vis.at(permutation.at(cur)-'A') = false;
            permutation.at(cur) = ' ';
        }
    }
}

int main(){
    string line;
    while(getline(cin, line)){
        if(line=="#") break;

        //读取数据
        vector<vector<bool> > graph(26, vector<bool>(26, false));
        vector<bool> exist(26, false);
        stringstream ss_line(line);
        string nodes;
        while(getline(ss_line, nodes, ';')){
            stringstream ss_nodes(nodes);
            string node, neighbor_nodes;
            getline(ss_nodes, node, ':');
            getline(ss_nodes, neighbor_nodes);
            exist.at(node.at(0)-'A') = true;
            for(int i=0; i<neighbor_nodes.size(); ++i){
                exist.at(neighbor_nodes.at(i)-'A') = true;
                graph.at(node.at(0)-'A').at(neighbor_nodes.at(i)-'A') = true;
                graph.at(neighbor_nodes.at(i)-'A').at(node.at(0)-'A') = true;
            }
        }
        int num_nodes(0);
        for(int i=0; i<exist.size(); ++i){
            if(exist.at(i)){
                ++num_nodes;
            }
        }
        int bw(INT_MAX);
        string permutation(num_nodes, ' ');
        vector<bool> vis(26, false);
        string res;
        searchBW(res, permutation, graph, vis, exist, num_nodes, 0, bw);
        for(int i=0; i<res.size(); ++i){
            cout << res.at(i) << ' ';
        }
        cout << "-> " << bw << endl;
    }
}
