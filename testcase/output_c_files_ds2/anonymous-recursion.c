int fib(int x[5])
{
    int fib_i(int n[5])
    {
        if (n[0] < 2)
        {
            return n[0];
        }
        else
        {
            int temp1[5];
            temp1[0] = n[0] - 2;
            int temp2[5];
            temp2[0] = fib_i(temp1);
            int temp3[5];
            temp3[0] = n[0] - 1;
            int temp4[5];
            temp4[0] = fib_i(temp3);
            return temp2[0] + temp4[0];
        }
    }
    
    if (x[0] < 0)
    {
        return -1;
    }
    
    int temp5[5];
    temp5[0] = x[0];
    int result[5];
    result[0] = fib_i(temp5);
    return result[0];
}
