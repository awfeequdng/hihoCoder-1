#include <iostream>
#include <vector>
using namespace std;
//vector<int>& getNum(vector<int> &vec, int num);
//创建求约数函数
vector<int>& getNum(vector<int> &vec, int num)
{
    for(int i=1; i <= num; i++)
    {
        if(!(num % i))
        {
            vec.push_back(i);
        }
    }
    return vec;
}

int main()
{
    int a = 0;
    int b = 0;
    while(cin >> a >> b)
    {
        vector<int> a_num;
        vector<int> b_num;
        a_num = getNum(a_num, a);
        b_num = getNum(b_num, b);
        for(auto x : a_num)
        {
            for (auto y : b_num)
            {
                cout << x << " " << y << endl;
            }
        }
    }
    return 0;
}

