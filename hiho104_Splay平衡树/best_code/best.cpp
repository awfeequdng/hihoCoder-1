#include<cstdio>
#include<set>
#include<cstring>

std::set<int> s;
int n,a,b;
char c;
int main(){
	scanf("%d\n",&n);
	std::set<int>::iterator it;
	while(n--){
		scanf("%c",&c);
		if(c=='I'){
			scanf("%d%c",&a,&c);
			s.insert(a);
		}
		else if(c=='Q'){
			scanf("%d%c",&a,&c);
			it=s.upper_bound(a);
			printf("%d\n",*(--it));
		}
		else if(c=='D'){
			scanf("%d%d%c",&a,&b,&c);
			it=s.lower_bound(a);
			while(it!=s.end()&&*it<=b)
				s.erase(it++);
		}
	}
}