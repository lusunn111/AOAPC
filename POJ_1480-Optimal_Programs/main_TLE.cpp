#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>

using std::abs;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::queue;
using std::stack;

enum ops{ADD, DIV, DUP, MUL, SUB};

bool add(stack<int>& operand){
    if(1==operand.size()){
        return false;
    }
    int a = operand.top();
    operand.pop();
    int b = operand.top();
    operand.pop();
    if(abs(a+b)>30000){
        operand.push(b);
        operand.push(a);
        return false;
    }
    operand.push(a+b);

    return true;
}

bool sub(stack<int>& operand){
    if(1==operand.size()){
        return false;
    }
    int a = operand.top();
    operand.pop();
    int b = operand.top();
    operand.pop();
    if(abs(b-a)>30000){
        operand.push(b);
        operand.push(a);
        return false;
    }
    operand.push(b-a);

    return true;
}

bool mul(stack<int>& operand){
    if(1==operand.size()){
        return false;
    }
    int a = operand.top();
    operand.pop();
    int b = operand.top();
    operand.pop();
    if(abs(a*b)>30000){
        operand.push(b);
        operand.push(a);
        return false;
    }
    operand.push(a*b);

    return true;
}

bool div(stack<int>& operand){
    if(1==operand.size()){
        return false;
    }
    int a = operand.top();
    operand.pop();
    if(0==a){
        operand.push(a);
        return false;
    }
    int b = operand.top();
    operand.pop();
    //貌似这个判断多余，b/a不可能大于30000
    if(abs(b/a)>30000){
        operand.push(b);
        operand.push(a);
        return false;
    }
    operand.push(b/a);

    return true;
}

bool dup(stack<int>& operand){
    operand.push(operand.top());

    return true;
}

#if 0
//这种方法是将所有operators全部确定后再计算operands，再判断，较慢，还是应该每确定一个operator就计算一下operands，回溯时的恢复只要再每一层dfs复制一个operands就ok
bool operRun(vector<stack<int> >& operands, const vector<ops>& operators){
    for(int i=0; i<operators.size(); ++i){
        for(int j=0; j<operands.size(); ++j){
            switch (operators.at(i)){
                case ADD:
                    if(!add(operands.at(j))){
                        return false;
                    }
                    break;
                case DIV:
                    if(!div(operands.at(j))){
                        return false;
                    }
                    break;
                case DUP:
                    if(!dup(operands.at(j))){
                        return false;
                    }
                    break;
                case MUL:
                    if(!mul(operands.at(j))){
                        return false;
                    }
                    break;
                case SUB:
                    if(!sub(operands.at(j))){
                        return false;
                    }
                    break;
            }
        }
    }
    return true;
}

bool time2finish(vector<stack<int> > operands, const vector<ops>& operators, const vector<int>& ys){
    if(!operRun(operands, operators)){
        return false;
    }
    //最后只能有一个操作数
    if(operands.at(0).size()>1) return false;

    for(int i=0; i<operands.size(); ++i){
        if(operands.at(i).top() != ys.at(i)){
            return false;
        }
    }

    return true;
}


bool dfs(const vector<stack<int> >& operands, vector<ops>& operators, const vector<int>& ys, int cur, const int len){
    if(cur==len){
        return time2finish(operands, operators, ys);
    }
    for(int i=0; i<5; ++i){
        operators.push_back(ops(i));
        if(dfs(operands, operators, ys, cur+1, len)){
            return true;
        }else{
            operators.erase(operators.begin()+cur+1);
        }
    }
    return false;
}
#endif

bool operRun(vector<stack<int> >& operands, ops op){
    for(int j=0; j<operands.size(); ++j){
        switch (op){
            case ADD:
                if(!add(operands.at(j))){
                    return false;
                }
                break;
            case DIV:
                if(!div(operands.at(j))){
                    return false;
                }
                break;
            case DUP:
                if(!dup(operands.at(j))){
                    return false;
                }
                break;
            case MUL:
                if(!mul(operands.at(j))){
                    return false;
                }
                break;
            case SUB:
                if(!sub(operands.at(j))){
                    return false;
                }
                break;
        }
    }

    return true;
}

bool time2finish(const vector<stack<int> >& operands, const vector<int>& ys){
    //最后只能有一个操作数
    if(operands.at(0).size()>1) return false;

    for(int i=0; i<operands.size(); ++i){
        if(operands.at(i).top() != ys.at(i)){
            return false;
        }
    }

    return true;
}

bool dfs(vector<stack<int> >& operands, vector<ops>& operators, const vector<int>& ys, int cur, const int len){
    if(cur==len){
        return time2finish(operands, ys);
    }
    vector<stack<int> > operands_copy(operands);
    for(int i=0; i<5; ++i){
        operators.push_back(ops(i));
        if(!operRun(operands, ops(i))){
            operators.erase(operators.begin()+cur);
            continue;
        }
        if(dfs(operands, operators, ys, cur+1, len)){
            return true;
        }else{
            operators.erase(operators.begin()+cur);
            operands = operands_copy;
        }
    }
    return false;
}

//TLE
int main(){
    int n;
    int cnt(0);
    while(cin>>n){
        if(0==n) break;
        ++cnt;

        //load inputs
        int x;
        vector<stack<int> > xs;
        vector<int> ys(n, 0);
        for(int i=0; i<n; ++i){
            cin >> x;
            stack<int> temp;
            temp.push(x);
            xs.push_back(temp);
        }
        for(int i=0; i<n; ++i){
            cin >> ys.at(i);
        }

        //Empty sequence case.
        bool empty_sequence(true);
        for(int i=0; i<n; ++i){
            if(xs.at(i).top() != ys.at(i)){
                empty_sequence = false;
                break;
            }
        }
        if(empty_sequence){
            cout << "Program " << cnt << "\nEmpty sequence\n" << endl;
            continue;
        }

        vector<ops> operators;

        //因为此题规定了最长操作长度，所以可以从小到大遍历各种长度，用dfs将各种长度的操作全排列，从而找到最短操作
        int i;
        for(i=1; i<=10; ++i){
            operators.clear();
            //the first operator must be DUP
            if(dfs(xs, operators, ys, 0, i)){
                break;
            }
        }
        if(i==11){
            cout << "Program " << cnt << "\nImpossible\n" << endl;
            continue;
        }

        cout << "Program " << cnt << "\n";
        for(int i=0; i<operators.size(); ++i){
            switch (operators.at(i)){
                case ADD:
                    cout << "ADD";
                    break;
                case DIV:
                    cout << "DIV";
                    break;
                case DUP:
                    cout << "DUP";
                    break;
                case MUL:
                    cout << "MUL";
                    break;
                case SUB:
                    cout << "SUB";
                    break;
            }
            if(i==operators.size()-1){
                cout << '\n' << endl;
            }else{
                cout << ' ';
            }
        }
    }
}
