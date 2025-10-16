void map(int* array, int len, void(*callback)(int,int))
{
    int i;
    int array_local[5];
    for (i = 0; i < 5; i = i + 1)
    {
        if (i < len)
        {
            array_local[i] = array[i];
        }
    }
    for (i = 0; i < 5; i = i + 1)
    {
        if (i < len)
        {
            callback(i, array_local[i]);
        }
    }
    return;
}
