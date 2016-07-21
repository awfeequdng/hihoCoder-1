#include <iostream>
#include <map>
using namespace std;

int main()
{
    string temp;
    map<string, int> m;
    for(int i = 0; i < 5; ++i)
    {
        cin >> temp;
        m.insert(make_pair(temp, i));
    }
    map<string, int>::iterator it;
    it = m.find("hello");
    cout << (*it).second << endl;
    return 0;
}
