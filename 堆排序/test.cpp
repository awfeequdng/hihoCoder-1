#include <iostream>
#include <vector>
using namespace std;

void quickSort(vector<int> &nums, int left, int right)
{
    if(left >= right)
        return;
    int l = left;
    int r = right;
    int temp = nums[left];
    while(l < r)
    {
        while(l < r && nums[r] >= temp)
            r--;
        if(l < r)
        {
            nums[l] = nums[r];
            l++;
        }

        while(l < r && nums[l] < temp)
            l++;
        if(l < r)
        {
            nums[r] = nums[l];
            r--;
        }
    }
    nums[l] = temp;
    quickSort(nums, left, l-1);
    quickSort(nums, l+1, right);
}

int main()
{
    vector<int> nums;
    int num;
    while(cin >> num)
    {
        nums.push_back(num);
    }
    quickSort(nums, 0, nums.size()-1);
    for(const auto x : nums)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
