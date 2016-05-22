#include <iostream>
#include <vector>
#include <queue>
using namespace std;

char pos[6];
queue<string> status;

bool check(string *s)
{
    
}

int step(string *s)
{
   status.push(sta);
   while(!status.empty())
   {
       auto now_status = queue.pop();
       for(int i = 0; i < 3; ++i)
       {
           for(int j = 0; j < 8; ++j)
           {
               auto next_status = move(now_status, i, j);
               if(next_status != "IIIIII")
               {
                   if(check(next_status))
                       return step(next_status) + 1;
               }
           }
       }
   }

}

int main()
{
    int num, count;
    cin >> num;
    while(num--)
    {
        string position, temp;
        for(int i = 0; i < 3; ++i)
        {
            cin >> temp;
            position += temp;
        }
        count = 0;
        for(auto const x : position)
        {
            if(x > 64)
                pos[count++] = x - 65 + 48;
            else if( x > 48)
                pos[count++] = x - 1;
            else
                continue;
        }
    }
    return 0;
}
