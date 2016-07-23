#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    map<string, string> m;
    map<string, string>::iterator it;
    string s1, s2;
    for(int i = 0; i < 5; ++i)
    {
        cin >> s1 >> s2;
        m.insert(make_pair(s1, s2));
    }
    while(cin >> s1)
    {
        it = m.find(s1);
        if(it != m.end())
            cout << m[s1] << endl;
    }
    return 0;
}
