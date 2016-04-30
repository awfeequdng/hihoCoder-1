#include <iostream>
using namespace std;
int main()
{
    bool flag[5000000] = {true};
    int state[5000000] = {0};
    int phi[5000000];
    int count = 0;
    int i;
    int num;
    cin >> num;
    for(i = 2; i <= num; ++i)
    {
        if(flag[i])
        {
            count++;
            state[count] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; i <= count; ++j)
        {
            if(i * state[j] > num)
                break;
            flag[i * state[j]] = false;
            if(i % state[j] == 0)
            {
                phi[i * state[j]] = phi[i] * state[j];
                break;
            }
            else
            {
                phi[i * state[j]] = phi[i] * (state[j] - 1);
            }
        }
    }
    int min = 5000000;
    for(i = 2; i <= num; ++i)
    {
        if(phi[i] < min)
            min = phi[i];
    }
    cout << min << endl;
    return 0;
}
