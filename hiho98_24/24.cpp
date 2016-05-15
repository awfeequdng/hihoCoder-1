//计算24点
//作者：haoyuanliu
//时间：2016.5.15

#include <iostream>
#include <vector>
using namespace std;

//1 +; 2 -; 3 *; 4 /; 5 反-; 6 反/
bool used[4] = false;
int nowNumber[] = {0, 0, 0, 0};
int ops[3] = {0, 0, 0};

bool makeNumber(int depth)
{
    if(depth >= 4)
        return makeOperation(0);
    for(int i = 0; i < 4; ++i)
    {
        if(!used[i])
        {
            nowNumber[i] = number[i];
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
        if(calcType1(nowNumber, ops) == 24)
            return true;
        if(calcType2(nowNumber, ops) == 24)
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
    int num, temp;
    vector<int> number;
    cin >> num;
    for(int i = 0; i < num; ++i)
    {
        cin >> temp;
        number.push_back(temp);
    }
}
