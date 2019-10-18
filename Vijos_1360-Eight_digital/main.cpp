#include <cstdio>
#include <array>
#include <cstring>

typedef std::array<int, 9> state;
//最大状态数9!=362880283104765
constexpr int MAXSTATE = 1000000;

std::array<int, 9> target{1,2,3,8,0,4,7,6,5};
std::array<state, MAXSTATE> st;
std::array<int, MAXSTATE> dist;

//9个数的排列，9!=362880，876543210，将每个状态换为一个数字并转为哈希
constexpr int MAXHASHSIZE = 100003;
//head和next存的都是st的index
std::array<int, MAXHASHSIZE> head;//存放哈希的头
std::array<int, MAXSTATE> next;

std::array<int, 4> dx{-1, 1, 0, 0};
std::array<int, 4> dy{0, 0, -1, 1};

void initHashTable(){
    head.fill(0);
}

int hash(int index){
    int sum(0);
    for(int i=0; i<9; ++i){
        sum = sum*10+st[index][i];
    }
    return sum%MAXHASHSIZE;
}

bool try2insert(int index){
    int hash_key = hash(index);
    int u = head[hash_key];
    while(u){
        if(st[u]==st[index]) return false;
        u = next[u];
    }
    next[index] = head[hash_key];
    head[hash_key] = index;
    return true;
}

int bfs(){
    initHashTable();
    int front = 1, rear = 2;
    while(front<rear){
        state &s = st.at(front);
        if(s == target) return dist[front];
        int i;
        for(i=0;i<9;++i){
            //寻找0的位置
            if(!s[i]) break;
        }
        //0位置的坐标
        int x = i / 3;
        int y = i % 3;
        for(int j=0;j<4;j++){
            int new_x = x + dx[j];
            int new_y = y + dy[j];
            if(new_x>=0 && new_x <3 && new_y>=0 && new_y<3){
                state new_s = s;
                int index = new_x*3+new_y;
                new_s[index] = s[i];
                new_s[i] = s[index];
                st[rear] = new_s;
                dist[rear] = dist[front]+1;
                //此状态可能已经到过了
                if(try2insert(rear)) ++rear;
            }
        }
        ++front;
    }
    return -1;
}

int main(){
//    int t;
//    scanf("%d", &t);
//    while(t--){
//        for(int i=0; i<9; ++i){
//            scanf("%d", &st.at(1).at(i));
//        }
//        for(int i=0; i<9; ++i){
//            scanf("%d", &target.at(i));
//        }
        int input;
        scanf("%d", &input);
        for(int i=8; i>=0; --i){
            st[1][i] = input%10;
            input/=10;
        }
        int ans = bfs();
        if(ans==-1){
            printf("%d\n", -1);
        }else{
            printf("%d\n", ans);
        }
//    }
}
