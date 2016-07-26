#include <iostream>
using namespace std;
#define N 1000010
int price[N];
int res[N][20];
int block[20];
int n, m;

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
        res[i][1] = price[i];
    for(int i = 1; i < 20; ++i)
    {

    }
}

int main()
{
    block[0] = 1;
    for(int i = 1; i < 20; ++i)
    {
        block[i] = 2 * block[i-1];
    }
    cout << "Enter n" << endl;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> price[i];
    }
}
