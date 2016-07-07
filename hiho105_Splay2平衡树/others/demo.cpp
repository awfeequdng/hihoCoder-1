#include <cstdio>
#include <map>
#include <cstring>
using namespace std;
char c[5];
int main(){
  int n,a,b,val,k;

  map<int,int> m;
  map<int,int>::iterator it1,it2;
  scanf("%d",&n);
  while(n--){
    scanf("%s",c);
    if(c[0] == 'I'){
      scanf("%d%d",&a,&val);
      m.insert(pair<int,int>(a,val));
    }
    else if(c[0] == 'Q'){
      scanf("%d%d",&a,&b);
      if(a <= b)
      {
        int sum = 0;
        it1 = m.find(a);
        it2 = m.upper_bound(b);

        for(map<int,int>::iterator it = it1;it != it2;it++)
        {
          sum += it->second;
        }
        printf("%d\n",sum);
      }
    }
    else if(c[0] == 'D'){
      scanf("%d%d",&a,&b);
      it1 = m.lower_bound(a);
      it2 = m.upper_bound(b);
      while(it1 != m.end() && it1 != it2)
        it1 = m.erase(it1);
    }
    else if(c[0] == 'M'){
       scanf("%d%d%d",&a,&b,&k);
       if(a <= b)
       {
         it1 = m.find(a);
         it2 = m.upper_bound(b);

         for(map<int,int>::iterator it = it1;it != m.end() && it != it2;it++)
         {
           (*it).second += k;
         }
       }
    }
  }
}
