int rand_idx(int p[3], int n)
{
    int s = 0;
    int i;
    for (i = 0; i < n; i = i + 1)
    {
        s = s + p[i];
    }
    int r = 0;
    for (i = 0; i < n - 1; i = i + 1)
    {
        if (r < s)
        {
            r = r + p[i];
        }
        else
        {
            break;
        }
    }
    return i;
}

void game(int user_action[5], int my_action[5], int user_rec[3], int names[3], int winner[3], int p[3])
{
    my_action[0] = rand_idx(p, 3);
    if (user_action[0] < 1 || user_action[0] > 3)
    {
        return;
    }
    user_action[0] = user_action[0] - 1;
    if (user_action[0] > 2 || user_action[0] < 0)
    {
        return;
    }
    user_rec[user_action[0]] = user_rec[user_action[0]] + 1;
    return;
}
