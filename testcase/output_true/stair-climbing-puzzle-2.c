void step_up(void)
{
    int i[5];
    i[0] = 0;
    
    for (; i[0] < 1; )
    {
        if (step())
        {
            i[0] = i[0] + 1;
        }
        else
        {
            i[0] = i[0] - 1;
        }
    }
    
    return;
}
