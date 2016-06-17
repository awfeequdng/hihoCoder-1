#include <iostream>
#include <bitset>
#include <string>
#include <cstring>

#define SIZE 105

using namespace std;

int n, m;
bitset<SIZE> row[SIZE];
bitset<SIZE> col[SIZE];
bitset<SIZE> row_used;
bitset<SIZE> col_covered;
int ans[SIZE];

void init()
{
    memset(ans, 0, SIZE * sizeof(int));
    row_used.reset();
    col_covered.reset();
    for(int i = 0; i < SIZE; ++i)
    {
        row[i].reset();
        col[i].reset();
    }
}

bool dfs(int index)
{
    if(col_covered.count() == m)
        return true;
    else if(row_used.count() == n)
        return false;

    bitset<SIZE> row_record = row_used;
    bitset<SIZE> col_record = col_covered;
    for(int i = index; i < n; ++i)
    {
        if(row_used[i] == 0)
        {
            ans[index] = i;
            for(int j = 0; j < m; ++j)
            {
                if(row[i][j] == 1)
                    row_used |= col[j];
            }

            col_covered |= row[i];
            if(dfs(i + 1))
                return true;
            row_used = row_record;//这个回溯太精髓了！
            col_covered = col_record;
        }
    }
    return false;
}

int main()
{
    int c, temp;
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
        {
            cout << "Yes" << endl;
            for(const auto x : ans)
                cout << x << " ";
            cout << endl;
        }
        else
            cout << "No" << endl;
    }
    return 0;
}
