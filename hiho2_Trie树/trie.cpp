#include <iostream>

using namespace std;

typedef struct trie
{
    char c;
    int count;
    struct trie *next[26];
    void init()
    {
        c = ' ';
        count = 0;
        for(int i = 0; i < 26; ++i)
            next[i] = NULL;
    }
}trie, *Trie;

//声明全局变量根节点
Trie root = NULL;

void insert(string s)
{
    Trie p = root;
    for(unsigned i = 0; i < s.size(); ++i)
    {
        int temp = s[i] - 'a';
        if(p->next[temp])
        {
            ++p->next[temp]->count;
        }
        else
        {
            Trie q = new trie;
            q->init();
            q->count = 1;
            q->c = s[i];
            p->next[temp] = q;
        }
        p = p->next[temp];
    }
}

void query(string s)
{
    Trie p = root;
    int res = 0;
    for(unsigned i = 0; i < s.size(); ++i)
    {
        int temp = s[i] - 'a';
        if(!p->next[temp])
        {
            res = 0;
            break;
        }
        else
        {
            p = p->next[temp];
            res = p ->count;
        }
    }
    cout << res << endl;
}

int main()
{
    root = new trie;
    root->init();
    int m, n;
    string str;
    cin >> m;
    while(m--)
    {
        cin >> str;
        insert(str);
    }
    cin >> n;
    while(n--)
    {
        cin >> str;
        query(str);
    }
    return 0;
}
