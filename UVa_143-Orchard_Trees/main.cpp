#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::ceil;
using std::floor;
using std::min;
using std::max;
using std::setw;
using std::fabs;

class Solution{
public:
	double directedArea(double x1, double y1, double x2, double y2, double x3, double y3){
	    double area = 1.0/2*(x1*y2+x2*y3+x3*y1-x3*y2-x2*y1-x1*y3);
		return fabs(area);
	}
};

int main(){
	Solution s;
	double x1(0.0), y1(0.0), x2(0.0), y2(0.0), x3(0.0), y3(0.0);
	while(cin>>x1>>y1>>x2>>y2>>x3>>y3){
	    if(x1<1e-6&&x2<1e-6&&x3<1e-6&&y1<1e-6&&y2<1e-6&&y3<1e-6){
	        break;
	    }
		double area_all = s.directedArea(x1, y1, x2, y2, x3, y3);
		int x_min(ceil(min({x1, x2, x3}))), x_max(floor(max({x1, x2, x3}))), y_min(ceil(min({y1, y2, y3}))), y_max(floor(max({y1, y2, y3})));
		//trees are from range 1 to 99
		if(x_min<1e-6) x_min = 1.0;
		if(fabs(x_max-100)<1e-6) x_max=99.0;
        if(y_min<1e-6) y_min = 1.0;
        if(fabs(y_max-100)<1e-6) y_max=99.0;
		int count(0);
		for(int x=x_min; x<=x_max; ++x){
		    for(int y=y_min; y<=y_max; ++y) {
                double area1 = s.directedArea(x, y, x1, y1, x2, y2);
                double area2 = s.directedArea(x, y, x1, y1, x3, y3);
                double area3 = s.directedArea(x, y, x2, y2, x3, y3);
                if (fabs(area1+area2+area3-area_all)<1e-6) {
                    ++count;
                }
            }
		}
		cout << setw(4) << count << endl;
	}
}
