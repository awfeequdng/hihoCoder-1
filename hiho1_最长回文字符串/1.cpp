#include <iostream>
#include <vector>
using namespace std;

int find(string ch)
{
    int ans = 1;
    int i, p, n;
    for(i = 0; ch[i]; ++i)
    {
        p = i;
        n = i;

        while(ch[n + 1] == ch[i])
            n++;
        i = n;
        while(ch[p - 1] == ch[n + 1])
        {
            p--;
            n++;
        }
        if(ans < (n - p + 1))
            ans = n - p + 1;
    }
    return ans;
}

int main()
{
    int num;
    string temp;
    cin >> num;
    for(int i = 0; i < num; ++i)
    {
       cin >> temp;
       cout << find(temp) << endl;
    }
    return 0;
}
