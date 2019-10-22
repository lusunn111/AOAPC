#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

using std::cout;
using std::cin;
using std::endl;

int seperate(std::vector<int>& books, int k){
    long long total(0);
    for(int i=0; i<books.size(); ++i){
        total += books.at(i);
    }
    long long lo(*std::min_element(books.begin(), books.end())), hi(total);
    BEG:
    while(lo<hi){
        long long mid = (lo+hi)/2;
        long long cnt(0), sum(0);
        for(int i=0; i<books.size(); ++i) {
            if (books.at(i) > mid) {
                lo = mid+1;
                goto BEG;
            }
        }
        for(int i=0; i<books.size(); ++i) {
            sum += books.at(i);
            if(sum > mid){
                sum = books.at(i);
                ++cnt;
            }
        }
        if(cnt+1 > k){
            lo = mid+1;
        }else{
            hi = mid;
        }
    }

    return hi;
}

void print(std::vector<int> books, int k, int group){
    long long sum(0);
    int cnt(1);
    std::set<int> slash_ind;
    //If there is more than one solution, print the one that minimizes the work assigned to the first scriber,
    //then to the second scriber etc. But each scriber must be assigned at least one book.
    for(int i=books.size()-1; i>=0; --i){
        sum += books.at(i);
        if(sum > group) {
            sum = books.at(i);
            ++cnt;
            slash_ind.insert(i);
        }
        if(k-cnt == i+1){
            for(int j=0; j<=i; j++){
                slash_ind.insert(j);
            }
            break;
        }
    }
    for(int i=0; i<books.size(); ++i){
        cout << books.at(i);
        if(i!=books.size()-1) cout << " ";
        if(slash_ind.count(i)) cout << "/ ";
    }
    cout << endl;
}



int main() {
    int N;
    cin >> N;
    while(N--){
        int m, k;
        cin >> m >> k;
        std::vector<int> books(m);
        for(int i=0; i<m; ++i){
            cin >> books.at(i);
        }
        int group = seperate(books, k);
        print(books, k, group);
    }
}
