#include <iostream>
#include <map>
using namespace std;
map<string, string> str;
map<string, string>::iterator it, it1, it2;

string find_represent(string s)
{
    it = str.find(s);
    if(s == (*it).second)
        return s;
    else
    {
        (*it).second = find_represent((*it).second);
        return (*it).second;
    }
}


int main()
{
    int n, oper;
    cin >> n;
    string s1, s2;
    while(n--)
    {
        cin >> oper >> s1 >> s2;
        if(oper)
        {
            string rep_s1 = find_represent(s1);
            string rep_s2 = find_represent(s2);
            if(rep_s1 == rep_s2)
                cout << "yes" << endl;
            else
                cout << "no" << endl;
        }
        else
        {
            it1 = str.find(s1);
            it2 = str.find(s2);
            if(it1 == str.end())
            {
                it1 = str.insert(make_pair(s1, s1)).first; //map.insert的返回值是pair<iterator, bool>，其中bool变量用于指示是否插入成功
            }
            if(it2 == str.end())
            {
                it2 = str.insert(make_pair(s2, s2)).first;
            }
            string rep_s1 = find_represent(s1);
            string rep_s2 = find_represent(s2);
            it = str.find(rep_s2);
            (*it).second = rep_s1;
        }
    }
    /*
    for(const auto x : str)
    {
        cout << x.first << " " << x.second << endl;
    }
    */
    return 0;
}
