#include <iostream>
#include <vector>
using namespace std;

typedef struct node
{
    string str;
    int data;
    node(string s) : str(s)
    {
        data = 2;
    }
}*Node;

int main()
{
    vector<Node> vec;
    string temp;
    for(int i = 0; i < 5; ++i)
    {
        cin >> temp;
        vec.push_back(new node(temp));
    }
    for(const auto x : vec)
    {
        cout << x->str << " " << x->data << endl;
    }
    return 0;
}
