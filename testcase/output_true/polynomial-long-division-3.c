int p_div(int p_power, int p_coef[5], int d_power, int d_coef[5], int r_power, int r_coef[5], int q_power, int q_coef[5])
{
    int i;
    int j;
    int power;
    int ratio;
    int temp[5];
    
    power = p_power - d_power;
    if (power < 0)
    {
        return 0;
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        q_coef[i] = 0;
    }
    q_power = power;
    
    for (i = 0; i < 5; i = i + 1)
    {
        r_coef[i] = p_coef[i];
    }
    r_power = p_power;
    
    for (i = p_power; i >= d_power; i = i - 1)
    {
        ratio = r_coef[i] / d_coef[d_power];
        q_coef[i - d_power] = ratio;
        r_coef[i] = 0;
        
        for (j = 0; j < d_power; j = j + 1)
        {
            r_coef[i - d_power + j] = r_coef[i - d_power + j] - d_coef[j] * ratio;
        }
    }
    
    while (r_coef[r_power] == 0)
    {
        r_power = r_power - 1;
    }
    
    return 0;
}
