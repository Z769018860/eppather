void step_up(void)
{
    int i;
    i = 0;
    for (; i < 1; )
    {
        if (step() != 0)
        {
            i = i + 1;
        }
        else
        {
            i = i - 1;
        }
    }
    return;
}
