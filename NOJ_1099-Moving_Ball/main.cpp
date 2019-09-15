#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

int main() {
    int num_of_nodes;
    int num_of_operations;
    while(cin >> num_of_nodes >> num_of_operations){
        //球不动，变的只是球的pre和next指向的球号
        vector<int> pre;
        vector<int> next;
        pre.push_back(-1);
        for(int i=0;i<=num_of_nodes;++i){
            pre.push_back(i);
            next.push_back(i+1);
        }
        next.push_back(-1);
        while(num_of_operations--){
            char oper;
            int move_node;
            int dest_node;
            cin >> oper >> move_node >> dest_node;
            //得到要删除的球的左边球的球号
            int l = pre[move_node], r = next[move_node];
            //此处看出必须要有0号球，否则很难找到开始位置，有0则next[0]就是头
            next[l] = r, pre[r] = l;
            if(oper=='A'){
                l = pre[dest_node], r = dest_node;
            }else if(oper=='B'){
                l = dest_node, r = next[dest_node];
            }
            next[l] = move_node, pre[r] = move_node;
            pre[move_node] = l, next[move_node] = r;
        }
        cout << next[0];
        for(int j=next[next[0]]; j>=1&&j<=num_of_nodes;j=next[j]){
            cout << " " << j;
        }
        cout << endl;
    }
}

/* STL implemented, TLE
#include <iostream>
#include <list>

using std::list;
using std::cout;
using std::cin;
using std::endl;

class Solution{
public:
	void moveBall(list<int>& balls, char oper, int move_node, int dest_node){
		if(oper=='A'){
			for(auto iter=balls.begin(); iter!=balls.end(); ++iter){
				if(*iter==move_node){
					balls.erase(iter);
                    break;
				}
			}
			for(auto iter=balls.begin(); iter!=balls.end(); ++iter){
                if(*iter==dest_node){
                    balls.insert(iter, move_node);
                    break;
                }
			}
		}else if(oper='B'){
            for(auto iter=balls.begin(); iter!=balls.end(); ++iter){
                if(*iter==move_node){
                    balls.erase(iter);
                    break;
                }
            }
            for(auto iter=balls.begin(); iter!=balls.end(); ++iter) {
                if(*iter==dest_node){
                    balls.insert(++iter, move_node);
                    break;
                }
            }
//            不要在删除了一个元素之后继续用同一个iter遍历，会出错，因为容器已经变了
//			int operations(0);
//			for(auto iter=balls.begin(); iter!=balls.end(); ++iter){
//				if(*iter==move_node){
//					balls.erase(iter);
//					++operations;
//					if(operations==2) break;
//				}
//				if(*iter==dest_node){
//					balls.insert(++iter, move_node);
//					++operations;
//					if(operations==2) break;
//				}
//			}
		}
	}
};

int main(){
	int num_of_nodes;
	int num_of_operations;
	while(cin >> num_of_nodes >> num_of_operations){
		Solution s;
		char oper;
		int move_node;
		int dest_node;
		list<int> balls;
		for(int i=0; i<num_of_nodes; ++i){
			balls.push_back(i+1);
		}
		while(num_of_operations){
			cin >> oper >> move_node >> dest_node;
			s.moveBall(balls, oper, move_node, dest_node);
			--num_of_operations;
		}
		cout << *(balls.begin());
		for(auto iter=++balls.begin(); iter!=balls.end(); ++iter){
			cout << " " << *iter;
		}
		cout << endl;
	}
}*/
