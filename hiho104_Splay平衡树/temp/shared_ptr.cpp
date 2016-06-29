#include <iostream>
#include <memory>

using namespace std;

typedef struct node
{
    int data;
    shared_ptr<node> next;
    node() {}
    node(int data_) : data(data_) {}
}*Node;

int main()
{
    shared_ptr<node> root(new node(0));
    auto p = root;
    int temp;
    while(cin >> temp)
    {
        shared_ptr<node> q(new node(temp));
        p->next = q;
        p = q;
    }
    p->next = NULL;
    p = root;
    while(p->next)
    {
        cout << p->next->data << endl;
        p = p->next;
    }
    return 0;
}
