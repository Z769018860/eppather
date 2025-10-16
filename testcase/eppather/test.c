void process(int a, int b, int *c) {
    int sum = 0;

    sum = 3 * 5 + 4 * 5 + 5 * 5;

    if (a > 0)
        a = a + 1;
    else
        a = a - 1;

    int i;
    for (i = 0; i < 10; i = i + 1)
        a = a + i;

    while (a > 1) {
        if (b > 0)
            a = a - 1;
        else
            a = a + 2;
        ;
    }

    *c = b = a;

    while (a < 0)
        a = a + 1;
    return;
}
