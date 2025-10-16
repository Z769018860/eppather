int create_user_authenticate_user(int username_limit, int password_limit, int salt_byte, int md5_digest_length, int username_length, int password_length, int username_index, int password_index)
{
    int binarysalt[5];
    int salt[5];
    int md5hash[5];
    int saltpass[5];
    int pass_md5[5];
    int user[5];
    int authok[5];
    int i;
    int res[5];
    
    for(i = 0; i < 5; i = i + 1)
    {
        binarysalt[i] = 0;
        salt[i] = 0;
        md5hash[i] = 0;
        saltpass[i] = 0;
        pass_md5[i] = 0;
        user[i] = 0;
        authok[i] = 0;
        res[i] = 0;
    }
    
    for(i = 0; i < 5; i = i + 1)
    {
        if (i < username_limit && username_index < username_length)
        {
            username_index = username_index + 1;
        }
        else
        {
            if (username_index < username_length)
            {
                return 0;
            }
        }
    }
    
    for(i = 0; i < 5; i = i + 1)
    {
        if (i < password_limit && password_index < password_length)
        {
            password_index = password_index + 1;
        }
        else
        {
            if (password_index < password_length)
            {
                return 0;
            }
        }
    }
    
    for(i = 0; i < 5; i = i + 1)
    {
        binarysalt[i] = i % 256;
    }
    
    for(i = 0; i < 5; i = i + 1)
    {
        saltpass[i] = binarysalt[i];
    }
    
    for(i = 0; i < 5; i = i + 1)
    {
        if (i < salt_byte)
        {
            saltpass[i] = binarysalt[i];
        }
    }
    
    for(i = 0; i < 5; i = i + 1)
    {
        if (i < md5_digest_length)
        {
            md5hash[i] = saltpass[i] + password_index;
        }
    }
    
    for(i = 0; i < 5; i = i + 1)
    {
        if (i < username_length)
        {
            user[i] = username_index + i;
        }
    }
    
    res[0] = 0;
    authok[0] = 1;
    
    for(i = 0; i < 5; i = i + 1)
    {
        if (i < md5_digest_length)
        {
            if (md5hash[i] != saltpass[i])
            {
                authok[0] = 0;
            }
        }
    }
    
    return authok[0];
}
