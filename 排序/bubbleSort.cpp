void bubbleSort(vector<int> &nums)
{
    for(int i = 0; i < nums.size()-1; ++i)
    {
        for(int j = nums.size()-1; j > i; --j)
        {
            if(nums[j] < nums[j-1])
            {
                int temp = nums[j];
                nums[j] = nums[j-1];
                nums[j-1] = temp;
            }
        }
    }
}
