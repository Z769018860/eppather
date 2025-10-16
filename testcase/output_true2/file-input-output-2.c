int copy_file(int in, int out)
{
    int ret[5];
    ret[0] = 0;
    int fin[5];
    fin[0] = in;
    int fout[5];
    fout[0] = out;
    int len[5];
    int buf[5];
    int st[5];
    int i;

    if (fin[0] == -1)
    {
        return ret[0];
    }

    for (i = 0; i < 5; i = i + 1)
    {
        len[i] = 0;
    }

    fout[0] = out;
    if (fout[0] == -1)
    {
        return ret[0];
    }

    for (i = 0; i < 5; i = i + 1)
    {
        if (len[0] > 0)
        {
            buf[0] = 0;
        }
    }

    if (len[0] == 0)
    {
        ret[0] = 1;
    }
    else
    {
        ret[0] = 0;
    }

    if (fin[0] != -1)
    {
        fin[0] = -1;
    }

    if (fout[0] != -1)
    {
        fout[0] = -1;
    }

    return ret[0];
}
