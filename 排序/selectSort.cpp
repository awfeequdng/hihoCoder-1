void selectSort(vector<int> &nums)
{
    for(int i = 0; i < nums.size(); ++i)
    {
        int index = i;
        for(int j = i+1; j < nums.size(); ++j)
        {
            if(nums[j] < nums[index])
                index = j;
        }
        if(index != i)
        {
            int temp = nums[i];
            nums[i] = nums[index];
            nums[index] = temp;
        }
    }
}
