#include <iostream>
#include <cmath>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::exp;
using std::sin;
using std::cos;
using std::tan;

int main() {
    int p, q, r, s, t, u;
    while(cin >> p >> q >> r >> s >> t >> u){
        double i(0), j(10000);
        double max = p*exp(0) + q*sin(0) + r*cos(0) + s*tan(0) + t*0*0 + u;
        double min = p*exp(-1) + q*sin(1) + r*cos(1) + s*tan(1) + t*1*1 + u;
        if(min>0 || max<0){
            cout << "No solution" << endl;
            continue;
        }
        double x;
        while(j-i>1e-5){
            double m = (i+j)/2;
            x = m/10000;
            double res = p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
            if(res>0){
                i = m;
            }else if(res<0){
                j = m;
            }
        }
        cout << std::fixed << std::setprecision(4) << x << endl;
    }
}
