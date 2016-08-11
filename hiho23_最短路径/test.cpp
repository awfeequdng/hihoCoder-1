#include <iostream>
#include <memory.h>
using namespace std;

int main()
{
    unsigned num[5];
    memset(num, 0xff, sizeof(num));
    cout << num[0] << endl;
    return 0;
}
