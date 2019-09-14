#include <iostream>
#include <queue>

using std::queue;
using std::cout;
using std::cin;
using std::endl;

int main(){
	int n;
	while(cin>>n){
		if(n==0) break;
		queue<int> q;
		for(int i=1; i<=n; ++i){
			q.push(i);
		}
		cout << "Discarded cards:";
		while(static_cast<int>(q.size())>2){
			cout << " " << q.front() << ",";
			q.pop();
			q.push(q.front());
			q.pop();
		}
		if(static_cast<int>(q.size())==2){
			cout << " " << q.front() << endl;
			q.pop();
			cout << "Remaining card: " << q.front() << endl;
		}else{
			cout << "\n" << "Remaining card: " << q.front() << endl;
		}
	}
}
