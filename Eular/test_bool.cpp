#include <iostream>
using namespace std;
int main()
{
    bool a[10] = {false};
    for(const auto x : a)
    {
        if(x)
            cout << "1 ";
        else
            cout << "0 ";
    }
    cout << endl;
    return 0;
}
