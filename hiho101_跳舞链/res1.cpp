#include <iostream>
#include <bitset>
#include <string>

#define SIZE 10

using namespace std;

bitset<SIZE> row[SIZE];
bitset<SIZE> col[SIZE];
bitset<SIZE> row_used;
bitset<SIZE> col_covered;

void init()
{
    row_used.reset();
    col_covered.reset();
    for(int i = 0; i < SIZE; ++i)
    {
        row[i].reset();
        col[i].reset();
    }
}



int main()
{
    int c, n, m, temp;
    cin >> c;
    while(c--)
    {
        cin >> n >> m; //n表示行，m表示列
        init();
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                cin >> temp;
                if(temp)
                {
                    row[i][j] = 1;
                    col[j][i] = 1;
                }
            }
        }
        if(dfs(0))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
