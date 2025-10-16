int take_it_or_not(int number[5], int guess[5], int yp, int xp, int LINE_BEGIN, int LAST_LINE)
{
    int cows;
    int bulls;
    int i;
    int j;
    int found;
    
    cows = 0;
    bulls = 0;
    for (i = 0; i < 4; i = i + 1) 
    {
        if (number[i] == guess[i]) 
        {
            bulls = bulls + 1;
        } 
        else 
        {
            found = 0;
            for (j = 0; j < 4; j = j + 1) 
            {
                if (guess[i] == number[j]) 
                {
                    found = 1;
                }
            }
            if (found != 0) 
            {
                cows = cows + 1;
            }
        }
    }
    if (bulls == 4) 
    {
        yp = yp + 1;
        return 1;
    }
    yp = yp + 1;
    if (yp > LAST_LINE) 
    {
        yp = LINE_BEGIN;
        xp = xp + 10;
    }
    return 0;
}

int ask_play_again(int yp, int LINE_BEGIN)
{
    int a;
    
    for (yp = yp; yp >= LINE_BEGIN; yp = yp - 1) 
    {
    }
    yp = LINE_BEGIN;
    for (a = 0; a < 5; a = a + 1) 
    {
        if (a == 1) 
        {
            return 1;
        }
        if (a == 2) 
        {
            return 0;
        }
    }
    return 0;
}

void main_func()
{
    int bingo;
    int again;
    int tries;
    int number[5];
    int guess[5];
    int yp;
    int xp;
    int LINE_BEGIN;
    int LAST_LINE;
    int MAX_NUM_TRIES;
    
    tries = 0;
    number[4] = 0;
    guess[4] = 0;
    do 
    {
        choose_the_number();
        do 
        {
            ask_for_a_number();
            bingo = take_it_or_not(number, guess, yp, xp, LINE_BEGIN, LAST_LINE);
            tries = tries + 1;
        } 
        while ((bingo == 0) && (tries < MAX_NUM_TRIES));
        again = ask_play_again(yp, LINE_BEGIN);
        tries = 0;
    } 
    while (again != 0);
    return;
}
