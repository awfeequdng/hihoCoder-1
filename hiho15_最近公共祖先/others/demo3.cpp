#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

const int maxn = 200009;
const int maxl = 21;

map <string, int> rn;
vector <int> e[maxn];
string name[maxn];
int n, m, tn, ath[maxn][maxl], d[maxn];

int getNum(string n) {
	map <string, int> :: iterator i = rn. find(n);
	if (i == rn. end()) {
		name[++ tn] = n;
		rn. insert(pair<string, int> (n, tn));
		return tn;
	}
	else
		return i-> second;
}

void buildTree() {
	queue <int> q;
	int p0 = 1;
	while (ath[p0][0])
		p0 = ath[p0][0];
	d[p0] = 1;
	q. push(p0);
	while (!q. empty()) {
		int p = q. front();
		q. pop();
		for (int i = 1; i < maxl; ++ i)
			ath[p][i] = ath[ath[p][i - 1]][i - 1];
		for (vector <int> :: iterator i = e[p]. begin(); i != e[p]. end(); ++ i) {
			q. push(*i);
			d[*i] = d[p] + 1;
		}
	}
}

int LCA(int p, int q) {
	if (d[p] < d[q])
		swap(p, q);
	for (int i = maxl - 1; i >= 0; -- i)
		if (d[ath[p][i]] >= d[q])
			p = ath[p][i];
	if (p == q)
		return p;
	for (int i = maxl - 1; i >= 0; -- i)
		if (ath[p][i] ^ ath[q][i])
			p = ath[p][i], q = ath[q][i];
	return ath[p][0];
}

int main() {
	cin. sync_with_stdio(0);
	cin >> n;
	tn = 0;
	while (n --) {
		string a, b;
		cin >> a >> b;
		int na = getNum(a), nb = getNum(b);
		ath[nb][0] = na;
		e[na]. push_back(nb);
	}
	buildTree();
	cin >> m;
	while (m --) {
		string a, b;
		cin >> a >> b;
		int na = getNum(a), nb = getNum(b);
		cout << name[LCA(na, nb)] << endl;
	}
}

