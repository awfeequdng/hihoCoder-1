#include <iostream>
#include <set>
#include <string>

using namespace std;

set<int> s;

int main()
{
    int num;
    int temp;
    char ch;
    set<int>::iterator it;
    cin >> num;
    while(num--)
    {
        cin >> ch >> temp;
        if(ch =='I')
        {
            s.insert(temp);
        }
        else if(ch == 'Q')
        {
            it = s.upper_bound(temp);
            cout << *(--it) << endl;
        }
        else
        {
            int b;
            cin >> b;
            it = s.lower_bound(temp);
            while(it != s.end() && *it <= b)
                s.erase(it++);
        }
    }
    return 0;
}
