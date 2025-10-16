void number_reversal_game(int list[9], int input)
{
    int tries[5];
    tries[0] = 0;
    int i;
    int j;
    int temp;

    for (i = 0; i < 5; i = i + 1)
    {
        if (list[0] != 1 || list[1] != 2 || list[2] != 3 || list[3] != 4 || list[4] != 5 || list[5] != 6 || list[6] != 7 || list[7] != 8 || list[8] != 9)
        {
            tries[0] = tries[0] + 1;
            if (input > 1 && input < 10)
            {
                for (j = 0; j < input / 2; j = j + 1)
                {
                    temp = list[j];
                    list[j] = list[input - j - 1];
                    list[input - j - 1] = temp;
                }
            }
        }
    }
    return;
}
