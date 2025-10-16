int eval(int* fn, int* u_k, int* x1_fn, int* x1_u_k, int* x2_fn, int* x2_u_k, int* x3_fn, int* x3_u_k, int* x4_fn, int* x4_u_k, int* x5_fn, int* x5_u_k)
{
    if (fn[0] == 0)
    {
        return u_k[0];
    }
    else
    {
        return eval(fn, u_k, x1_fn, x1_u_k, x2_fn, x2_u_k, x3_fn, x3_u_k, x4_fn, x4_u_k, x5_fn, x5_u_k);
    }
}

int A(int* u_k, int* x1_fn, int* x1_u_k, int* x2_fn, int* x2_u_k, int* x3_fn, int* x3_u_k, int* x4_fn, int* x4_u_k, int* x5_fn, int* x5_u_k);

int B(int* u_k, int* x1_fn, int* x1_u_k, int* x2_fn, int* x2_u_k, int* x3_fn, int* x3_u_k, int* x4_fn, int* x4_u_k, int* x5_fn, int* x5_u_k)
{
    u_k[0] = u_k[0] - 1;
    int b_fn[5] = {1};
    int b_u_k[5] = {0};
    b_u_k[0] = u_k[0];
    return A(b_u_k, x1_fn, x1_u_k, x2_fn, x2_u_k, x3_fn, x3_u_k, x4_fn, x4_u_k, x5_fn, x5_u_k);
}

int A(int* u_k, int* x1_fn, int* x1_u_k, int* x2_fn, int* x2_u_k, int* x3_fn, int* x3_u_k, int* x4_fn, int* x4_u_k, int* x5_fn, int* x5_u_k)
{
    if (u_k[0] <= 0)
    {
        int temp1 = eval(x4_fn, x4_u_k, x1_fn, x1_u_k, x2_fn, x2_u_k, x3_fn, x3_u_k, x4_fn, x4_u_k, x5_fn, x5_u_k);
        int temp2 = eval(x5_fn, x5_u_k, x1_fn, x1_u_k, x2_fn, x2_u_k, x3_fn, x3_u_k, x4_fn, x4_u_k, x5_fn, x5_u_k);
        return temp1 + temp2;
    }
    else
    {
        return B(u_k, x1_fn, x1_u_k, x2_fn, x2_u_k, x3_fn, x3_u_k, x4_fn, x4_u_k, x5_fn, x5_u_k);
    }
}

int main_func(int k)
{
    int a_fn[5] = {1};
    int a_u_k[5] = {0};
    a_u_k[0] = k;
    int f1_fn[5] = {0};
    int f1_u_k[5] = {0};
    f1_u_k[0] = 1;
    int f0_fn[5] = {0};
    int f0_u_k[5] = {0};
    f0_u_k[0] = 0;
    int fn1_fn[5] = {0};
    int fn1_u_k[5] = {0};
    fn1_u_k[0] = -1;
    return A(a_u_k, f1_fn, f1_u_k, fn1_fn, fn1_u_k, fn1_fn, fn1_u_k, f1_fn, f1_u_k, f0_fn, f0_u_k);
}

return;
