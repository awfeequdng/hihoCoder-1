#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

int main()
{
    shared_ptr<vector<int>> v = make_shared<vector<int>>(10, -1);
    for(const auto x : *v)
        cout << x << endl;
    return 0;
}
