#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int, int> num;
    num[1] = 1;
    num[2] = 2;
    //num[3] = 3;
    num[4] = 4;
    num[5] = 5;
    //auto a = num.lower_bound(3);
    //auto b = num.upper_bound(3);
    //cout << a->first << endl;
    //cout << b->first << endl;
    //auto l = num.lower_bound(5);
    auto r = num.upper_bound(4);
    //cout << l->first << endl;
    cout << r->first << endl;
    //for(auto i = l; i != r; ++i)
       // cout << i->first << " ";
    //cout << endl;
    //for(auto i = l; i != r; )
       // cout << (i++)->first << " ";
    //cout << endl;
    return 0;
}
