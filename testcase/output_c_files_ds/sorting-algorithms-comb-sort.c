void Combsort11(int a[100], int nElements)
{
    int i;
    int j;
    int gap;
    int swapped;
    int temp;
    
    gap = nElements;
    swapped = 1;
    for (; gap > 1 || swapped == 1; )
    {
        gap = gap * 10;
        gap = gap / 13;
        if (gap == 9 || gap == 10)
        {
            gap = 11;
        }
        if (gap < 1)
        {
            gap = 1;
        }
        swapped = 0;
        for (i = 0, j = gap; j < nElements; i = i + 1, j = j + 1)
        {
            if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                swapped = 1;
            }
        }
    }
    return;
}
