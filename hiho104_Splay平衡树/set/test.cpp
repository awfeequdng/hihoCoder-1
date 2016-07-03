#include <iostream>
#include <set>

using namespace std;

int main()
{
    set<int> s;
    int num;
    for(int i = 0; i < 9; ++i)
    {
        cin >> num;
        s.insert(num);
    }
    while(cin >> num)
    {
       set<int>::iterator it = s.upper_bound(num);
       set<int>::iterator it1 = s.lower_bound(num);
       cout << *it1 << '\t' << *it << endl;
    }
    return 0;
}
