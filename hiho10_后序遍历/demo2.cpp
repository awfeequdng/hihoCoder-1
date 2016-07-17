/*
 *思路是对的，就是之前建立str太浪费空间时间，直接进行打印操作即可。
 *不需要额外建立string，使用substr进行表示节省空间，算完直接打印节省时间
 */
#include <iostream>
#include <string>

using namespace std;

void postOrder(string str1, string str2)
{
    if(str1.size() <= 1)
    {
        cout << str1;
        return;
    }
    int len = str2.find(str1[0]);
    postOrder(str1.substr(1, len), str2.substr(0, len));
    postOrder(str1.substr(len+1), str2.substr(len+1));
    cout << str1.substr(0, 1);
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    postOrder(s1, s2);
    cout << endl;
    return 0;
}
