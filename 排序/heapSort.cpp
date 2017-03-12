void heapAdjust(vector<int> &nums, int i, int len)
{
    int child;
    int temp;
    for(; 2 * i + 1 < len; i = child)
    {
        child = 2 * i + 1;
        if(child < len - 1 && nums[child+1] > nums[child])
            child++;
        if(nums[i] < nums[child])
        {
            temp = nums[i];
            nums[i] = nums[child];
            nums[child] = temp;
        }
        else break;
    }
}

void heapSort(vector<int> &nums)
{
    int i;
    int len = nums.size();
    for(int i = len/2 - 1; i >= 0; i--)
    {
        heapAdjust(nums, i, len);
    }

    for(i = len-1; i > 0; i--)
    {
        int temp = nums[0];
        nums[0] = nums[i];
        nums[i] = temp;
        heapAdjust(nums, 0, i);
    }
}
