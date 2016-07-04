#include <iostream>
#include <set>

using namespace std;

typedef struct node
{
    int key;
    int id;
    bool color;
    node *parent, *leftchild, *rightchild;
    node(){}
    node(int id_, int key_) : id(id_), key(key_)
    {
        parent = NULL;
        leftchild = NULL;
        rightchild = NULL;
    }
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
    int id, key;
    for(int i = 0; i < 5; ++i)
    {
        cin >> id >> key;
        s.insert(new node(id, key));
    }
    for(const auto x : s)
    {
        cout << x->id << ' ' << x->key << endl;
    }
    return 0;
}
