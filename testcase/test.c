int main() {
    int sum=0;
    int a;
    int b;
    int c;
    int M=5;
    sum = 3 * M + 4 * M + 5 * M;
    if (a>0)
        a=a+1;
    else
        a=a-1;
    int i;
    for (i=0;i<10;i=i+1)
        a=a+i;
    while (a>1)
    {
        if (b>0)
            a=a-1;
        else
            a=a+2;
    }
    c=b=a;
    while (a<0)
        a=a+1;
    return 0;
}
