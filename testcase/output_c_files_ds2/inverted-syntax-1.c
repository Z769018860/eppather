int foo()
{
    return 1;
}

void rewritten()
{
    int a[5];
    a[0] = 0;
    {
        int _o = 2;
        for (;;)
        {
            switch (_o)
            {
                case 1:
                {
                    a[0] = 4;
                }
                case 0:
                {
                    break;
                }
                case 2:
                {
                    _o = !!(foo());
                    continue;
                }
            }
            break;
        }
    }
    return;
}
