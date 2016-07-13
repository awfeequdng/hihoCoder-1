#include <iostream>
using namespace std;

int main()
{
    for(int i = 10; i < 20; ++i)
    {
        cout << ((i & 0x7)>>1) << endl;
    }
    return 0;
}
