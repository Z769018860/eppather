void map(int* array, int len, void(*callback)(int,int))
{
    int i;
    for(i = 0; i < len; i = i + 1)
    {
        callback(i, array[i]);
    }
    return;
}
