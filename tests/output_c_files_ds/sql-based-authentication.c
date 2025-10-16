int create_user_authenticate(int action, char username[32], char password[32], int salt[16], int hash1[16], int hash2[16], int user_escaped[64], int query_buf[256], int row_buf[256], int len_buf[4])
{
    int i;
    int username_valid;
    int password_valid;
    int res;
    int authok;
    
    username_valid = 1;
    for(i = 0; i < 32; i = i + 1)
    {
        if(username[i] == 0)
        {
            break;
        }
    }
    if(i == 32 && username[31] != 0)
    {
        username_valid = 0;
    }
    
    password_valid = 1;
    for(i = 0; i < 32; i = i + 1)
    {
        if(password[i] == 0)
        {
            break;
        }
    }
    if(i == 32 && password[31] != 0)
    {
        password_valid = 0;
    }
    
    if(username_valid == 0 || password_valid == 0)
    {
        return 0;
    }
    
    if(action == 0)
    {
        for(i = 0; i < 16; i = i + 1)
        {
            salt[i] = i * 17 % 256;
        }
        
        for(i = 0; i < 16; i = i + 1)
        {
            hash1[i] = (salt[i] + password[i % 8]) % 256;
        }
        
        for(i = 0; i < 32; i = i + 1)
        {
            user_escaped[i] = username[i];
            if(username[i] == 0)
            {
                break;
            }
        }
        
        res = 1;
        return res;
    }
    else if(action == 1)
    {
        for(i = 0; i < 16; i = i + 1)
        {
            hash2[i] = (row_buf[16 + i] + password[i % 8]) % 256;
        }
        
        authok = 1;
        for(i = 0; i < 16; i = i + 1)
        {
            if(hash2[i] != row_buf[32 + i])
            {
                authok = 0;
                break;
            }
        }
        return authok;
    }
    
    return 0;
}
