#include <iostream>
#include <stack>

using std::stack;
using std::cout;
using std::cin;
using std::endl;

int main() {
    int N;
    block:
    while (cin >> N) {
        if(N==0) break;
        while (true) {
            stack<int> B;
            for (int i = 0; i < N; ++i) {
                int temp;
                cin >> temp;
                if (temp == 0) {
                    cout << endl;
                    goto block;
                }
                B.push(temp);
            }
            stack<int> A;
            for (int i = N; i > 0; --i) {
                A.push(i);
            }
            stack<int> S;
            stack<int> temp;
            while (!B.empty()) {
                temp.push(B.top());
                B.pop();
            }
            while (!A.empty()) {
                S.push(A.top());
                A.pop();
                while (!S.empty()&&!temp.empty()&&S.top() == temp.top()) {
                    S.pop();
                    temp.pop();
                }
            }
            if (!S.empty()) {
                cout << "No" << endl;
            } else {
                cout << "Yes" << endl;
            }
        }
    }
}
