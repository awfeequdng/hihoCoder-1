#include <iostream>
#include <queue>

using namespace std;

int main()
{
    queue<string> que;
    string str;
    for(int i = 0; i < 5; ++i)
    {
        cin >> str;
        que.push(str);
    }
    while(!que.empty())
    {
        cout << que.front() << endl;
        que.pop();
    }
    return 0;
}
