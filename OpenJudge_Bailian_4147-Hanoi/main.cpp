#include <iostream>
#include <cstring>
#include <cfloat>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <map>
#include <numeric>
#include <climits>

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

int n;

//把i个盘子借助y从x移到z
void move(char x, char y, char z, int i){
    if(i==0) return;
    move(x, z, y, i-1);
    cout << i << ":" << x << "->" << z << endl;
    move(y, x, z, i-1);
}

int main() {
    char a, b, c;
    cin >> n >> a >> b >> c;
    move(a, b, c, n);//借助b把n个盘子从a移到c
}
