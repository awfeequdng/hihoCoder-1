#include <iostream>
using namespace std;

typedef struct node
{
    int key;
    int num;
    node *father, *left, *right;
    node(int key) : key(key_)
    {
        num = 1;
        father = NULL;
        left = NULL;
        right = NULL;
    }
}
