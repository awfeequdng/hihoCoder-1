#include <iostream>

using namespace std;

typedef struct node
{
    int key;
    node *father, *left, *right;
    node() {}
    node(int key_) : key(key_)
    {
        this->father = NULL;
        this->left = NULL;
        this->right = NULL;
    }
}*Node;

//加入root结点
Node root = NULL;


int main()
{
    return 0;
}
