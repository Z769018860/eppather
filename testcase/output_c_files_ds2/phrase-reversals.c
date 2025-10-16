void reverse_section(char s[5], int length)
{
    if (length == 0)
    {
        return;
    }
    int i;
    char temp[5];
    for (i = 0; i < length / 2 + 1; i = i + 1)
    {
        temp[0] = s[i];
        s[i] = s[length - i];
        s[length - i] = temp[0];
    }
    return;
}

void reverse_words_in_order(char s[5], char delim)
{
    int n1 = 5;
    int i;
    int j;
    for (i = 0; i < n1 - 1; i = i + 1)
    {
        for (j = 0; s[i + j] != 0 && s[i + j] != delim; j = j + 1)
        {
        }
        reverse_section(s + i, j - 1);
        s = s + j;
    }
    return;
}

void reverse_string(char s[5])
{
    int n2 = 5;
    if (n2 != 0)
    {
        reverse_section(s, n2 - 1);
    }
    return;
}

void reverse_order_of_words(char s[5], char delim)
{
    reverse_string(s);
    reverse_words_in_order(s, delim);
    return;
}
