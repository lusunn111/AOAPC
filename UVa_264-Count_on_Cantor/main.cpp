#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Solution{
public:
    void findKthNumber(int order){
        int i(1);
        while(1){
            int nums = (1+i)*i/2;
            if(nums>order)
                break;
            ++i;
        }
        int numerator(0);//分子
        int denominator(0);//分母
        int nums = (1+i-1)*(i-1)/2;
        if(nums == order){
            i -= 1;
            nums = (1+i-1)*(i-1)/2;
        }
        if(i%2){
            denominator = order - nums;
            numerator = i + 1 - denominator;
        }else{
            numerator = order - nums;
            denominator = i + 1 - numerator;
        }
        cout << "TERM " << order << " IS " << numerator << "/" << denominator << endl;
    }
};

int main(){
    Solution s;
    int order;
    while(cin >> order){
        s.findKthNumber(order);
    }
}
