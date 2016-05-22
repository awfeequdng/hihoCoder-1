#include <iostream>
#include <vector>
using namespace std;

char pos[6];

int main()
{
    int num, count;
    cin >> num;
    while(num--)
    {
        string position, temp;
        for(int i = 0; i < 3; ++i)
        {
            cin >> temp;
            position += temp;
        }
        count = 0;
        for(auto const x : position)
        {
            if(x > 64)
                pos[count++] = x - 65 + 48;
            else if( x > 48)
                pos[count++] = x - 1;
            else
                continue;
        }
    }
    return 0;
}
