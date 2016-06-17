#include <iostream>
#include <bitset>
#include <cstring>
#define SIZE 10
#define M 729
#define N 324
using namespace std;

int board[SIZE][SIZE];
bitset<N+1> row[M+1];
bitset<M+1> col[N+1];
bitset<M+1> row_used;
bitset<N+1> col_covered;

void init()
{
    memset(board, 0, SIZE * SIZE * sizeof(int));
    row_used.reset();
    col_covered.reset();
    for(int i = 0; i < M+1; ++i)
        row[i].reset();
    for(int j = 0; j < N+1; ++j)
        col[j].reset();
}

void set(int i, int j, int k)
{
    int id = (i - 1) * 9 + j;
    int pid = (id - 1) * 9 + k;

    row[pid][(i - 1) * 9 + k] = 1;
    col[(i - 1) * 9 + k][pid] = 1;

    row[pid][81 + (j - 1) * 9 + k] = 1;
    col[81 + (i - 1) * 9 + k][pid] = 1;

    int t = ((i - 1) / 3 * 3 + (j - 1) / 3) + 1;

    row[pid][162 + (t - 1) * 9 + k] = 1;
    col[162 + (t - 1) * 9 + k][pid] = 1;

    row[pid][243 + id] = 1;
    col[243 + id][pid] = 1;
}

void create()
{
    for(int i = 1; i < 10; ++i)
    {
        for(int j = 1; j < 10; ++j)
        {
            if(board[i][j] == 0)
                for(int k = 1; k < 10; ++k)
                    set(i, j, k);
            else
                set(i, j, board[i][j]);
        }
    }
}

int main()
{
    int num;
    cin >> num;
    while(num--)
    {
        init();
        for(int i = 1; i < 10; ++i)
            for(int j = 1; j < 10; ++j)
                cin >> board[i][j];
        create();
    }
    return 0;
}
