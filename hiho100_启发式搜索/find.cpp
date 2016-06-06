#include <iostream>

int main()
{
    int temp;
    int num[9]
    int n;
    cin >> n;
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
