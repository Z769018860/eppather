int power_next_filter(int n, int pos, int output, int in_output, int wo_output, int in_pos, int wo_pos, int in_n, int wo_n)
{
    int result[5];
    result[0] = -1;
    for (int i = 0; i < 5; i = i + 1)
    {
        for (int j = 0; j < 5; j = j + 1)
        {
            pos = pos + 1;
            in_output = 1;
            for (int k = 0; k < n; k = k + 1)
            {
                in_output = in_output * pos;
            }
            wo_output = 1;
            wo_pos = wo_pos + 1;
            for (int k = 0; k < 3; k = k + 1)
            {
                wo_output = wo_output * wo_pos;
            }
            while (wo_output < in_output)
            {
                wo_output = 1;
                wo_pos = wo_pos + 1;
                for (int k = 0; k < 3; k = k + 1)
                {
                    wo_output = wo_output * wo_pos;
                }
            }
            if (wo_output != in_output)
            {
                result[0] = in_output;
                break;
            }
        }
        if (result[0] != -1)
        {
            break;
        }
    }
    return result[0];
}

void filter_power_sequences()
{
    int n[5];
    n[0] = 2;
    int pos[5];
    pos[0] = -1;
    int output[5];
    output[0] = -1;
    int in_output[5];
    in_output[0] = -1;
    int wo_output[5];
    wo_output[0] = -1;
    int in_pos[5];
    in_pos[0] = -1;
    int wo_pos[5];
    wo_pos[0] = -1;
    int in_n[5];
    in_n[0] = 2;
    int wo_n[5];
    wo_n[0] = 3;
    for (int i = 0; i < 5; i = i + 1)
    {
        output[0] = power_next_filter(n[0], pos[0], output[0], in_output[0], wo_output[0], in_pos[0], wo_pos[0], in_n[0], wo_n[0]);
    }
    return;
}
