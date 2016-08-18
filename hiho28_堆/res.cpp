#include <iostream>
#define N 100010
using namespace std;
int num[N];

void HeapUpdate(int cur, int len)
{
    int pos = cur;
    int left = cur * 2;
    int right = cur * 2 + 1;
    if(cur <= len/2)
    {
        if(left <= len && num[left] > num[pos])
            pos = left;
        if(right <= len && num[right] > num[pos])
            pos = right;
        if(pos != cur)
        {
            swap(num[pos], num[cur]);
            HeapUpdate(pos, len);
        }
    }
    return;
}

int main()
{
    int n;
    int len = 0;
    char oper;
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> oper;
        if(oper == 'A')
        {
            cin >> num[++len];
            int l = len/2;
            while(l != 0)
            {
                HeapUpdate(l, len);
                l = l/2;
            }
        }
        else
        {
            cout << num[1] << endl;
            swap(num[1], num[len--]);
            HeapUpdate(1, len);
        }
    }
    return 0;
}
