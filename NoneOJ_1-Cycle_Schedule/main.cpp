#include <iostream>
#include <vector>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

void schedule(int k, vector<vector<int> >& sch){
    if(k==0){
        sch.at(k).at(k) = 1;
        return;
    }else{
        schedule(k-1, sch);
        int p = static_cast<int>(std::pow(2, k-1));
        for(int i=0; i<p; ++i){
            for(int j=0; j<p; ++j){
                sch.at(p+i).at(j) = sch.at(i).at(j) + p;
            }
        }
        for(int i=0; i<p; ++i){
            for(int j=0; j<p; ++j){
                sch.at(i).at(p+j) = sch.at(i).at(j) + p;
                sch.at(p+i).at(p+j) = sch.at(i).at(j);
            }
        }
    }
}

int main(){
    int k;
    while(cin>>k){
        int dims = static_cast<int>(std::pow(2, k));
        vector<vector<int> > sch(dims, vector<int>(dims, 0));
        schedule(k, sch);
        for(int i=0; i<sch.size(); ++i){
            for(int j=0; j<sch.at(i).size(); ++j){
                cout << sch.at(i).at(j) << ' ';
            }
            cout << endl;
        }
    }
}
