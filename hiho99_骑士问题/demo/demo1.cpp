#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

char start[3][3];//表示三个骑士起始位置坐标字符表示
queue<int> q;//用于广度搜索的队列
int step[270000];//记录8^6个状态整数
int now_status;//将当前位置坐标映射成一个八进制数1-8 => 0-7，A-H => 0-7
int next_status;

int next_step[8][2] = { { -2,1 },{ -1,2 },{ 1,2 },{ 2,1 },{ 2,-1 },{ 1,-2 },{ -1,-2 },{ -2,-1 } };

//将当前状态转移
//i表示第几个位置，j表示移动方向
//同时检查状态是否合法
int move(int status,int i, int j)
{
    int now_site = (status >> (6 * (2 - i))) & 0x3F;
    int next_site = now_site;

    next_site += next_step[j][0] * 8 + next_step[j][1];

    if (next_site >= 0 && next_site <= 0x3F)
        next_status = status ^ (now_site << (6 * (2 - i))) | (next_site << (6 * (2 - i)));//修改对应位置的状态
    else
        return -1;
    return next_status;
}

bool checkOK(int status)
{
    //若三个位置相同，则找到一个结果
    return ((status & 0x3F) == ((status >> 6) & 0x3F) && (status >> 6) & 0x3F) == ((status >> 12) & 0x3F);
}
int solve()
{
    char s[7]="";
    start[0][0] = start[0][0] - 'A' + '0';
    start[1][0] = start[1][0] - 'A' + '0';
    start[2][0] = start[2][0] - 'A' + '0';

    start[0][1] = start[0][1] - '1' + '0';
    start[1][1] = start[1][1] - '1' + '0';
    start[2][1] = start[2][1] - '1' + '0';

    strcat_s(s, start[0]);
    strcat_s(s, start[1]);
    strcat_s(s, start[2]);

    //cout << s << endl;
    //cout  << strtol(s,NULL,8)<< endl;

    now_status = strtol(s, NULL, 8);//按八进制转换为十进制整数

    if (checkOK(now_status))
    {
        return 0;//开始状态符合，返回0
    }

    memset(step,-1,sizeof(step));//按字节初始化,只能为0或-1
    step[now_status] = 0;
    //清空队列
    while (!q.empty())
        q.pop();

    q.push(now_status);
    while (!q.empty())
    {
        now_status = q.front();
        q.pop();
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 8; ++j)
            {
                next_status = move(now_status, i, j);
                if (next_status != -1 && step[next_status] == -1)
                {
                    step[next_status] = step[now_status] + 1;
                    q.push(next_status);
                    if (checkOK(next_status))
                    {
                        return step[next_status];
                    }
                }
            }
    }
    return 0;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> start[0] >> start[1] >> start[2];
        cout << solve() << endl;
    }
    return 0;
}