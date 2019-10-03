#include <stdio.h>

int n, start[20], end[20], md;

enum OP
{
    ADD = 0,
    DIV = 1,
    DUP = 2,
    MUL = 3,
    SUB = 4
};
//ADD DIV DUP MUL SUB

int stk[10][20];
int cnt;
int ops[20];

char str[5][5] = {"ADD", "DIV", "DUP", "MUL", "SUB"};

bool check()
{
    for (int i = 0; i < n; i++)
    {
        if (end[i] != stk[i][0])
            return false;
    }
    for (int i = 1; i <= md; i++)
    {
        if (i != 1) putchar(' ');
        printf("%s", str[ops[i]]);
    }
    puts("");
    return true;
}

bool dup()
{
    for (int i = 0; i < n; i++)
    {
        stk[i][cnt] = stk[i][cnt - 1];
    }
    cnt++;
    return true;
}

bool add()
{
    for (int i = 0; i < n; i++)
    {
        stk[i][cnt - 2] = stk[i][cnt - 1] + stk[i][cnt - 2];

        if (stk[i][cnt - 2] > 30000 || stk[i][cnt - 2] < -30000)    return false;
    }
    cnt--;
    return true;
}

bool mul()
{
    for (int i = 0; i < n; i++)
    {
        stk[i][cnt - 2] = stk[i][cnt - 1] * stk[i][cnt - 2];

        if (stk[i][cnt - 2] > 30000 || stk[i][cnt - 2] < -30000)    return false;
    }
    cnt--;
    return true;
}

bool sub()
{
    for (int i = 0; i < n; i++)
    {
        stk[i][cnt - 2] = stk[i][cnt - 2] - stk[i][cnt - 1];

        if (stk[i][cnt - 2] > 30000 || stk[i][cnt - 2] < -30000)    return false;
    }
    cnt--;
    return true;
}

bool div()
{
    for (int i = 0; i < n; i++)
    {
        if (stk[i][cnt - 1] == 0)   return false;
        stk[i][cnt - 2] = stk[i][cnt - 2] / stk[i][cnt - 1];
    }
    cnt--;
    return true;
}

#define SAVE    bc = cnt;\
                for (int i = 0; i < n; i++)\
                for (int j = 0; j < cnt; j++)\
                    bk[i][j] = stk[i][j];

#define RECOVER cnt = bc;\
                for (int i = 0; i < n; i++)\
                for (int j = 0; j < cnt; j++)\
                    stk[i][j] = bk[i][j];

bool dfs(int d)
{
    if (d > md)
    {
        return cnt == 1 && check();
    }

    int bc, bk[10][11];

    SAVE

    if (cnt == 1)//only dup
    {
        ops[d] = DUP;
        dup();
        if (dfs(d + 1)) return true;
        RECOVER
    }
    else
    {
        //ADD
        ops[d] = ADD;
        if (add() && dfs(d + 1)) return true;
        RECOVER

        //DIV
        ops[d] = DIV;
        if (div() && dfs(d + 1))    return true;
        RECOVER

        //DUP
        ops[d] = DUP;
        if (dup() && dfs(d + 1))    return true;
        RECOVER

        //MUL
        ops[d] = MUL;
        if (mul() && dfs(d + 1))    return true;
        RECOVER

        //SUB
        ops[d] = SUB;
        if (sub() && dfs(d + 1))    return true;
        RECOVER
    }
    return false;
}

void solve()
{
    for (md = 2; md <= 10; md += 1)
    {
        cnt = 1;
        for (int i = 0; i < n; i++)
        {
            stk[i][0] = start[i];
        }
        if (dfs(1))
        {
            return;
        }
    }
    puts("Impossible");
}

int main()
{
    int cas = 1;

    while (scanf("%d", &n), n)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &start[i]);
        }
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &end[i]);
        }
        bool search = false;
        printf("Program %d\n", cas++);
        for (int i = 0; i < n; i++)
        {
            if (start[i] != end[i])
            {
                search= true;
                break;
            }
        }
        if (!search)
            puts("Empty sequence");
        else
            solve();
        puts("");
    }
    return 0;
}
