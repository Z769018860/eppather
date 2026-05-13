int mapRange(int a1[5], int a2[5], int b1[5], int b2[5], int s[5])
{
    int result[5];
    result[0] = b1[0] + (s[0] - a1[0]) * (b2[0] - b1[0]) / (a2[0] - a1[0]);
    return result[0];
}

void main_func()
{
    int i[5];
    int a1[5] = {0};
    int a2[5] = {10};
    int b1[5] = {-1};
    int b2[5] = {0};
    int s[5] = {0};
    
    for (i[0] = 0; i[0] <= 5; i[0] = i[0] + 1)
    {
        s[0] = i[0];
        mapRange(a1, a2, b1, b2, s);
    }
    
    return;
}
