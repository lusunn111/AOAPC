#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

//n个叶子的二叉树一定对应一个非前缀码

void generateCode(vector<string>& codes, int len){
    if(codes.empty()){
        codes.emplace_back("0");
        codes.emplace_back("1");
        generateCode(codes, len);
    }else if(codes.size()==std::pow(2, len)){
        return;
    }else{
        vector<string> temp;
        for(string c: codes){
            temp.push_back(c+"0");
            temp.push_back(c+"1");
        }
        codes = temp;
        generateCode(codes, len);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> frequencies(n, 0);
    int c(0);
    while(c < n){
        cin >> frequencies.at(c);
        ++c;
    }
    std::sort(frequencies.begin(), frequencies.end());

    int b(0);
    int leaves(0);
    while(true){
        leaves = std::pow(2, b);
        if(leaves >= n) break;
        ++b;
    }
    int len_equ_n = (n-std::pow(2, b-1))*2;
    int len_equ_n_1 = n-len_equ_n;

    //频率小的对应长码，频率大的对应短码
    vector<string> codes;
    generateCode(codes, b-1);
    for(int i=0; i<len_equ_n; ++i){
        cout << frequencies.at(i) << ": ";
        if(!(i%2)){
            cout << codes.at(i/2)+"0" << endl;
        }else{
            cout << codes.at(i/2)+"1" << endl;
        }
    }
    for(int i=0; i<len_equ_n_1; ++i){
        cout << frequencies.at(i+len_equ_n) << ": ";
        //len_equ_n一定是偶数
        cout << codes.at(i+len_equ_n/2) << endl;
    }
}
