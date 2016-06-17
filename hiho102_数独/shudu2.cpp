#include <iostream>
#include <memory>
#include <stack>
#include <cstring>
#define SIZE 10
#define n 729
#define m 324
using namespace std;

struct Node
{
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    int x, y;
    Node(){ }
    Node(Node *left_, Node *right_, Node *up_, Node *down_, int x_, int y_) : left(left_), right(right_), up(up_), down(down_), x(x_), y(y_) { }
};

int board[SIZE][SIZE];
int matrix[n+1][m+1];
int id[n+1][m+1];
int ans[SIZE][SIZE];
int cnt[m+1];
Node *head = NULL;//初始化为NULL
Node *columnHead[m + 1];//构建列头结点
Node *node[(n+1)*(m+1)];//构建结点矩阵


/*
 *使用memset进行初始化不靠谱，还得是用for循环
 *切记切记！！！
 */
void init()
{
    head = NULL;//这里一定要初始化为NULL，不然会报段错误，无法成功build函数
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j)
            board[i][j] = 0;
    for(int i = 0; i <= n; ++i)
        for(int j = 0; j <= m; ++j)
            id[i][j] = 0;
    for(int i = 0; i <= n; ++i)
        for(int j = 0; j <= m; ++j)
            matrix[i][j] = 0;
    for(int i = 0; i <= m; ++i)
        cnt[i] = 0;
    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j)
            ans[i][j] = 0;

    //memset(board, 0, SIZE * SIZE);
    //memset(id, 0, 730 * 325);
    //memset(matrix, 0, 730 * 325);
    //memset(cnt, 0, m + 1);
    //memset(ans, 0, SIZE * SIZE);
    for(auto x : columnHead)//使用C11新特性初始化为NULL，方便
        x = NULL;
    for(auto x : node)
        x = NULL;
}


void set(int i, int j, int k)
{
    int id = (i - 1) * 9 + j;
    int pid = (id - 1) * 9 + k;
    matrix[pid][(i - 1) * 9 + k] = 1;
    matrix[pid][81 + (j - 1) * 9 + k] = 1;
    int t = ((i - 1) / 3 * 3 + (j - 1) / 3) + 1;
    matrix[pid][162 + (t - 1) * 9  + k] = 1;
    matrix[pid][243 + id] = 1;
}

void create()
{
    for(int i =  1; i < 10; ++i)
    {
        for(int j = 1; j < 10; ++j)
        {
            if(board[i][j] == 0)
                for(int k = 1; k < 10;  ++k)
                    set(i, j, k);
            else
                set(i, j, board[i][j]);
        }
    }
}

void build()
{
    if(head == NULL)
    {
        //这种写法是错误的！还没构建就使用。。。
        //head = new Node(head, head, head, head, 0, 0);
        //使用两步进行构建，这个非常重要
        head = new Node();
        *head = Node(head, head, head, head, 0, 0);
    }
    auto pre = head;
    //构建列头结点
    for(int i = 1; i <= m; ++i)
    {
        columnHead[i] = new Node();
        auto p = columnHead[i];
        p->up = p->down = p;
        p->x = 0;
        p->y = i;
        p->right = pre->right;
        p->left = pre;
        pre->right->left = p;
        pre->right = p;
        pre = p;
    }
    int count = 0;
    //结点编号并初始化
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            if(matrix[i][j] == 1)
            {
                count++;
                id[i][j] = count;
                node[count] = new Node();
                *node[count] = Node(node[count], node[count], node[count], node[count], i, j);
            }
        }
    }
    //纵向添加结点
    for(int j = 1; j <= m; ++j)
    {
        auto pre = columnHead[j];
        for(int i = 1; i <= n; ++i)
        {
            if(matrix[i][j] == 1)
            {
                cnt[j] += 1;
                auto p = node[id[i][j]];
                p->down = pre->down;
                p->up = pre;
                pre->down->up = p;
                pre->down = p;
                pre = p;
            }
        }
    }
    //横向添加结点
    for(int i = 1; i <=n; ++i)
    {
        Node *pre = NULL; //???
        for(int j = 1; j <= m; ++j)
        {
            if(matrix[i][j] == 1)
            {
                if(pre == NULL)
                    pre = node[id[i][j]];
                else
                {
                    auto p = node[id[i][j]];
                    p->right = pre->right;
                    p->left = pre;
                    pre->right->left = p;
                    pre->right = p;
                    pre = p;
                }
            }
        }
    }
}

//移除列的函数
void remove(int col)
{
    auto p = columnHead[col];
    p->right->left = p->left;
    p->left->right = p->right;
    auto p2 = p->down;
    while(p2 != p)
    {
        auto p3 = p2->right;
        while(p3 != p2)
        {
            p3->down->up = p3->up;
            p3->up->down = p3->down;
            cnt[p3->y] -= 1;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}

//恢复列的函数
void resume(int col)
{
    auto p = columnHead[col];
    p->right->left = p;
    p->left->right = p;
    auto p2 = p->down;
    while(p2 != p)
    {
        auto p3 = p2->right;
        while(p3 != p2)
        {
            p3->down->up = p3;
            p3->up->down = p3;
            cnt[p3->y] += 1;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}

Node* findMinCnt(Node *point)
{
    int min = 999;
    int index = 0;
    auto p = point->right;
    while(p != point)
    {
        if(min > cnt[p->y])//这里需要注意的是，> 和　>=遍历的顺序是不一样的
        {
            min = cnt[p->y];
            index = p->y;
        }
        p = p->right;
    }
    return columnHead[index];
}

//跳舞链深度搜索函数
bool dance(int depth)
{
    if(head->right == head)
        return true;
    auto p = findMinCnt(head);
    auto p2 = p->down;
    if(p2 == p)
        return false;

    remove(p->y);

    while(p2 != p)
    {
        ans[(p2->x - 1)/81 +1][((p2->x - 1)/9) % 9 + 1] = (p2->x - 1) % 9 + 1;

        auto p3 = p2->right;
        while(p3 != p2)
        {
            remove(p3->y);
            p3 = p3->right;
        }

        if(dance(depth + 1))
            return true;

        p3 = p2->left;
        while(p3 != p2)
        {
            resume(p3->y);
            p3 = p3->left;
        }

        p2 = p2->down;
    }
    resume(p->y);//所有更改全部回溯
    return false;
}


int main()
{
    int num;
    cin >> num;
    while(num--)
    {
        init();
        for(int i = 1; i < 10; ++i)
        {
            for(int j = 1; j < 10; ++j)
            {
                cin >> board[i][j];
            }
        }
        create();
        build();
        if(dance(0))
        {
            for(int i = 1; i < 10; ++i)
            {
                for(int j = 1; j < 10; ++j)
                    cout << ans[i][j] << " ";
                cout << endl;
            }
        }
    }
    return 0;
}
