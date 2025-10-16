int sort_array(int nums[5])
{
    int i;
    int j;
    int temp;
    for (i = 0; i < 5; i = i + 1)
    {
        for (j = i + 1; j < 5; j = j + 1)
        {
            if (nums[i] > nums[j])
            {
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }
    return;
}
