void insertionSort(int arr[10])
{
    int i = 1;
    while (i < 9)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
        i = i + 1;
    }
}
