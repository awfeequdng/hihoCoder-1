#include <iostream>
#include <map>
#define N 100010
using namespace std;
int n, m;

typedef struct node
{
    string name;
    int depth;
    int in, out;
    node* father;
    vector<node*> child;
    node(string name_) : name(name_)
    {
        depth = 0;
        in = 0;
        out = 0;
        father = NULL;
    }
    node(string name_, int depth_) : name(name_), depth(depth_)
    {
        in = 0;
        out = 0;
        father = NULL;
    }
}*Node;

int main()
{
    string fa, son;
    cin >> n;
    while(n--)
    {
        cin >> fa >> son;
    }
}
