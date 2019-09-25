#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using std::min;
using std::setw;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

void search(vector<vector<int> >& postions, vector<int>& pos, vector<vector<int> >& vis, int cur, int init_row, int init_col){
    if(cur==9){
        postions.push_back(pos);
        return;
    }
    if(cur==init_col){
        search(postions, pos, vis, cur+1, init_row, init_col);
    }else{ //一定要是else，否则返回到init_col那行后，会再次搜索
        for(int i=1; i<pos.size(); ++i){
            //判断（i，cur）所在斜线有没有皇后
            bool slash = true;
            for(int j=1; j<min(i, cur); ++j){
                if(vis.at(i-j).at(cur-j)){
                    slash = false;
                    goto has_row;
                }
            }
            for(int j=1; j<min(9-i, cur); ++j){
                if(vis.at(i+j).at(cur-j)){
                    slash = false;
                    goto has_row;
                }
            }
            if(cur<init_col){
                if(abs(i-init_row)==abs(cur-init_col)){
                    slash = false;
                    goto has_row;
                }
            }
        has_row:
            //判断（i，cur）所在行有没有皇后
            bool has_row(true);
            for(int j=1; j<9; ++j){
                if(vis.at(i).at(j)){
                    has_row = false;
                    goto flag;
                }
            }
            if(cur<init_col){
                if(i==init_row){
                    has_row = false;
                }
            }
        flag:
            if(slash && has_row){
                pos.at(cur) = i;
                vis.at(i).at(cur) = 1;
                search(postions, pos, vis, cur+1, init_row, init_col);
                pos.at(cur) = 0;
                vis.at(i).at(cur) = 0;
            }
        }
    }
}

int main(){
    int num_datasets;
    cin >> num_datasets;
    while(num_datasets--){
        cin.get();
        vector<vector<int> > vis(9, vector<int>(9, 0));
        vector<int> pos(9, 0);
        int row, col;
        cin >> row >> col;
        vis.at(row).at(col) = 1;
        pos.at(col) = row;
        vector<vector<int> > res;
        search(res, pos, vis, 1, row, col);
        cout << "SOLN       " << "COLUMN\n";
        cout << " #      1 2 3 4 5 6 7 8\n\n";
        for(int i=0; i<res.size(); ++i){
            cout << setw(2) << i+1;
            cout << "     ";
            for(int j=1; j<res.at(i).size(); ++j){
                cout << ' ' << res.at(i).at(j);
            }
            cout << '\n';
        }
        if(num_datasets!=0){
            cout << endl;
        }
    }
}
