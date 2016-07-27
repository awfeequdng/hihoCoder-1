#include <iostream>
#include <algorithm>
#include <map>
#define N 100010
using namespace std;

typedef struct node
{
    string name;
    int depth;
    int id;
    node* father;
    vector<node*> child;
    node(string name_) : name(name_)
    {
        depth = 0;
        id = 0;
        father = NULL;
    }
}*Node;

int n, m;
int cnt = 0;
int num = 0;
Node root = NULL;
map<string, Node> tree;
map<string, int> seq;
map<int, string> seq2;
vector<pair<int, int>> dp[19];

void dfs(Node p, int d)
{
    p->depth = d;
    p->id = num++;

    seq[p->name] = cnt;
    seq2[cnt] = p->name;
    dp[0].push_back(make_pair(p->depth, cnt++));

    for(int i = 0; i < p->child.size(); ++i)
    {
        dfs(p->child[i], d+1);
    }

    if(p->father)
    {
        seq[p->father->name] = cnt;
        seq2[cnt] = p->father->name;
        dp[0].push_back(make_pair(p->father->depth, cnt++));
    }
}

void st()
{
    //因为是n行，对应n+1个结点，所以是2 × n + 1
    int k = log2(2 * n + 1);
    for(int i = 1; i <= k; ++i)
    {
        for(int j = 0; j + (1<<i) - 1 < 2 * n + 1; ++j)
        {
            int next = j + (1<<(i-1));
            if(dp[i-1][j].first < dp[i-1][next].first)
                dp[i].push_back(dp[i-1][j]);
            else
                dp[i].push_back(dp[i-1][next]);
        }
    }
}

int main()
{
    string s1, s2;
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

    dfs(root, 0);
    st();

    /*for(int i = 0; i <= log2(n * 2 + 1); ++i)
    {
        for(const auto x : dp[i])
        {
            cout << x.first << " " << x.second << endl;
        }
    }*/
    cin >> m;
    while(m--)
    {
        cin >> s1 >> s2;
        int l, r, res, temp;
        l = seq[s1];
        r = seq[s2];
        if(l > r)  //这里需要判断输入的字符串的顺序
            swap(l, r);
        int k = log2(r - l + 1);
        if(dp[k][l].first < dp[k][r - (1<<k) + 1].first)
            res = dp[k][l].second;
        else
            res = dp[k][r - (1<<k) + 1].second;
        cout << seq2[res] << endl;
    }
    return 0;
}
