void transpose(int dest[5][5], int src[5][5], int src_h, int src_w)
{
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1)
    {
        for (j = 0; j < 5; j = j + 1)
        {
            if (i < src_h && j < src_w)
            {
                dest[j][i] = src[i][j];
            }
        }
    }
    return;
}
