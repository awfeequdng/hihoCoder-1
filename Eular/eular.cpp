#include <iostream>
using namespace std;
#define Length 1000000
int main()
{
    int num;
    cin >> num;
    int flag[Length] = {0};
    int prime[1000];
    int count = 0;
    for(int i = 2; i <= num; ++i)
    {
        if(!flag[i])
        {
            prime[++count] = i;
        }
        for(int j = 1; j <= count; ++j)
        {
            if(i * prime[j] > num)
                break;
            flag[i * prime[j]] = 1;
            if(i % prime[j] == 0)
                break;
        }
    }
    cout << count << endl;
}
