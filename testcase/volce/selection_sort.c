void selectionSort(int arr[10])
{
    int i = 0;
    while (i < 9)
    {
        int min_idx = i;
        int j = i + 1;
        while (j < 9)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
            j = j + 1;
        }

        if (min_idx != i)
        {
            int tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }

        i = i + 1;
    }
}
