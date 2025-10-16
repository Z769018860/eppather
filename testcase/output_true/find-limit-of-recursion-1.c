void recurse(int i)
{
    int arr[5];
    arr[0] = i;
    for (int j = 0; j < 5; j = j + 1)
    {
        if (j == 0)
        {
            arr[0] = arr[0];
        }
    }
    recurse(arr[0] + 1);
    return;
}
