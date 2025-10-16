void Combsort11(int a[5], int nElements)
{
    int i[5];
    int j[5];
    int gap[5];
    int swapped[5];
    int temp[5];
    
    gap[0] = nElements;
    swapped[0] = 1;
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1)
    {
        if (gap[0] > 1 || swapped[0] == 1)
        {
            gap[0] = gap[0] * 10 / 13;
            if (gap[0] == 9 || gap[0] == 10)
            {
                gap[0] = 11;
            }
            if (gap[0] < 1)
            {
                gap[0] = 1;
            }
            swapped[0] = 0;
            for (i[1] = 0, j[0] = gap[0]; j[0] < nElements; i[1] = i[1] + 1, j[0] = j[0] + 1)
            {
                if (a[i[1]] > a[j[0]])
                {
                    temp[0] = a[i[1]];
                    a[i[1]] = a[j[0]];
                    a[j[0]] = temp[0];
                    swapped[0] = 1;
                }
            }
        }
    }
    return;
}
