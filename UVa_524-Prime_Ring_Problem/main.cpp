#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

bool isPrime(int num){
    for(int i=2; i<num; ++i){
        if(!(num%i)){
            return false;
        }
    }
    return true;
}

void search(vector<vector<int> >& rings, vector<int>& ring, vector<bool>& vis, int cur, int n){
    if(cur==n-1 && isPrime(ring.back()+ring.front())){
        rings.push_back(ring);
        return;
    }
    for(int i=2; i<=n; ++i){
        if(!vis.at(i-1) && isPrime(ring.back()+i)){
            ring.push_back(i);
            vis.at(i-1) = true;
            search(rings, ring, vis, cur+1, n);
            ring.erase(ring.end()-1);
            vis.at(i-1) = false;
        }
    }
}

int main(){
    int n;
    int cnt(0);
    while(cin >> n){
        if(cnt>0) cout << '\n';
        ++cnt;
        vector<vector<int> > rings;
        vector<int> ring{1};
        vector<bool> vis(n, false);
        //1已经被放入最前面
        vis.at(0) = true;
        search(rings, ring, vis, 0, n);
        cout << "Case " << cnt << ":\n";
        for(int i=0; i<rings.size(); ++i){
            cout << rings.at(i).at(0);
            for(int j=1; j<rings.at(i).size(); ++j){
                cout << ' ' << rings.at(i).at(j);
            }
            cout << endl;
        }
    }
}
