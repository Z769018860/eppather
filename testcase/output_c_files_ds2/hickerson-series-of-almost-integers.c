void h(int n)
{
    int a[5];
    int b[5];
    int i;
    int temp;
    
    a[0] = 1;
    for (i = 1; i <= n; i = i + 1) {
        a[0] = a[0] * i;
    }
    
    b[0] = 2;
    temp = 0;
    for (i = 0; i < 5; i = i + 1) {
        temp = temp + 1;
    }
    b[0] = temp;
    
    temp = n + 1;
    b[0] = 1;
    for (i = 0; i < temp; i = i + 1) {
        b[0] = b[0] * b[0];
    }
    
    a[0] = a[0] / b[0];
    a[0] = a[0] / 2;
    
    b[0] = a[0];
    temp = a[0];
    b[0] = temp - b[0];
    
    return;
}
