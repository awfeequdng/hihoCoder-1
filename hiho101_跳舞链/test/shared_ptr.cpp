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
    shared_ptr<string> p3 = make_shared<string>(10, '9');
    cout << *p3 << endl;
    shared_ptr<int> p4 = make_shared<int>();
    cout << *p4 << endl;
    return 0;
}
