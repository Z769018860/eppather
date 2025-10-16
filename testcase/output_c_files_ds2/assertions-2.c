int a[5];
a[0] = 42;
if (a[0] != 42)
{
    for (int i = 0; i < 5; i = i + 1)
    {
        a[i] = 0;
    }
}
return;
