#include <iostream>
#include <set>

using namespace std;

int main()
{
    set<int> s;
    for(int i = 0; i < 19; ++i)
        s.insert(i);
    int num;
    while(cin >> num)
    {
       set<int>::iterator it = s.upper_bound(num);
       set<int>::iterator it1 = s.lower_bound(num);
       cout << *it1 << '\t' << *it << endl;
    }
    return 0;
}
