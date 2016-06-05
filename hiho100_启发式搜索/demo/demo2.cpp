#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <math.h>
using namespace std;

int factorial[9] = { 1 };
const int number[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const int dir[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
inline int fact(int k)
{
	return factorial[k];
}

int num2order(int val)
{
	int n[9];
	for (int i = 8, v = val; i >= 0; i--, v /= 10) {
		n[i] = v % 10;
	}

	int a[9] = { 0 };
	int k = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 9; j++) {
			if (n[j] < n[i])
				a[i]++;
		}
		k += a[i] * fact(8 - i);
	}
	return k;
}

int order2num(int k)
{
	int a[9] = { 0 };
	for (int i = 0, v = k; i < 9; i++) {
		a[i] = (v / fact(8 - i));
		v %= fact(8 - i);

	}

	int val = 0;
	list<int> q(number, number + 9);
	for (int i = 0; i < 9; i++) {
		list<int>::iterator p = q.begin();
		while (a[i]-- > 0) {
			p++;
		}
		val = val * 10 + *p;
		q.erase(p);
	}

	return val;
}

struct state
{
	int val;
	int f, g, h;

	state(int v_ = 123456789, int g_ = 0, int h_ = 0) :val(v_), g(g_), h(h_) {
		f = g + h;
	}

	friend bool operator< (const state& p, const state& q)
	{
		return p.f > q.f;
	}

};

int dis(int p[3][3])
{
	int ans = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (p[i][j] == 9)
				continue;
			int x = (p[i][j] - 1) / 3;
			int y = (p[i][j] - 1) % 3;
			
			ans += abs(x - i) + abs(y - j);
		}
	}

	return ans;
}

int Astar_search(int start)
{
	int board[3][3];
	for (int i = 2, v = start; i >= 0; i--) {
		for (int j = 2; j >= 0; j--, v /= 10) {
			board[i][j] = v % 10;
		}
	}

	priority_queue<state> open;
	vector<int> close(9 * fact(8), -1);

	open.push(state(start, 0, dis(board)));

	while (!open.empty() && close[0] == -1) {
		state s = open.top();
		open.pop();

		int k = num2order(s.val);
		if (close[k] != -1)
			continue;
		close[k] = s.g;

		for (int i = 2, v = s.val; i >= 0; i--) {
			for (int j = 2; j >= 0; j--, v /= 10) {
				board[i][j] = v % 10;
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == 9) {

					for (int t = 0; t < 4; t++) {
						int x = i + dir[t][0], y = j + dir[t][1];

						if (x >= 0 && x < 3 && y >= 0 && y < 3) {
							swap(board[i][j], board[x][y]);

							int u = 0;
							for (int p = 0; p < 3; p++) {
								for (int q = 0; q < 3; q++) {
									u = u * 10 + board[p][q];
								}
							}
							open.push(state(u, s.g + 1, dis(board)));

							swap(board[i][j], board[x][y]);
						}
					}

					break;
				}
			}
		}
	}

	return close[0];
}

int main()
{
	for (int i = 1; i < 9; i++) {
		factorial[i] = i* factorial[i - 1];
	}

	int t;
	cin >> t;
	while (t--) {
		int board[9];
		int val = 0;
		for (int i = 0; i < 9; i++) {
			cin >> board[i];
			if (board[i] == 0)
				board[i] = 9;
			val = val * 10 + board[i];
		}

		int c = Astar_search(val);
		if (c == -1) {
			cout << "No Solution!\n";
		}
		else {
			cout << c << endl;
		}

	}
	return 0;
}