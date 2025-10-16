int test(int n, int num_items, int items_set[5])
{
    int s_env_sample[5];
    int s_env_i = 0;
    int s_env_n = n;
    int s_env_size = 1;
    int i;
    int j;
    int rand_val;
    
    for (i = 0; i < 5; i = i + 1)
    {
        s_env_sample[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        s_env_i = s_env_i + 1;
        if (s_env_i <= s_env_n)
        {
            s_env_sample[s_env_i - 1] = items_set[i];
        }
        else
        {
            rand_val = 0;
            if ((rand_val % s_env_i) < s_env_n)
            {
                s_env_sample[rand_val % s_env_n] = items_set[i];
            }
        }
    }
    return s_env_sample[0];
}
