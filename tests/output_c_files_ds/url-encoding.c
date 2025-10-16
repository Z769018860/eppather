void encode(const char *s, char *enc, char *tb)
{
    int i;
    int j;
    int k;
    int temp;
    for (i = 0; s[i] != 0; i = i + 1)
    {
        if (tb[s[i]])
        {
            enc[0] = tb[s[i]];
            enc = enc + 1;
        }
        else
        {
            enc[0] = '%';
            temp = s[i];
            j = temp / 16;
            k = temp % 16;
            enc[1] = j < 10 ? j + '0' : j - 10 + 'A';
            enc[2] = k < 10 ? k + '0' : k - 10 + 'A';
            enc = enc + 3;
        }
    }
    enc[0] = 0;
    return;
}
