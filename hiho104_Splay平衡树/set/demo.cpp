#include <iostream>
#include <set>

using namespace std;

set<int> s;
set<int>::iterator it;
int main()
{
    int n;
    cin >> n;
    int num;
    char ch;
    int bnum;
    while(n--)
    {
        cin >> ch >> num;
        if(ch == 'I')
        {
            s.insert(num);
        }
        else if(ch == 'Q')
        {
            it = s.upper_bound(num);
            cout << *(--it) << endl;
        }
        else
        {
            cin >> bnum;
            auto low_it = s.lower_bound(num);
            auto up_it = s.upper_bound(bnum);
            s.erase(low_it, up_it);
        }
    }
    return 0;
}
