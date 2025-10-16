# include <stdio.h>
# define  N 10000
# define lowbit(x) (x&-x)
typedef  long long elem;
elem BIT[N][N];
void ADD(elem BIT[][N],int n,int m,int x,int y,int key)
{
    int j;
    for(j=y;x<=n;x+=lowbit(x))
    {
        for(y=j;y<=m;y+=lowbit(y))
        {
            BIT[x][y]+=key;
        }
    }
}
void update(elem BIT[][N],int n,int m,int x,int y,int a,int b,int key)
{
    ADD(BIT,n,m,x,y,key);
    ADD(BIT,n,m,x,b+1,-key);
    ADD(BIT,n,m,a+1,y,-key);
    ADD(BIT,n,m,a+1,b+1,key);
}
elem SUM(elem BIT[][N],int x,int y)
{
    int j;
    elem sum=0;
    for(j=y;x;x-=lowbit(x))
    {
        for(y=j;y;y-=lowbit(y))
        {
            sum+=BIT[x][y];
        }
    }
    return sum;
}

int main()
{
    int n,m,i,j;
    int choose,X,Y,A,B,K;
    elem sum=0;
    scanf("%d%d",&n,&m);
    while(~scanf("%d",&choose))
    {
        if(choose==1)
        {
            scanf("%d%d%d",&X,&Y,&K);
            ADD(BIT,n,m,X,Y,K);
        }else{
            scanf("%d%d%d%d",&A,&B,&X,&Y);
            sum=SUM(BIT,X,Y)-SUM(BIT,A-1,Y)-SUM(BIT,X,B-1)+SUM(BIT,A-1,B-1);
            printf("%lld\n",sum);
        }
    }
    return 0;
}
