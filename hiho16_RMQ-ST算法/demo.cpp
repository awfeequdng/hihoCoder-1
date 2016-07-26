#include <iostream>
using namespace std;
#define N 1000010
int price[N];
int res[N][20];
int block[20];
int n, m;
void print();
void init()
{
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < 20; ++j)
            res[i][j] = 100000;
}

int getIndex(int n)
{
    int count = 0;
    while(n)
    {
        n = n>>1;
        count++;
    }
    return count;
}

void build()
{
    for(int i = 0; i < n; ++i)
        res[i][0] = price[i];
    print();
    for(int i = 0; i < n; ++i)
    {
        for(int j = 1; j <= getIndex(n-1); ++j)
        {
            res[i][j] = (res[i][j-1] < res[i+block[j-1]][j-1] ? res[i][j-1] : res[i+block[j-1]][j-1]);
        }
    }
}

void print()
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= getIndex(n-1); ++j)
        {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    init();
    block[0] = 1;
    for(int i = 1; i < 20; ++i)
    {
        block[i] = 2 * block[i-1];
    }
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> price[i];
    }
    build();
    print();
    return 0;
}
