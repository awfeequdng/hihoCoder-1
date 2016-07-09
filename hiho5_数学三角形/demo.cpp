#include <iostream>

using namespace std;

int res[101];

int main()
{
    int n;
    int prev = 0;
    int curr = 0;
    int temp = 0;
    int max = 0;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        prev = 0;
        for(int j = 0; j <= i; ++j)
        {
            cin >> temp;
            curr = res[j];
            res[j] = temp + (prev > curr ? prev : curr);
            prev = curr;
        }
    }
    for(int i = 0; i < n; ++i)
        if(max < res[i])
            max = res[i];
    cout << max << endl;
    return 0;
}
