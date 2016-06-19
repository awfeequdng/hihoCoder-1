#include <cstdio>
#include <cstring>
#include <algorithm> 
#include <vector>
 
#define FOR(i,A,s) for(int i=A[s];i!=s;i=A[i])
using namespace std;
 
const int maxnode=3024;
const int maxm=400;
struct DLX{
    int n,sz;
    int S[maxm];
    int L[maxnode],R[maxnode],U[maxnode],
        D[maxnode];
    int row[maxnode],col[maxnode];
    int ansd,ans[maxm*2]; 
         
    void init(int n)
    {
        for(int i=0;i<=n;i++)
        {
            U[i]=i;D[i]=i;L[i]=i-1;R[i]=i+1;    
        }
        R[n]=0;L[0]=n;
        sz=n+1;
        memset(S,0,sizeof(S));
    }
     
    void AddRow(int r,vector<int> clms)
    {
        int frs=sz;
        for(int i=0;i<clms.size();i++)
        {
            int c=clms[i];
            L[sz]=sz-1;R[sz]=sz+1;D[sz]=D[c];U[sz]=c;
            U[D[sz]]=sz;D[c]=sz;
            row[sz]=r;col[sz]=c;
            S[c]++;sz++;
        }
        R[sz-1]=frs;L[frs]=sz-1;
    }
     
    void remove(int c)
    {
        L[R[c]]=L[c];R[L[c]]=R[c];
        FOR(i,D,c)
            FOR(j,R,i) 
            {
                U[D[j]]=U[j];
                D[U[j]]=D[j];
                --S[col[j]];
            }
    }
     
    void restore(int c)
    {
        FOR(i,D,c)
            FOR(j,L,i)
            {
                ++S[col[j]];
                D[U[j]]=j;
                U[D[j]]=j;
            }
        L[R[c]]=c;
        R[L[c]]=c;
    }
     
    bool dfs(int d)
    {
        if(R[0]==0)
        {
        	ansd=d;
            return true;
        }
        int c=R[0];
        FOR(i,R,0) if(S[i]<S[c]) c=i;
        remove(c);
        FOR(i,D,c)
        {
        	ans[d] = row[i];
            FOR(j,R,i) remove(col[j]);
            if(dfs(d+1)) return true;
            FOR(j,L,i) restore(col[j]);
        }
        restore(c);
        return false;
    }
}solver;

const int SLOT=0;
const int ROW=1;
const int COL=2;
const int SUB=3;

int encode(int a,int b,int c){
	return a*81+b*9+c+1;
}

void decode(int code,int& a,int& b,int& c){
	code--;
	c=code%9; code/=9;
	b=code%9; code/=9;
	a=code;
}

int puzzle[9][9];
int main() 
{
	int T;
	scanf("%d",&T); 
    vector<int> st;
    while(T--)
    {
        solver.init(324);
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                scanf("%d",&puzzle[i][j]);
                for(int v=0;v<9;v++){
					if( !puzzle[i][j] || puzzle[i][j]==v+1){
						st.clear();
						st.push_back(encode(SLOT,i,j));
						st.push_back(encode(ROW,i,v));
						st.push_back(encode(COL,j,v));
						st.push_back(encode(SUB,(i/3)*3+j/3,v));
						solver.AddRow(encode(i,j,v),st);
						if(puzzle[i][j]==v+1) break;
					}
				}
            } 
        }
        solver.dfs(0);
        for(int i=0;i<solver.ansd;i++){
        	int r,c,v;
        	decode(solver.ans[i],r,c,v);
        	puzzle[r][c]=v+1;
		}
		for(int i=0;i<9;i++){
			for(int j=0;j<8;j++)
				printf("%d ",puzzle[i][j]);
			printf("%d\n",puzzle[i][8]);
		}
    }
    return 0;
}