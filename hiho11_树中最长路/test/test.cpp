#include <iostream>
#include <vector>
using namespace std;
int main()
{
    //这两种写法都是建立一个二维数组，第一种方法行列都是vector属性的
    //而第二种方法，行为普通数组属性，列为vector属性
    //重要的是其中一个是（），一个是【】，还有这里需要赋值的话需要哦&符号
    vector<vector<int>> res(10);
    vector<int> a[10];
    for(auto &x : res)
    {
        x.push_back(1);
    }
    for(const auto x : res)
    {
        for(const auto y : x)
            cout << y << " ";
        cout << endl;
    }
    return 0;
}
