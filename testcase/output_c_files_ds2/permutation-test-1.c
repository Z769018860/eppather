int pick(int at, int remain, int accu, int treat, int data[19])
{
    if (remain == 0)
    {
        if (accu > treat)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int result1 = pick(at - 1, remain - 1, accu + data[at - 1], treat, data);
    int result2 = 0;
    if (at > remain)
    {
        result2 = pick(at - 1, remain, accu, treat, data);
    }
    return result1 + result2;
}

void calculate(int data[19])
{
    int treat[5];
    treat[0] = 0;
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        if (i < 9)
        {
            treat[0] = treat[0] + data[i];
        }
    }

    int total[5];
    total[0] = 1;
    for (i = 19; i > 10; i = i - 1)
    {
        total[0] = total[0] * i;
    }
    for (i = 9; i > 0; i = i - 1)
    {
        total[0] = total[0] / i;
    }

    int gt[5];
    gt[0] = pick(19, 9, 0, treat[0], data);
    int le[5];
    le[0] = total[0] - gt[0];
    return;
}
