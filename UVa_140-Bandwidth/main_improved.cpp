#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>
#include <map>

using std::map;
using std::vector;
using std::string;
using std::max;
using std::min;
using std::stringstream;
using std::cout;
using std::cin;
using std::endl;
using std::getline;

void searchMinBW(string& res, string& permutation, string& nodes, vector<vector<bool> >& graph, map<char, bool>& vis, int cur, int& bw){
    if(cur == nodes.size()){
        int cur_bw(0);
        for(int i=0; i<permutation.size(); ++i){
            int node_pos_1 = i;
            //x是permutation[i]在graph中的坐标
            int x = find(nodes.begin(), nodes.end(), permutation.at(i)) - nodes.begin();
            int max_distance(0);
            for(int j=0; j<nodes.size(); ++j){
                if(graph.at(x).at(j)){
                    int node_pos_2 = find(permutation.begin(), permutation.end(), nodes.at(j)) - permutation.begin();
                    max_distance = max(max_distance, abs(node_pos_1 - node_pos_2));
                }
            }
            cur_bw = max(max_distance, cur_bw);
        }
        if(cur_bw < bw){
            res = permutation;
            bw = cur_bw;
            return;
        }
    }
    for(int i=0; i<nodes.size(); ++i){
        if(!vis.at(nodes.at(i))){
            permutation.at(cur) = nodes.at(i);
            vis.at(nodes.at(i)) = true;

            int cur_distance(0);
            for(int j=0; j<cur; ++j){
                int x = find(nodes.begin(), nodes.end(), permutation.at(j)) - nodes.begin();
                if(graph.at(i).at(x)){
                    cur_distance = max(cur_distance, cur-j);
                }
            }
            if(cur_distance>bw){
                permutation.at(cur) = ' ';
                vis.at(nodes.at(i)) = false;
                continue;
            }

            int undefined_neighbor_nodes(0);
            for(int j=0; j<vis.size(); ++j){
                if(graph.at(i).at(j) && !vis.at(nodes.at(j))){
                    ++undefined_neighbor_nodes;
                }
            }
            if(undefined_neighbor_nodes>bw){
                permutation.at(cur) = ' ';
                vis.at(nodes.at(i)) = false;
                continue;
            }

            searchMinBW(res, permutation, nodes, graph, vis, cur+1, bw);
            vis.at(nodes.at(i)) = false;
            permutation.at(cur) = ' ';
        }
    }
}

int main(){
    string line;
    while(getline(cin, line)){
        if(line=="#") break;

        //读取数据并制图
        stringstream ss_line(line);
        vector<string> keys;
        vector<string> values;
        string block;
        string nodes;
        while(getline(ss_line, block, ';')){
            stringstream ss_block(block);
            string key;
            string value;
            getline(ss_block, key, ':');
            getline(ss_block, value, ':');
            keys.push_back(key);
            values.push_back(value);
            if(find(nodes.begin(), nodes.end(), key.at(0)) == nodes.end()){
                nodes.push_back(key[0]);
            }
            for(int i=0; i<value.size(); ++i){
                if(find(nodes.begin(), nodes.end(), value.at(i)) == nodes.end()){
                    nodes.push_back(value.at(i));
                }
            }
        }
        sort(nodes.begin(), nodes.end());
        map<char, bool> vis;
        for(int i=0; i<nodes.size(); ++i){
            vis.insert({nodes.at(i), false});
        }
        vector<vector<bool> > graph(nodes.size(), vector<bool>(nodes.size(), false));
        for(int i=0; i<keys.size(); i++){
            int x = find(nodes.begin(), nodes.end(), keys.at(i).at(0)) - nodes.begin();
            for(int j=0; j<values.at(i).size(); ++j){
                int y = find(nodes.begin(), nodes.end(), values.at(i).at(j)) - nodes.begin();
                graph.at(x).at(y) = true;
                graph.at(y).at(x) = true;
            }
        }
        string res;
        string permutation(nodes.size(), ' ');
        int bw(INT_MAX);
        //graph的坐标顺序对应的是nodes
        searchMinBW(res, permutation, nodes, graph, vis, 0, bw);
        for(int i=0; i<res.size(); ++i){
            cout << res.at(i) << ' ';
        }
        cout << "-> " << bw << endl;
    }
}
