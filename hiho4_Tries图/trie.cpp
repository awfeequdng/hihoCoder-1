#include <iostream>
#include <queue>
#include <string>

using namespace std;

typedef class node
{
    public:
        node *next[26];
        node *prev;
        bool bad;
        node()
        {
            for(int i = 0; i < 26; ++i)
                this->next[i] = NULL;
            this->prev = NULL;
            bad = false;
        }
}*Node;

typedef class ttree
{
    public:
        ttree()
        {
            root = new node();
        }
        void insert(string &word);
        void build();
        bool search(string &word);
    private:
        Node root;
}*TTree;

void ttree::insert(string &word)
{
    int len = word.size();
    Node proot = root;
    for(int i = 0; i < len; ++i)
    {
        if(proot->next[word[i] - 'a'] == NULL)
            proot->next[word[i] - 'a'] = new node();
        proot = proot->next[word[i] - 'a'];
    }
    proot->bad = true;
}

void ttree::build()
{
    Node proot = root;
    queue<Node> Q;
    //proot->prev = root;
    for(int i = 0; i < 26; ++i)
    {
        if(proot->next[i] != NULL)
        {
            proot->next[i]->prev = root;
            Q.push(proot->next[i]);
        }
    }
    while(!Q.empty())
    {
        Node proot = Q.front();
        Q.pop();
        for(int i = 0; i < 26; ++i)
        {
            Node p = proot->next[i];
            if(p && p->bad == false)
            {
                Node prev = proot->prev;
                while(prev)
                {
                    if(prev->next[i])
                    {
                        p->prev = prev->next[i];
                        if(prev->next[i]->bad)
                            p->bad = true;
                        break;
                    }
                    else
                        prev = prev->prev;
                }
                if(p->prev = NULL)
                    p->prev = root;
                Q.push(p);
            }
        }
    }
}

bool ttree::search(string &word)
{
    int len = word.size();
    Node proot = root;
    for(int i = 0; i < len; ++i)
    {
        while(true)
        {
            if(proot->next[word[i] - 'a'])
            {
                proot = proot->next[word[i] - 'a'];
                if(proot->bad == true)
                    return true;
                break;
            }
            else
                proot = proot->prev;
            if(proot == NULL || proot == root)
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
    string temp;
    string str;
    int num;
    ttree T;
    cin >> num;
    while(num--)
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
