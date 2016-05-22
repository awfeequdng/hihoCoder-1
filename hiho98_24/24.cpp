#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
double number[4];

bool trueorfalse(int n)
{
    if(n == 1)
    {
        if(fabs(number[0] - 24) < 0.0001)
            return true;
        else
            return false;
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = i + 1; j < n; ++j)
        {
            double a = number[i];
            double b = number[j];
            number[j] = number[n - 1];//用于压缩数组空间

            number[i] = a + b;
            if(trueorfalse(n - 1))
                return true;

            number[i] = a - b;
            if(trueorfalse(n - 1))
                return true;

            number[i] = b - a;
            if(trueorfalse(n - 1))
                return true;

            number[i] = a * b;
            if(trueorfalse(n - 1))
                return true;

            if(b != 0)
            {
                number[i] = a / b;
                if(trueorfalse(n - 1))
                    return true;
            }

            if( a != 0)
            {
                number[i] = b / a;
                if(trueorfalse(n - 1))
                    return true;
            }

            //回溯回去
            number[i] = a;
            number[j] = b;
        }
    }
    return false;
}


int main()
{
    int num;
    double temp;
    cin >> num;
    while(num--)
    {
        for(int i = 0; i < 4; ++i)
        {
            cin >> temp;
            number[i] = temp;
        }
        if(trueorfalse(4))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
