int rand5_7()
{
    int rand_max;
    int r;
    int temp;
    int result;
    
    for (;;)
    {
        rand_max = 2147483647 - (2147483647 % 5);
        for (;;)
        {
            r = rand();
            if (r < rand_max)
            {
                break;
            }
        }
        temp = r / (rand_max / 5) + 1;
        
        r = temp * 5;
        
        rand_max = 2147483647 - (2147483647 % 5);
        for (;;)
        {
            temp = rand();
            if (temp < rand_max)
            {
                break;
            }
        }
        temp = temp / (rand_max / 5) + 1;
        
        r = r + temp;
        
        if (r < 27)
        {
            break;
        }
    }
    
    result = r / 3 - 1;
    return result;
}
