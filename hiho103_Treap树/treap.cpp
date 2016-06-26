#include <iostream>

using namespace std;

typedef struct node
{
    int key;
    int weight;
    struct node *fa, *lchild, *rchild;
    node() {}
    node(int key_, int weight_) : key(key_), weight(weight_) {}
}*Node;

int main()
{
    Node root = new node;
    *root = node(1, 2);
    cout << root->key << " " << root->weight << endl;
    return 0;
}
