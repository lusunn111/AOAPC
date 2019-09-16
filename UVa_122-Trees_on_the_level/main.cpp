#include <iostream>
#include <string>
#include <cstdio>
#include <queue>
#include <vector>

using std::vector;
using std::queue;
using std::sscanf;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Node{
public:
	bool have_value = false;
	int value = 0;
	Node* left = nullptr;
	Node* right = nullptr;
};

bool addNode(Node* root, int value, string oper){
	Node* u = root;
	for(int i=0; i<oper.size()-1; ++i){
		if(oper[i]=='L'){
		    if(u->left){
		        u = u->left;
		    }else{
                u->left = new Node;
                u = u->left;
		    }
		}else if(oper[i]=='R'){
            if(u->right){
                u = u->right;
            }else{
                u->right = new Node;
                u = u->right;
            }
		}
	}
	//一个结点重复赋值
	if(u->have_value){
	    return false;
	}
	else{
        u->value = value;
        u->have_value = true;
        return true;
	}
}

bool bfs(vector<int>& ans, Node* root){
	queue<Node*> node_que;
    if(root->have_value){
        ans.push_back(root->value);
        node_que.push(root);
    }
    else
        return false;
    while(!node_que.empty()){
        Node* u = node_que.front();
        node_que.pop();
        if(u->left){
            node_que.push(u->left);
            if(u->left->have_value)
                ans.push_back(u->left->value);
            else
                return false;
        }
        if(u->right){
            node_que.push(u->right);
            if(u->right->have_value)
                ans.push_back(u->right->value);
            else
                return false;
        }
    }

	return true;
}

void deleteBfs(Node* root){
    queue<Node*> node_que;
    node_que.push(root);
    while(!node_que.empty()){
        Node* u = node_que.front();
        node_que.pop();
        if(u->left) node_que.push(u->left);
        if(u->right) node_que.push(u->right);
        delete u;
    }
}

int main(){
	string str;
block:
	Node* root = new Node;
    bool flag_1 = true;
	while(cin >> str){
		if(str!="()"){
			int num(0);
			//必须先分配内存在sscanf之前
			char* oper = new char;
			sscanf(str.c_str(), "(%d,%s", &num, oper);
			string oper_str = oper;
			bool flag = addNode(root, num, oper_str);
			if(!flag) flag_1 = false;
		}else{
		    if(false==flag_1){
		        cout << "not complete" << endl;
                deleteBfs(root);
		    }else{
                vector<int> ans;
                bool flag = bfs(ans, root);
                if(flag){
                    cout << ans[0];
                    for(int i=1;i<ans.size();++i){
                        cout << " " << ans.at(i);
                    }
                    cout << endl;
                }else{
                    cout << "not complete" << endl;
                }
                deleteBfs(root);
		    }
            goto block;
		}
	}
}
