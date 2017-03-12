void merge(vector<int> &nums, int start, int mid, int end)
{
    int i = start;
    int j = mid + 1;
    int len = end - start + 1;
    vector<int> temp(len, 0);
    int k = 0;
    while( i < mid+1 && j < end+1)
    {
        if(nums[i] > nums[j])
            temp[k++] = nums[j++];
        else
            temp[k++] = nums[i++];
    }

    while(i < mid + 1)
    {
        temp[k++] = nums[i++];
    }
    while(j < end+1)
    {
        temp[k++] = nums[j++];
    }

    for(i = 0, j = start; j < end+1; i++, j++)
        nums[j] = temp[i];
}

void mergeSort(vector<int> &nums, int start, int end)
{
    if(start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(nums, start, mid);
        mergeSort(nums, mid+1, end);
        merge(nums, start, mid, end);
    }
}
