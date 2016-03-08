#include <iostream>
#include <string>
#include <vector>
using namespace std;
int del(string s)
{
    int len = s.size();
    if(len == 0)
        return 0;
    string temp = "";
    s += "$";
    int flag = 0;
    for (int i = 1; i <= len; i++)
    {
        if (s[i] != s[i - 1])
        {
            if (flag == i-1)
            {
                temp += s[i-1];
            }
            flag = i;
        }
    }
    int tlen = temp.size();
    if (tlen == len)
        return 0;
    return len - tlen + del(temp);
}

int main()
{
    int n;
    cin >> n;
    vector<string> str;
    for(int i = 0; i < n; i++)
    {
        string temp = "";
        cin >> temp;
        str.push_back(temp);
    }
    for(auto s : str)
    {
        int ans = 0;
        int len = s.size();
        int t;
        for(int i = 0; i <= len; i++)
        {
            string tmp = s;
            tmp.insert(i, "A");
            if((t = del(tmp)) > ans)
                ans = t;
            tmp = s;
            tmp.insert(i, "B");
            if((t = del(tmp)) > ans)
                ans = t;
            tmp = s;
            tmp.insert(i, "C");
            if((t = del(tmp)) > ans)
                ans = t;
        }
        cout << ans << endl;
    }
return 0;
}
