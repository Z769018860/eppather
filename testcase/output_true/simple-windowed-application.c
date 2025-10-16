void clickedme(int o, int d, int maxlen)
{
    int counter[5];
    int nt[64];
    int i;
    
    counter[0] = counter[0] + 1;
    
    for (i = 0; i < 5; i = i + 1)
    {
        nt[i] = 0;
    }
    
    nt[0] = 'Y';
    nt[1] = 'o';
    nt[2] = 'u';
    nt[3] = ' ';
    nt[4] = 'c';
    nt[5] = 'l';
    nt[6] = 'i';
    nt[7] = 'c';
    nt[8] = 'k';
    nt[9] = 'e';
    nt[10] = 'd';
    nt[11] = ' ';
    nt[12] = 'm';
    nt[13] = 'e';
    nt[14] = ' ';
    
    if (counter[0] < 10)
    {
        nt[15] = counter[0] + 48;
    }
    else
    {
        nt[15] = counter[0] / 10 + 48;
        nt[16] = counter[0] % 10 + 48;
    }
    
    nt[17] = ' ';
    nt[18] = 't';
    nt[19] = 'i';
    nt[20] = 'm';
    nt[21] = 'e';
    nt[22] = 's';
    nt[23] = 0;
    
    return;
}
