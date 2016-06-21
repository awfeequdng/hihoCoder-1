#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    string str;
    while(cin >> str)
    {
        cout << str << endl;
        cout << str.size() << endl;
    }
    int test[10];
    memset(test, -2, sizeof(test));
    for(const auto x : test)
        cout << x << endl;
    return 0;
}
