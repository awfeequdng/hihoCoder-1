void insertSort(vector<int> &nums)
{
    for(int i = 1; i < nums.size(); ++i)
    {
        int j = i - 1;
        int k = nums[i];
        while(j > -1 && k < nums[j])
        {
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = k;
    }
}
