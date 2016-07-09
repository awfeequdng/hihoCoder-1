#include <iostream>
#include <set>
using namespace std;

int main()
{
    set<int> s;
    set<int>::iterator it;
    int n;
    int temp;
    char ch;
    cin >> n;
    while(n--)
    {
        cin >> ch >> temp;
        if(ch == 'I')
            s.insert(temp);
        else if(ch == 'Q')
        {
            it = s.begin();
            for(int i = 1; i < temp; ++i)
                it++;
            cout << *it << endl;
        }
    }
    return 0;
}