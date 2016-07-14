#include <iostream>
using namespace std;

int main()
{
    int temp = 16;
    while(temp > 0)
    {
        cout << (temp >> 1) << endl;
        temp = temp >> 1;
    }
    for(int i = 10; i < 20; ++i)
    {
        cout << ((i & 0x7)>>1) << endl;
    }
    return 0;
}
