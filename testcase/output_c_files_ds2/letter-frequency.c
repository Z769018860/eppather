int frequency[26];
int ch[5];
int txt_file[5];
int n;
int n1;
int n2;

{
    for (n = 0; n < 26; n = n + 1)
    {
        frequency[n] = 0;
    }
    for (n1 = 0; n1 < 5; n1 = n1 + 1)
    {
        ch[0] = 0;
        if (ch[0] == -1)
        {
            break;
        }
        if (97 <= ch[0] && ch[0] <= 122)
        {
            n2 = ch[0] - 97;
            frequency[n2] = frequency[n2] + 1;
        }
        else
        {
            if (65 <= ch[0] && ch[0] <= 90)
            {
                n2 = ch[0] - 65;
                frequency[n2] = frequency[n2] + 1;
            }
        }
    }
    return;
}
