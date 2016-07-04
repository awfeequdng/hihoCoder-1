#include <iostream>
#include <set>
#define MAX_V 10000000
#define MIN_V 0
using namespace std;

typedef struct node
{
    long long id;
    long long key;
    node() { }
    node(long long id_, long long key_) : id(id_), key(key_) {}
    bool operator < (const node *a)
    {
        if(this->id != a->id)
            return this->id < a->id;
        else
            return this->key < a->key;
    }
}*Node;

int main()
{
    set<Node> s;
    set<Node>::iterator it;
    long long n;
    long long a, b, c, d;
    char ch;
    cin >> n;
    long long res = 0;
    while(n--)
    {
        res = 0;
        bool flag = false;
        cin >> ch >> a >> b;
        if(ch == 'I')
        {
            for(it = s.begin(); it != s.end(); it++)
            {
                if((*it)->id == a)
                    flag = true;
            }
            if(!flag)
            {
                if(b < MIN_V)
                    b = MIN_V;
                else if(b > MAX_V)
                    b = MAX_V;
                s.insert(new node(a, b));
            }
        }
        else if(ch == 'Q')
        {
            for(it = s.begin(); it != s.end(); it++)
            {
                if((*it)->id >= a && (*it)->id <= b)
                    res += (*it)->key;
            }
            if(res > 0)
                cout << res << endl;
        }
        else if(ch == 'M')
        {
            cin >> d;
            for(it = s.begin(); it != s.end(); it++)
            {
                if((*it)->id >= a && (*it)->id <= b)
                {
                    (*it)->key += d;
                    if((*it)->key < MIN_V)
                        (*it)->key = MIN_V;
                    else if((*it)->key > MAX_V)
                        (*it)->key = MAX_V;
                }
            }
        }
        else
        {
            for(it = s.begin(); it != s.end(); it++)
            {
                if((*it)->id >= a && (*it)->id <= b)
                {
                    s.erase(*it);
                }
            }
        }
    }
    return 0;
}
