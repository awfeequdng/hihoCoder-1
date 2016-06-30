#include <iostream>
#include <string>
#include <cstring>
#include <bitset>

using namespace std;

struct Trie {
	Trie *subs[26];
	bitset<26> fins;
	Trie *back;
	Trie() : fins(0), back(NULL) {
		memset(subs, 0, sizeof(subs));
	}

	void genSkips(const string &p, int skips[]) {
		const int M = p.length();
		skips[0] = -1;
		int i = 1, j = skips[i - 1];
		while ( i < M ) {
			if ( j < 0 ) {
				skips[i ++] = j = 0;

			} else if ( p[i - 1] == p[j] ) {
				skips[i ++] = ++ j;

			} else {
				j = skips[j];
			}
		}
	}

	void insert(const string &p) {
		const int M = p.length();
		if ( M == 0 ) return;
		int skips[M];
		genSkips(p, skips);
		Trie *nodes[M];

		Trie *cur = this;
		Trie *last = cur;
		int c = 0;
		for (int i = 0; i < M; i ++) {
			c = p[i] - 'a';
			if ( cur->subs[c] == NULL ) {
				cur->subs[c] = new Trie;
			}
			last = cur;
			nodes[i] = cur;
			cur = cur->subs[c];
		}
		last->fins[c] = true;

		for (int i = 0; i < M; i ++) {
			if ( skips[i] >= 0 ) {
				nodes[i]->back = nodes[skips[i]];
			}
		}
	}

	bool find(const string &s) {
		const int N = s.length();
		int i = 0;
		Trie *cur = this;
		while ( i < N ) {
			int c = s[i] - 'a';
			if ( cur == NULL ) {
				i ++;
				cur = this;
			} else if ( cur->subs[c] ) {
				if ( cur->fins[c] ) return true;
				cur = cur->subs[c];
				i ++;
			} else {
				cur = cur->back;
			}
		}
		return false;
	}
};

int main() {
	Trie trie;
	int N;
	cin >> N;
	for (int i = 1; i <= N; i ++) {
		string p;
		cin >> p;
		trie.insert(p);
	}
	string s;
	cin >> s;
	bool res = trie.find(s);
	cout << (res ? "YES" : "NO") << endl;
	return 0;
}