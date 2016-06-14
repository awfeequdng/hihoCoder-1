#include <iostream>
#include <bitset>
using namespace std;

#define SIZE 10

int main()
{
    bitset<SIZE> rol[SIZE];
    rol[0][1] = 1;
    for(const auto x : rol)
        cout << x << endl;
    bitset<SIZE> col(1023);
    cout << col << endl;
    for(int i = 0; i < SIZE; ++i)
        cout << col[i] << endl;
    return 0;
}
