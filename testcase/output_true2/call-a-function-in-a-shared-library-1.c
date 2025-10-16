int myopenimage(int in[5])
{
    static int handle[5];
    handle[0] = handle[0] + 1;
    return handle[0] - 1;
}

int openimage(int imglib[5], int extopenimage[5], int imghandle[5])
{
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        imglib[i] = 0;
        extopenimage[i] = 0;
        imghandle[i] = 0;
    }
    if (imglib[0] != 0)
    {
        extopenimage[0] = 1;
        imghandle[0] = extopenimage[0];
    }
    else
    {
        int in[5];
        for (i = 0; i < 5; i = i + 1)
        {
            in[i] = 0;
        }
        imghandle[0] = myopenimage(in);
    }
    return;
}
