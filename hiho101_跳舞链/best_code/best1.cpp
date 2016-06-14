#include<iostream>
#include<cstdio>
#include<bitset>
#include<cstring>

#define MAXN 105

using namespace std;

int n,m;
bitset<MAXN>rolcolList[MAXN];
bitset<MAXN>colrolList[MAXN];
bitset<MAXN>colremain;
bitset<MAXN>rolremain;

bool Dfs(int index, int count)
{
	//if we have found the answer or there is no rol to choose
	//return the result
	if(colremain.count() == m)return true;
	else if(rolremain.count() == n)return false;
    else if(count >= 5) return false;
	int i,j;
	bitset<MAXN>recordrol;
	bitset<MAXN>recordcol;
	recordcol = colremain;
	recordrol = rolremain;
	for(i=index;i<=n;i++){
		//search for the available row
		if(rolremain[i] == 0){
			for(j=1;j<=m;j++){
				if(rolcolList[i][j] == 1){
                    rolremain |= colrolList[j];
                }
			}
			colremain |= rolcolList[i];
			if(Dfs(i, ++count))return true;
			rolremain = recordrol;
			colremain = recordcol;
		}
	}
	return false;
}

void Init()
{
	rolremain.reset();
	colremain.reset();
	int i;
	for(i=0;i<MAXN;i++){
		colrolList[i].reset();
		rolcolList[i].reset();
	}
}

int main()
{
	//freopen("input","r",stdin);
	int t,i,j,a;
	scanf("%d",&t);
	while(t--){
		Init();
		scanf("%d %d",&n,&m);
		//input the whole matrix
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				scanf("%d",&a);
				if(a){
					rolcolList[i][j] = 1;
					colrolList[j][i] = 1;
				}
			}
		}
		if(Dfs(1, 1))printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
