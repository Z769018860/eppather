char s[1<<21];int i,j,l=1;main()
{
    gets(s);
    for(;s[i];j++)
    {
        int f=0;
        s[j]>s[j-l]&&(f=l=j-i+1);
        if(!f&&s[j]<s[j-l]){
            while(i<=j-l)printf("%d ",i+=l);j=i;l=1;
            }
        }
}