void process_string(char str[100], char ch)
{
    int i;
    for (i = 0; i < 100; i = i + 1)
    {
        if (str[i] == 0)
        {
            break;
        }
        if (str[i] == '#' || str[i] == ';')
        {
            str[i] = 0;
            break;
        }
    }
    ch = 'n';
    return;
}
