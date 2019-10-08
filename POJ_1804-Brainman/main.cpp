#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

void mergeSort(vector<int>& A, int l, int r, vector<int>& T, int& cnt){
	if(r-l>1){
		int m = (l+r)/2;
		mergeSort(A, l, m, T, cnt);
		mergeSort(A, m, r, T, cnt);
		int p = l, q = m, i = l;
		while(p<m || q<r){
			if(q>=r || p<m && A.at(p)<=A.at(q)){
				T.at(i++) = A.at(p++);
			}else{ //先放[m,r)内的元素到T，说明[l,m)内A[p]~A(m)都大于A[q]
				T.at(i++) = A.at(q++);
				cnt += m-p;
			}
		}
		for(int k=l; k<r; ++k){
		    A.at(k) = T.at(k);
		}
	}
}

int main(){
	int scenarios;
	cin >> scenarios;
	int scenario(0);
	while(++scenario <= scenarios){
		int N;
		cin >> N;
		vector<int> A(N);
		for(int i=0; i<N; ++i){
			cin >> A.at(i);
		}
		vector<int> T(N);
		int count(0);
		mergeSort(A, 0, N, T, count);
		cout << "Scenario #" << scenario << ":\n" << count << '\n' << endl;
	}
}
