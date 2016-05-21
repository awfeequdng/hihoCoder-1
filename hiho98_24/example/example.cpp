#include <stdio.h>
#include <math.h>
double num[4];
bool dfs(int n)
{
	if(n==1)
	{
		//n=1时  最终的结果保存在num[0]
		if(fabs(num[0]-24)<0.000001)
		return true;
		else
		return false;
	}
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			double x=num[i];
			double y=num[j];
			//已经使用过的数 使它等于最后一个数
			num[j]=num[n-1];
			num[i]=x+y;if(dfs(n-1)) return true;
			num[i]=x-y;if(dfs(n-1)) return true;
			num[i]=y-x;if(dfs(n-1)) return true;
			num[i]=x*y;if(dfs(n-1)) return true;
			//避免除0
			if(y)
			{
				num[i]=x/y;
				if(dfs(n-1)) return true;
			}
			//避免除0
			if(x)
			{
				num[i]=y/x;
				if(dfs(n-1)) return true;
			}
			//回溯
			num[i]=x;
			num[j]=y;
		}
	}
	return false;
}
int main()
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%lf %lf %lf %lf",&num[0],&num[1],&num[2],&num[3]);
		if(dfs(4))
		puts("Yes");
		else
		puts("No");
	}
	return 0;
}
