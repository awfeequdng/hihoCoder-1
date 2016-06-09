#include <iostream>
#include <memory>
#include <string>
using namespace std;

int main()
{
    shared_ptr<string> p1 = make_shared<string>("Hello, World!");
    cout << *p1 << endl;
    shared_ptr<int> p2 = make_shared<int>(22);
    cout << *p2 << endl;
    return 0;
}
