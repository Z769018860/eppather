int func(int NMEMB, int SIZEOF_MEMB)
{
    int ints[5];
    int int2[5];
    char intstack[5];
    int pointers_to_char[5];
    
    int2[0] = (int)intstack[0];
    
    for (int i = 0; i < 5; i = i + 1)
    {
        pointers_to_char[i] = 0;
    }
    pointers_to_char[0] = 0;
    
    return 0;
}
