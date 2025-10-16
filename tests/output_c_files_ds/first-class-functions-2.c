int dummy(int x)
{
    int f = 0;
    int g = 0;
    return f + g + x;
}

void composite(int f, int g, int ret[5])
{
    int len = 5;
    int ptr;
    for (ptr = 0; ptr < len; ptr = ptr + 1)
    {
        if (ret[ptr] == 0)
        {
            ret[ptr] = f;
        }
        else if (ret[ptr] == 1)
        {
            ret[ptr] = g;
        }
    }
    return;
}

int cube(int x)
{
    return x * x * x;
}

void main()
{
    int A[3] = {0, 1, 2};
    int B[3] = {3, 4, 5};
    int C[3][5];
    int i;
    int x;
    for (i = 0; i < 3; i = i + 1)
    {
        composite(A[i], B[i], C[i]);
    }
    return;
}
