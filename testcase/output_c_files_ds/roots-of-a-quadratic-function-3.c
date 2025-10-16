void roots_quadratic_eq2(int a, int b, int c, int x[4])
{
    int b_div_a;
    int c_div_a;
    int delta;
    int root;
    int sol;
    int i;
    int temp;
    
    b_div_a = b / a;
    c_div_a = c / a;
    delta = b_div_a * b_div_a - 4 * c_div_a;
    
    if (delta < 0)
    {
        temp = 0 - delta;
        for (i = 0; i * i < temp; i = i + 1)
        {
        }
        x[0] = (0 - b_div_a) / 2;
        x[1] = i / 2;
        x[2] = (0 - b_div_a) / 2;
        x[3] = (0 - i) / 2;
    }
    else
    {
        for (i = 0; i * i <= delta; i = i + 1)
        {
        }
        root = i - 1;
        if (b_div_a > 0)
        {
            sol = (0 - b_div_a - root) / 2;
        }
        else
        {
            sol = (0 - b_div_a + root) / 2;
        }
        x[0] = sol;
        x[1] = 0;
        x[2] = c_div_a / sol;
        x[3] = 0;
    }
    return;
}
