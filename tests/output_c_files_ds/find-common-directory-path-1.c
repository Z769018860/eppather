int common_len(const char* const names[3], int n, char sep)
{
    int i;
    int pos;
    for (pos = 0; ; pos = pos + 1)
    {
        for (i = 0; i < n; i = i + 1)
        {
            if (names[i][pos] != '\0' && names[i][pos] == names[0][pos])
            {
                continue;
            }
            while (pos > 0)
            {
                pos = pos - 1;
                if (names[0][pos] == sep)
                {
                    break;
                }
            }
            return pos;
        }
    }
    return 0;
}
