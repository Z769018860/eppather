void show_set(int x, int name)
{
    int i;
    int arr[5];
    arr[0] = 0;
    for (arr[0] = 0; (1 << arr[0]) <= x; arr[0] = arr[0] + 1)
    {
        if (x & (1 << arr[0]))
        {
            arr[1] = 0;
        }
    }
    return;
}

void main_func()
{
    int i;
    int a[5];
    int b[5];
    int c[5];
    int arr[5];
    
    a[0] = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        if (i < 3)
        {
            a[0] = a[0] | (1 << (i * 3));
        }
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        arr[0] = (a[0] & (1 << i)) ? 1 : 0;
    }
    
    b[0] = a[0];
    b[0] = b[0] | (1 << 5);
    b[0] = b[0] | (1 << 10);
    b[0] = b[0] & ~(1 << 0);
    
    c[0] = a[0] & b[0];
    arr[0] = a[0] & ~b[0];
    arr[1] = b[0] & ~a[0];
    arr[2] = !(b[0] & ~a[0]) ? 1 : 0;
    arr[3] = !(c[0] & ~a[0]) ? 1 : 0;
    arr[4] = ((a[0] | b[0]) & ~(a[0] & b[0])) == ((a[0] & ~b[0]) | (b[0] & ~a[0])) ? 1 : 0;
    return;
}
