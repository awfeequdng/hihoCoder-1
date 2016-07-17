/*状态压缩DP******填充地板 http://hihocoder.com/contest/hiho9/problem/1 */
#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;
#define NMax 1000
#define MMax 1<<5

bool testFirstLine(int j, int M) // 主要用来测试第一行的兼容性
{
	int i = 0;
	while(i < M)
	{
		if((j & (1<<i)) == 0)       // 判断j的第i位是否为0  为1则执行   如果第i为1 则其前一位为0  如果判断的第j位为1  其后一位必然为0
			i++;
		else if(i == M-1 || !(j & (1 << (i+1))))
			return false;
		else i += 2;
	}
	return true;
}

bool testCompatible(int statesA, int statesB, int M)   // 判断下一行状态stateA与上一行状态stateB的兼容性
{
	int i = 0;
	while(i < M)
	{
		if((statesA & (1<<i)) == 0)
		{
			if((statesB & (1<<i)) == 0)
			{
				return false;
			}
			i++;
		}
		else{
			if((statesB & (1<<i)) == 0) i++;
			else if(i == M-1 || !((statesA &(1<<(i+1))) && (statesB &(1<<(i+1)))))
			{
				return false;
			}
			else i += 2;
		}
	}
	return true;
}

int main()
{
	int N, M;
	cin >> N >> M;
	if(M > N){
		swap(M, N);
	}
	int allStates = 1 << M;
	long long F[NMax][MMax];
	int i,j;
	memset(F, 0, sizeof(F));
	for(j = 0; j < allStates; j++)
	{
		if(testFirstLine(j, M))
		{
			F[0][j] = 1;
		}
	}
	int k;
	for(i = 1; i < N; i++)
	{
		for(j = 0; j < allStates; j++)
		{
			for(k = 0; k < allStates; k++)
			{
				if(testCompatible(j,k,M))
				{
					F[i][j] += F[i-1][k];
					F[i][j] = F[i][j] % 1000000007;

				}
			}
		}
	}
	cout << F[N-1][allStates-1]<< endl;
	return 0;
}

/* 测试案例
2 4
5
*/
