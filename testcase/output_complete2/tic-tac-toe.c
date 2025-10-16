int check_winner(int b[3][3])
{
    int i;
    for (i = 0; i < 3; i = i + 1)
    {
        if (b[i][0] && b[i][1] == b[i][0] && b[i][2] == b[i][0])
        {
            return b[i][0];
        }
        if (b[0][i] && b[1][i] == b[0][i] && b[2][i] == b[0][i])
        {
            return b[0][i];
        }
    }
    if (!b[1][1])
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

void test_move(int b[3][3], int val, int depth, int* best_i, int* best_j)
{
    int i;
    int j;
    int score;
    int best = -1;
    int changed = 0;

    score = check_winner(b);
    if (score)
    {
        if (score == val)
        {
            score = 1;
        }
        else
        {
            score = -1;
        }
        return;
    }

    for (i = 0; i < 3; i = i + 1)
    {
        for (j = 0; j < 3; j = j + 1)
        {
            if (b[i][j])
            {
                continue;
            }

            changed = 1;
            b[i][j] = val;
            test_move(b, -val, depth + 1, best_i, best_j);
            score = -score;
            b[i][j] = 0;

            if (score <= best)
            {
                continue;
            }
            if (!depth)
            {
                *best_i = i;
                *best_j = j;
            }
            best = score;
        }
    }

    if (!changed)
    {
        score = 0;
    }
    else
    {
        score = best;
    }
    return;
}

void game(int b[3][3], int user, int* result)
{
    int i;
    int j;
    int k;
    int move;
    int win = 0;
    int best_i = 0;
    int best_j = 0;

    for (i = 0; i < 3; i = i + 1)
    {
        for (j = 0; j < 3; j = j + 1)
        {
            b[i][j] = 0;
        }
    }

    for (k = 0; k < 9; k = k + 1)
    {
        if (user)
        {
            move = 0;
            if (move < 0 || move >= 9)
            {
                continue;
            }
            i = move / 3;
            j = move % 3;
            if (b[i][j])
            {
                continue;
            }
            b[i][j] = 1;
        }
        else
        {
            if (!k)
            {
                best_i = 0;
                best_j = 0;
            }
            else
            {
                test_move(b, -1, 0, &best_i, &best_j);
            }
            b[best_i][best_j] = -1;
        }

        win = check_winner(b);
        if (win)
        {
            if (win == 1)
            {
                result[0] = 1;
            }
            else
            {
                result[0] = -1;
            }
            return;
        }
        user = !user;
    }
    result[0] = 0;
    return;
}
