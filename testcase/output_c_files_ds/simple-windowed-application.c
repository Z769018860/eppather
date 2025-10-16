int clickedme(int d, int counter)
{
    int nt[64];
    int i;
    int temp;
    
    counter = counter + 1;
    
    for (i = 0; i < 64; i = i + 1)
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
    
    temp = counter;
    i = 15;
    while (temp > 0)
    {
        nt[i] = '0' + (temp % 10);
        temp = temp / 10;
        i = i + 1;
    }
    
    nt[i] = ' ';
    nt[i + 1] = 't';
    nt[i + 2] = 'i';
    nt[i + 3] = 'm';
    nt[i + 4] = 'e';
    nt[i + 5] = 's';
    nt[i + 6] = '\0';
    
    return counter;
}
