int func()
{
    int ints[100];
    int int2[100];
    char intstack[100];
    int i;
    for (i = 0; i < 100; i = i + 1)
    {
        int2[i] = (int)intstack[i];
    }
    {
        char pointers_to_char[100][10];
        pointers_to_char[0][0] = 'e';
        pointers_to_char[0][1] = 'd';
        pointers_to_char[0][2] = 'u';
        pointers_to_char[0][3] = 'c';
        pointers_to_char[0][4] = 'a';
        pointers_to_char[0][5] = 't';
        pointers_to_char[0][6] = 'i';
        pointers_to_char[0][7] = 'v';
        pointers_to_char[0][8] = 'e';
        pointers_to_char[0][9] = '\0';
    }
    return;
}
