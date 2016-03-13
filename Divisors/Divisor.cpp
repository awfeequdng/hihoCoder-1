//这段代码的循环体较难看懂
//这是一种乱序循环，但是效率很高，效果很好
#include<cmath>
#include<iostream>
using namespace std;
typedef long long ll;

long prime[] = {2 ,3 ,5 ,7 ,11 ,13 ,17 ,19 ,23 ,29 ,31 ,37 ,41};
ll result, n, maxDivisors;
void dfs(long t, ll now, ll divisors, ll lastNi)
{
    if(divisors > maxDivisors || (divisors == maxDivisors && now < result))
    {
        maxDivisors = divisors;
        result = now;
    }
    int i = 1;
    while(now * pow(prime[t], i) < n && i <= lastNi)
    {
        //抛出循环，进行测试，进入到primer_next的循环
        dfs(t + 1, now * pow(prime[t], i), divisors * (i+1), i);
        //继续本循环，维持now_primer的循环，i++
        i = i + 1;
    }
}
int main()
{
    cin >> n;
    maxDivisors = 0;
    dfs(0, 1, 1, 100);
    cout << result << endl;
    return 0;
}
