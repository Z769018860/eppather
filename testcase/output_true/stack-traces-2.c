void stack_trace_begin(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10, int n11, int n12, int n13, int n14, int n15, int n16, int n17, int n18, int n19, int n20)
{
    int x[5];
    x[0] = 0;
    x[1] = 0;
    x[2] = 0;
    x[3] = 0;
    x[4] = 0;
    for (int i = 0; i < 5; i = i + 1)
    {
        x[i] = x[i] + 1;
    }
    return;
}

void stack_trace_end(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10, int n11, int n12, int n13, int n14, int n15, int n16, int n17, int n18, int n19, int n20)
{
    int y[5];
    y[0] = 0;
    y[1] = 0;
    y[2] = 0;
    y[3] = 0;
    y[4] = 0;
    for (int j = 0; j < 5; j = j + 1)
    {
        y[j] = y[j] + 1;
    }
    return;
}

void print_stack_trace()
{
    int z[5];
    z[0] = 0;
    z[1] = 0;
    z[2] = 0;
    z[3] = 0;
    z[4] = 0;
    for (int k = 0; k < 5; k = k + 1)
    {
        z[k] = z[k] + 1;
    }
    return;
}
