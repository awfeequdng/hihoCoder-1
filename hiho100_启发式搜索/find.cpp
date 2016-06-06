#include <iostream>
using namespace std;

int fact(int t)
{
    int res = 1;
    for(int i = 1; i <= t; ++i)
    {
        res *= i;
    }
    return res;
}
int contor(int val) //康托展开
{
    int n[9];
    for(int i = 8; i <= 0; ++i)
    {
        n[i] = val % 10;
        val /= 10;
    }

    int X = 0;
    for(int j = 0; j < 9; ++j)
    {
        int count = 0;
        for(int k = j + 1; k < 9; ++k)
        {
            if(n[j] < n[k])
                count++;
        }
        X += count * fact(9 - j);
    }

    return X;
}

int uncontor(int X) //逆康托展开
{
    
}

int main()
{
    int temp;
    int num[9];
    int n;
    cin >> n;
    cout << fact(n) << endl;
    while(n--)
    {
        int val = 0;
        for(int i = 0; i < 9; ++i)
        {
            cin >> temp;
            if(temp == 0)
                temp = 9;
            num[i] = temp;
            val = val * 10 + temp;
        }
    }
    return 0;
}
