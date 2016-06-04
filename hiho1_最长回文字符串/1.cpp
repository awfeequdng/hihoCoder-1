#include <iostream>
#include <string>
using namespace std;

int find(char *ch)
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
    char temp[1000002];
    temp[0] = '$';
    cin >> num;
    for(int i = 0; i < num; ++i)
    {
       cin >> temp + 1;
       cout << find(temp) << endl;
    }
    return 0;
}
