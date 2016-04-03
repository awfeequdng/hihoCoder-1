/*#include <iostream>
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
}*/

/*#include <iostream>
using namespace std;
int main()
{
	int a = 1;
	int num = 8;
	while(num--)
	{
	a = a << 1;
	cout << a << endl;
	}
	return 0;
}*/

	#include <iostream>
	using namespace std;
	int main()
	{
		int num = 10;
		while(num--)
		{
			cout << num << ":" << (num & 1) << endl;
		}
		return 0;

	}