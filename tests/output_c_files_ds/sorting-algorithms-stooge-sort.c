void StoogeSort(int a[15], int i, int j)
{
    int t;
    if (a[j] < a[i])
    {
        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
    if (j - i > 1)
    {
        t = (j - i + 1) / 3;
        StoogeSort(a, i, j - t);
        StoogeSort(a, i + t, j);
        StoogeSort(a, i, j - t);
    }
    return;
}
