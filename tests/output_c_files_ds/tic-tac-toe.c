int check_winner(int b[3][3])
{
    int i;
    for (i = 0; i < 3; i = i + 1)
    {
        if (b[i][0] != 0 && b[i][1] == b[i][0] && b[i][2] == b[i][0])
        {
            return b[i][0];
        }
        if (b[0][i] != 0 && b[1][i] == b[0][i] && b[2][i] == b[0][i])
        {
            return b[0][i];
        }
    }
    if (b[1][1] == 0)
    {
        return 0;
    }
    if (b[1][1] == b[0][0] && b[2][2] == b[0][0])
    {
        return b[0][0];
    }
    if (b[1][1] == b[2][0] && b[0][2] == b[1][1])
    {
        return b[1][1];
    }
    return 0;
}

int test_move(int b[3][3], int val, int depth, int* best_i, int* best_j)
{
    int i;
    int j;
    int score;
    int best = -1;
    int changed = 0;
    score = check_winner(b);
    if (score != 0)
    {
        if (score == val)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    for (i = 0; i < 3; i = i + 1)
    {
        for (j = 0; j < 3; j = j + 1)
        {
            if (b[i][j] != 0)
            {
                continue;
            }
            changed = 1;
            b[i][j] = val;
            score = -test_move(b, -val, depth + 1, best_i, best_j);
            b[i][j] = 0;
            if (score <= best)
            {
                continue;
            }
            if (depth == 0)
            {
                *best_i = i;
                *best_j = j;
            }
            best = score;
        }
    }
    if (changed != 0)
    {
        return best;
    }
    else
    {
        return 0;
    }
}

void game(int b[3][3], int user, int* win, int* move, int* best_i, int* best_j)
{
    int i;
    int j;
    int k;
    for (i = 0; i < 3; i = i + 1)
    {
        for (j = 0; j < 3; j = j + 1)
        {
            b[i][j] = 0;
        }
    }
    for (k = 0; k < 9; k = k + 1)
    {
        if (user != 0)
        {
            if (*move >= 0 && *move < 9)
            {
                i = *move / 3;
                j = *move % 3;
                if (b[i][j] == 0)
                {
                    b[i][j] = 1;
                }
            }
        }
        else
        {
            if (k == 0)
            {
                *best_i = 1;
                *best_j = 1;
            }
            else
            {
                test_move(b, -1, 0, best_i, best_j);
            }
            b[*best_i][*best_j] = -1;
        }
        *win = check_winner(b);
        if (*win != 0)
        {
            return;
        }
        user = !user;
    }
    return;
}
