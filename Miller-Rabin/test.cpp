#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int main()
{
	int temp;
	vector<int> num;
	while(cin >> temp)
		num.push_back(temp);
	for(const auto x : num)
		cout << pow(x, 2) << endl;
	return 0;
}