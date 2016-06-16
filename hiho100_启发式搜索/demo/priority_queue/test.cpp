#include <iostream>
#include <queue>

using namespace std;

int main()
{
    priority_queue<int, vector<int>, greater<int>> test;
    test.push(5);
    test.push(6);
    test.push(8);
    cout << test.top() << endl;
    return 0;
}
