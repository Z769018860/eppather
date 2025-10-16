# include <stdio.h>
# define  N 2050
# define lowbit(x) (x&-x)
typedef  long long elem;
elem BA[N][N],BB[N][N],BC[N][N],BD[N][N];
void ADD(int n,int m,int x,int y,int key)
{
    int i,j;
    for(i=x;i<=n;i+=lowbit(i))
    {
        for(j=y;j<=m;j+=lowbit(j))
        {
            BA[i][j]+=key;
            BB[i][j]+=key*x;
            BC[i][j]+=key*y;
            BD[i][j]+=key*x*y;
        }
    }
}
elem SUM(int x,int y)
{
    int i,j;
    elem sum=0;
    for(i=x;i;i-=lowbit(i))
    {
        for(j=y;j;j-=lowbit(j))
        {
            sum+=(x+1)*(y+1)*BA[i][j] - (y+1)*BB[i][j] - (x+1)*BC[i][j] + BD[i][j];
        }
    }
    return sum;
}
void update(int n,int m,int a,int b,int x,int y,int key)
{
    ADD(n,m,a,b,key);
    ADD(n,m,x+1,b,-key);
    ADD(n,m,a,y+1,-key);
    ADD(n,m,x+1,y+1,key);
}
int main()
{
    int n,m,i,j;
    int choose,X,Y,A,B,K;
    elem sum=0;
    scanf("%d%d",&n,&m);
    while(~scanf("%d%d%d%d%d",&choose,&A,&B,&X,&Y))
    {
        if(choose==1)
        {
            scanf("%d",&K);
            update(n,m,A,B,X,Y,K);
        }else{
            sum=SUM(X,Y)-SUM(A-1,Y)-SUM(X,B-1)+SUM(A-1,B-1);
            printf("%lld\n",sum);
        }
    }
    return 0;
}
