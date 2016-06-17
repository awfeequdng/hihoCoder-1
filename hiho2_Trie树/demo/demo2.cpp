//Trie tree

#include <iostream>
#include <string>
using namespace std;

typedef struct trie
{
	char c;
	int count;
	struct trie* next[26];
} Trie;

int main()
{
	Trie* root = new Trie;
	for (unsigned i(0); i < 26; ++i)
		root->next[i] = NULL;
	int n, m;
	string s;
	cin >> n;
	while (n--)
	{
		cin >> s;
		Trie* p = root;
		for (unsigned i(0); i < s.size(); ++i)
		{
			unsigned j = s[i] - 'a';
			if (p->next[j])
			{
				++p->next[j]->count;
			}
			else
			{
				Trie* q = new Trie;
				q->c = s[i];
				q->count = 1;
				for (unsigned k(0); k < 26; ++k)
					q->next[k] = NULL;
				p->next[j] = q;
			}
			p = p->next[j];
		}
	}
	cin >> m;
	while (m--)
	{
		cin >> s;
		bool flag = false;
		Trie* p = root;
		for (unsigned i(0); i < s.size(); ++i)
		{
			unsigned j = s[i] - 'a';
			if (!p->next[j])
			{
				flag = true;
				break;
			}
			p = p->next[j];
		}
		if (flag) cout << '0' << endl;
		else cout << p->count << endl;
	}
	return 0;
}
