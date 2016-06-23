#include <string>
#include <iostream>

using namespace std;

int main()
{
    string temp;
    while(cin >> temp)
        cout << sizeof(temp) << endl;
    return 0;
}
