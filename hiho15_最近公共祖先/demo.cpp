#include <iostream>
#include <map>
#include <vector>
using namespace std;
enum color {white, grey, black};

typedef struct node
{
    string name;
    color col;
    node(string name_) : name(name_)
    {
        col = white;
    }
}*Node;

map<string, vector<Node>> tree;
map<string, vector<Node>>::iterator it;

int main()
{
    int n;
    string fa, son;
    cin >> n;
    while(n--)
    {
        cin >> fa >> son;
        it = tree.find(fa);
        if(it == tree.end())
        {
            vector<Node> vec;
            vec.push_back(new node(son));
            tree.insert(make_pair(fa, vec));
        }
        else
        {
            (*it).second.push_back(new node(son));
        }
    }
    return 0;
}
