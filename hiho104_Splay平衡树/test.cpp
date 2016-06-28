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

int main()
{
    return 0;
}
