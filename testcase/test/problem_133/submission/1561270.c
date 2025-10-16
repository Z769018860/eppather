#include <stdio.h>
#define N 5010
#define int long long
int g[N][N],n,m;
int lowbit(int x){
    return x&(-x);
}
void add(int x,int y,int val)
{
   for(int i = x ; i <= n ; i += lowbit(i) )
        for(int j = y ; j <= m ; j+= lowbit(j))
            g[i][j] += val;

}
int query(int x,int y){
    int res = 0;
    for(int i = x ; i ; i -= lowbit(i))
        for(int j = y ;j ;j -= lowbit(j))
            res += g[i][j];
    return res;
}
signed main()
{
    int opt,x,y,c,d;
    scanf("%lld%lld",&n,&m);
    while(~scanf("%lld",&opt)){
        if(opt == 1){
        scanf("%lld%lld%lld",&x,&y,&d);
        add(x,y,d);
        }
        else {
            scanf("%lld%lld%lld%lld",&x,&y,&c,&d);
            printf("%lld\n",query(c,d) - query(x-1,d)-query(c,y-1) + query(x-1,y-1));
        }
    }
}

