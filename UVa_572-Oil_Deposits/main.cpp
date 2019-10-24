#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

class Solution{
public:
    void dfs(vector<vector<char> >& regions, vector<vector<bool> >& vis, int x, int y){
        if(vis.at(x).at(y) || regions.at(x).at(y) == '*') return;
        vis.at(x).at(y) = true;
        dfs(regions, vis, x-1, y);
        dfs(regions, vis, x+1, y);
        dfs(regions, vis, x-1, y-1);
        dfs(regions, vis, x, y-1);
        dfs(regions, vis, x+1, y-1);
        dfs(regions, vis, x-1, y+1);
        dfs(regions, vis, x, y+1);
        dfs(regions, vis, x+1, y+1);
    }
};

int main(){
    int m(0), n(0);
    while(cin>>m>>n){
        if(m==0||0==n) break;
        vector<vector<char> > regions;
        vector<vector<bool> > vis;
        for(int i=0; i<m+2; ++i){
            vector<char> regions_temp;
            vector<bool> vis_temp;
            for(int j=0; j<n+2; ++j){
                if(i==0||i==m+1||j==0||j==n+1){
                    regions_temp.push_back('*');
                    vis_temp.push_back(false);
                }
                else{
                    char ch = cin.get();
                    if(ch=='\n') ch = cin.get();
                    regions_temp.push_back(ch);
                    vis_temp.push_back(false);
                }
            }
            regions.push_back(regions_temp);
            vis.push_back(vis_temp);
        }
        int count(0);
        Solution s;
        for(int i=1; i<m+1; ++i){
            for(int j=1; j<n+1; ++j){
                if(regions.at(i).at(j)=='@' && !vis.at(i).at(j)){
                    ++count;
                    s.dfs(regions, vis, i, j);
                }
            }
        }
        cout << count << endl;
    }
}
