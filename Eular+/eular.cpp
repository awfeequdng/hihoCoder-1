#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int l = 0;
    int r = 0;
    cin >> l >> r;
    vector<bool> flag(r+1, true);
    vector<int> prime;
    vector<int> func(r+1, r);
    int i, j;
    int count = 0;
    for(i = 2; i <= r; ++i)
    {
        if(flag[i])
        {
            count++;
            prime.push_back(i);
            func[i] = i - 1;
        }
        for(j = 0; j < count; ++j)
        {
            if(i * prime[j] > r)
                break;
            flag[i * prime[j]] = false;
            if(i % prime[j] == 0)
            {
                func[i * prime[j]] = func[i] * prime[j];
                break;
            }
            else
            {
                func[i * prime[j]] = func[i] * (prime[j] - 1);
            }
        }
    }
    int min = r;
    int index = 0;
    for(i = r-1; i >= l; --i)
    {
        if(func[i] <= min)
        {
            min = func[i];
            index = i;
        }
    }
    cout << index << endl;
    return 0;
}
