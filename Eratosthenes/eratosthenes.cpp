#include <iostream>
using namespace std;
int main()
{
    int num;
    cin >> num;
    int flag[1000] = {0};
    int prime[1000];
    int count = 0;
    for(int i = 2; i < num; ++i)
    {
        if(!flag[i])
            prime[count++] = i;
        for(int j = i + i; j <= num; j += i)
            flag[j] = 1;
    }
    cout << "The number is: " << count << endl;
}
