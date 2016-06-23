#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string str;
string p;
int next[10005];

void getNext(int next[], string p)
{
    int pLen = strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while(j < pLen - 1)
    {
        if(k == -1 || p[j] == p[k])
        {
            j++;
            k++;
            if(p[j] != p[k])
                next[j] = k;
            else
                next[j] = next[k];
        }
        else
            k = next[k];
    }
}

int kmpSearch(string str, str p)
{
    int count = 0;
    int j = 0;
    int i = 0;
    int sLen = strlen(str);
    int pLen = strlen(p);
    while(i < sLen)
    {
        if(j == -1 || s[i] == p[j])
        {
            j++;
            i++;
        }
        else
        {
            j = next[j];
        }
        if(j == pLen - 1)
            count++;
    }
    return count;
}

int main()
{
    int num;
    cin >> num;
    while(num--)
    {
        cin >> p;
        cin >> str;
        getNext(p);
        cout << kmpSearch(str, p) << endl;
    }
    return 0;
}
