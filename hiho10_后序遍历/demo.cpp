#include <iostream>
#include <string>

using namespace std;

string postOrder(string str1, string str2)
{
    string res, root, left, right;
    root = str1.substr(0, 1);
    int lenLeft = str2.find(root[0], 0);
    int lenRight = str1.size() - 1 - lenLeft;
    //string preLeft = str1.substr(1, lenLeft);
    //string preRight = str1.substr(lenLeft+1);
    //string midLeft = str2.substr(0, lenLeft);
    //string midRight = str2.substr(lenLeft+1);
    if(lenLeft == 1 || lenRight == 1)
    {
        if(lenLeft == 1)
            left = str2.substr(0, lenLeft);
        if(lenRight == 1)
            right = str2.substr(lenLeft+1);
    }
    else
    {
        left = postOrder(str1.substr(1, lenLeft), str2.substr(0, lenLeft));
        right = postOrder(str1.substr(lenLeft+1), str2.substr(lenLeft+1));
    }
    return res = left + right + root;
}

int main()
{
    string str1;
    string str2;
    cin >> str1 >> str2;
    cout << postOrder(str1, str2) << endl;
    return 0;
}
