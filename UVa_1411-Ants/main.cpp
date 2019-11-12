#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

struct point{
    //color == 0 represents ants, ind存放的是输入时的序号
    int x, y, ind, color;
    double angle;
    bool operator < (struct point rhs) const {
        return angle < rhs.angle;
    }
};

void match(int left, int right, vector<struct point>& points, vector<int>& res){
    if(left == right-2){
        if(points.at(left).color==0){
            res.at(points.at(left).ind) = points.at(right-1).ind;
        }else if (points.at(left).color==1){
            res.at(points.at(right-1).ind) = points.at(left).ind;
        }
        return;
    }

    int lowest_point_ind(left);
    for(int i=left+1; i<right; ++i){
        if(points.at(i).y < points.at(lowest_point_ind).y){
            lowest_point_ind = i;
        }else if (points.at(i).y == points.at(lowest_point_ind).y && points.at(i).x < points.at(lowest_point_ind).x){
            lowest_point_ind = i;
        }
    }
    std::swap(points.at(left), points.at(lowest_point_ind));
    for(int i=left+1; i<right; ++i){
        double ny = static_cast<double>(points.at(i).y-points.at(left).y);
        double nx = static_cast<double>(points.at(i).x-points.at(left).x);
        points.at(i).angle = atan2(ny, nx);
    }
    std::sort(points.begin()+left+1, points.begin()+right);
    if(points.at(left).color == points.at(left+1).color){
        int cnt(0);
        int r = left+1;
        while(cnt!=0 || r==left+1){
            if(points.at(left).color == points.at(r).color){
                ++cnt;
            }else{
                --cnt;
            }
            ++r;
        }
        //从此最低开始配对配不上，因为多于一对，所以将此最低换到r-1的位置去配对
        std::swap(points.at(left), points.at(r-1));
        match(left, r-1, points, res);
        match(r-1, right, points, res);
    }else{
        match(left, left+2, points, res);
        match(left+2, right, points, res);
    }
}

int main(){
    int n;
    while(cin>>n){
        vector<struct point> points;
        int cnt(0);
        vector<int> res(n);
        while(cnt < 2 * n){
            int x, y;
            cin >> x >> y;
            struct point temp;
            temp.x = x;
            temp.y = y;
            temp.ind = cnt % n;
            temp.color = cnt >=n ? 1 : 0;
            points.push_back(temp);
            ++cnt;
        }
        match(0, 2*n, points, res);
        for(int i=0; i<res.size(); ++i){
            cout << res.at(i)+1 << endl;
        }
        cout << endl;
    }

}
