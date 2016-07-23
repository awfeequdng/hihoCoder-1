#include <iostream>
#include <map>
#include <vector>
#include <string>
#define N 100010
using namespace std;

typedef struct node
{
    string name;
    int color;
    node* father;
    vector<node*> child;
    node(string name_) : name(name_)
    {
        color = 0;
        father = NULL;
    }
}*Node;

string res[N];
map<string, Node> tree;
typedef pair<Node, int> nodeNum;
map<string, vector<nodeNum>> query;

Node findRoot(Node p)
{
    if(p->color == 1)
        return p;
    else
    {
        p->father = findRoot(p->father);
        return p->father;
    }
}

void dfs(Node p)
{
    p->color = 1;
    vector<nodeNum> &pQuery = query[p->name];
    for(int i = 0; i < pQuery.size(); ++i)
    {
        Node pChild = pQuery[i].first;
        int id = pQuery[i].second;
        if(pChild->color == 0)
            continue;
        res[id] = findRoot(pChild)->name;
    }

    for(int i = 0; i < p->child.size(); ++i)
    {
        dfs(p->child[i]);
    }

    p->color = 2;
}

int main()
{
    int n, m;
    string s1, s2;
    Node root = NULL;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> s1 >> s2;
        if(tree.find(s1) == tree.end())
            tree[s1] = new node(s1);
        if(tree.find(s2) == tree.end())
            tree[s2] = new node(s2);
        tree[s1]->child.push_back(tree[s2]);
        tree[s2]->father = tree[s1];

        if(i == 0)
            root = tree[s1];
    }

    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        cin >> s1 >> s2;
        if(query.find(s1) == query.end())
            query[s1] = vector<nodeNum>();
        if(query.find(s2) == query.end())
            query[s2] == vector<nodeNum>();
        Node p1 = tree[s1];
        Node p2 = tree[s2];
        query[s1].push_back(make_pair(p2, i));

        if(s1 != s2)
            query[s2].push_back(make_pair(p1, i));
    }

    dfs(root);

    for(int i = 0; i < m; ++i)
        cout << res[i] << endl;

    return 0;
}
