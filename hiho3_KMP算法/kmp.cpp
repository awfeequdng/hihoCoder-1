#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int flag[10005];

void getNext(string p)
{
    int pLen = p.length();
    flag[0] = -1;
    int k = -1;
    int j = 0;
    while(j < pLen - 1)
    {
        if(k == -1 || p[j] == p[k])
        {
            j++;
            k++;
            if(p[j] != p[k])
                flag[j] = k;
            else
                flag[j] = flag[k];
        }
        else
            k = flag[k];
    }
}

int kmpSearch(string s, string p)
{
    int count = 0;
    int j = 0;
    int i = 0;
    int sLen = s.length();
    int pLen = p.length();
    while(i < sLen)
    {
        if(j == -1 || s[i] == p[j])
        {
            j++;
            i++;
        }
        else
        {
            j = flag[j];
        }
        if(j == pLen - 1)
            count++;
    }
    return count;
}

int main()
{
    int num;
    string str;
    string p;
    cin >> num;
    while(num--)
    {
        memset(flag, 0, 10005 * sizeof(int));
        cin >> p;
        p = p + "*";
        cin >> str;
        getNext(p);
        cout << kmpSearch(str, p) << endl;
    }
    return 0;
}
