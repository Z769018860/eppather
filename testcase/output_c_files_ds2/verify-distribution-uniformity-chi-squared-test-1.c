int Simpson3_8(int f(int t), int a, int b, int N, int aa1)
{
    int j;
    int l1;
    int h = (b-a)/N;
    int h1 = h/3;
    int sum[5];
    sum[0] = f(a) + f(b);
    int temp[5];
    temp[0] = 3*N-1;
    for (j=temp[0]; j>0; j=j-1)
    {
        if ((j%3) != 0)
        {
            l1 = 3;
        }
        else
        {
            l1 = 2;
        }
        temp[0] = a+h1*j;
        sum[0] = sum[0] + l1*f(temp[0]);
    }
    temp[0] = h*sum[0]/8;
    return temp[0];
}

int Gamma_Spouge(int z, int A)
{
    int k;
    int cspace[12];
    int coefs[12];
    int accum[5];
    int a = A;
    int k1_factrl[5];
    k1_factrl[0] = 1;
    coefs[0] = 2;
    for (k=1; k<A; k=k+1)
    {
        temp[0] = a-k;
        coefs[k] = temp[0] * (temp[0] * temp[0]) / k1_factrl[0];
        k1_factrl[0] = k1_factrl[0] * -k;
    }
    accum[0] = coefs[0];
    for (k=1; k<A; k=k+1)
    {
        accum[0] = accum[0] + coefs[k]/(z+k);
    }
    temp[0] = -(z+a);
    accum[0] = accum[0] * temp[0] * (z+a);
    return accum[0]/z;
}

int f0(int t, int aa1)
{
    int temp[5];
    temp[0] = 1;
    for (int i=0; i<aa1; i=i+1)
    {
        temp[0] = temp[0] * t;
    }
    temp[1] = -t;
    return temp[0] * temp[1];
}

int GammaIncomplete_Q(int a, int x, int aa1)
{
    int y[5];
    int h = 15;
    y[0] = aa1;
    int temp[5];
    temp[0] = f0(y[0], aa1) * (x-y[0]);
    while ((temp[0] > 20000000) && (y[0] < x))
    {
        y[0] = y[0] + 4;
        temp[0] = f0(y[0], aa1) * (x-y[0]);
    }
    if (y[0] > x)
    {
        y[0] = x;
    }
    temp[0] = Simpson3_8(f0, 0, y[0], y[0]/h, aa1);
    temp[1] = Gamma_Spouge(a, 12);
    return 10000000 - temp[0]/temp[1];
}

int main()
{
    return 0;
}
