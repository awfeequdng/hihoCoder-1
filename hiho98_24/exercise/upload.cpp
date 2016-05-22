//计算24点
//作者：haoyuanliu
//时间：2016.5.15

#include <iostream>
#include <vector>
using namespace std;

//0 +; 1 -; 2 *; 3 /; 4 反-; 5 反/
bool used[4] = {false};
double nowNumber[4] = {0};
int ops[3] = {0};
double number[4] = {0};
int down = 1;

bool makeOperation(int depth);

double cal(double a, double b, int opt)
{
    switch(opt)
    {
        case 0:
            return a + b;
        case 1:
            return a - b;
        case 2:
            return a * b;
        case 3:
            if(b == 0)
                break;
            return a / b;
        case 4:
            return b - a;
        case 5:
            if(a == 0)
                break;
            return b / a;
    }
}

double calcType1(double *n, int *ops)
{
    return cal(cal(cal(n[0], n[1], ops[0]), n[2], ops[1]), n[3], ops[2]);
}

double calcType2(double *n, int *ops)
{
    return cal(cal(n[0], n[1], ops[0]), cal(n[2], n[3], ops[2]), ops[1]);
}

bool makeNumber(int depth)
{
    if(depth >= 4)
        return makeOperation(0);
    for(int i = 0; i < 4; ++i)
    {
        if(!used[i])
        {
            nowNumber[depth] = number[i];
            used[i] = true;
            if(makeNumber(depth + 1))
                return true;
            used[i] = false;
        }
    }
    return false;
}

bool makeOperation(int depth)
{
    if(depth >= 3)
    {
        auto temp1 = calcType1(nowNumber, ops);
        auto temp2 = calcType2(nowNumber, ops);
        if(temp1 == 24)
        {
            return true;
        }
        if(temp2 == 24)
            return true;
        return false;
    }
    for(int i = 0; i < 6; ++i)
    {
        ops[depth] = i;
        if(makeOperation(depth + 1))
            return true;
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
        if(makeNumber(0))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
