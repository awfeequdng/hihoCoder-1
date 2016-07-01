#include <iostream>
#include <queue>
#include <string>

using namespace std;

typedef class node
{
    public:
        node* prev;
        node* next[26];
        bool bad;
        node()
        {
            prev = NULL;
            for(int i = 0; i < 26; ++i)
                next[i] = NULL;
            bad = false;
        }
}*Node;

typedef class trieTree
{
    public:
        trieTree()
        {
            root = new node();
        }
        void insert(string &str);
        void build();
        bool search(string &str);
    private:
        Node root;
}*TrieTree;

void trieTree::insert(string &str)
{
    int len = str.size();
    Node proot = root;
    for(int i = 0; i < len; ++i)
    {
        if(proot->next[str[i] - 'a'] == NULL)
        {
            proot->next[str[i] - 'a'] = new node();
        }
        proot = proot->next[str[i] - 'a'];
    }
    proot->bad = true;
}

void trieTree::build()
{
    queue<Node> treeQue;
    Node proot = root;
    for(int i = 0; i < 26; ++i)
    {
        if(proot->next[i])
        {
            proot->next[i]->prev = root;
            treeQue.push(proot->next[i]);
        }
    }
    while(!treeQue.empty())
    {
        proot = treeQue.front();
        treeQue.pop();
        for(int i = 0; i < 26; ++i)
        {
            Node prev = proot->prev;
            if(proot->next[i])
            {
                while(prev)
                {
                    if(prev->next[i])
                    {
                        proot->next[i]->prev = prev->next[i];
                        if(prev->next[i]->bad)
                            proot->next[i]->prev->bad = true;
                        break;
                    }
                    else
                        prev = prev->prev;
                }
                if(prev == NULL)
                {
                    proot->next[i]->prev = root;
                }
                treeQue.push(proot->next[i]);
            }
        }
    }
}

bool trieTree::search(string &str)
{
    int len = str.size();
    Node proot = root;
    for(int i = 0; i < len; ++i)
    {
        while(1)
        {
            if(proot->next[str[i] - 'a'])
            {
                proot = proot->next[str[i]- 'a'];
                if(proot->bad)
                    return true;
                break;
            }
            else
                proot = proot->prev;
            if(proot == root || proot == NULL)
            {
                proot = root;
                break;
            }
        }
    }
    return false;
}

int main()
{
    int n;
    cin >> n;
    string str, temp;
    trieTree T;
    while(n--)
    {
        cin >> temp;
        T.insert(temp);
    }
    T.build();

    cin >> str;
    if(T.search(str))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
