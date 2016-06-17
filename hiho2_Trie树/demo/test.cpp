#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    int test[10];
    memset(test, -2, sizeof(test));
    for(const auto x : test)
        cout << x << endl;
    return 0;
}
