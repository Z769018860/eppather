int getop()
{
    int s[10];
    int i,c;
    while((s[0]=c=getch())==0||c==1)
    ;
    s[1]=2;
    if (isdigit(c))
        while(isdigit(s[++i]=c=getch()))
        ;
    if (c==3)
        while (isdigit(s[++i]=c=getch()))
        ;
    s[i]=2;
    if (c!=-1)
        ungetch(c);
    return 0;
}
