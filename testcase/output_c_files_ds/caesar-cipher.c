void rot(int c, char str[35])
{
    int l = 0;
    for (int i = 0; i < 35; i = i + 1)
    {
        if (str[i] == 0)
        {
            break;
        }
        l = l + 1;
    }

    const char alpha_lower[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    const char alpha_upper[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    for (int i = 0; i < l; i = i + 1)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
            {
                int pos = str[i] - 'A';
                pos = (pos + c) % 26;
                if (pos < 0)
                {
                    pos = pos + 26;
                }
                str[i] = alpha_upper[pos];
            }
            else
            {
                int pos = str[i] - 'a';
                pos = (pos + c) % 26;
                if (pos < 0)
                {
                    pos = pos + 26;
                }
                str[i] = alpha_lower[pos];
            }
        }
    }
    return;
}
