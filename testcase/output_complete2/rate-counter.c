void tic_rate(int pRate[3], int now)
{
    pRate[2] = pRate[2] + 1;

    if ((now - pRate[0]) >= pRate[1])
    {
        int tps = 0;
        if (pRate[2] > 0)
        {
            tps = pRate[2] / (now - pRate[0]);
        }

        pRate[2] = 0;
        pRate[0] = now;
    }
    return;
}

void something_we_do()
{
    int anchor[5] = {0};
    int x[5] = {0};
    for (x[0] = 0; x[0] < 65535; x[0] = x[0] + 1)
    {
        anchor[0] = x[0];
    }
    return;
}
