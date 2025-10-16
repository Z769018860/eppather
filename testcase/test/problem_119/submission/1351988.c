#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n,m;
struct way{
int u,v,w;
}a[6201];
typedef long long int lld;
lld ans=1e18;
int s,t;
int len;
int find[2501];
int h[2501];
struct x{
int v,w,last;
}b[12402];
lld d[2501][2501];
void add(int u,int v,int w)
{
        b[++len].v=v;
        b[len].w=w;
        b[len].last=h[u];
        h[u]=len;
}
int dfs(int u,int x,lld d[])
{
        find[u]=1;
     for(int i=h[u];i;i=b[i].last){
        int v=b[i].v,w=b[i].w;
        if(v!=x){
                lld t=d[u];
                if(t+w<d[v]||d[v]==-1)
                {
                        d[v]=t+w;
                       if(!find[v])
                       {
                               if(dfs(v,u,d))
                                return;
                       }
                       else
                        return 1;

                }
        }
     }
     find[u]=0;
     return 0;
}
int main()
{
        memset(d,-1,sizeof(d));
        scanf("%d%d%d%d",&n,&m,&s,&t);
         d[s][s]=0;
        for(int i=1;i<=m;i++)
                {scanf("%d%d%d",&a[i].u,&a[i].v,&a[i].w);
                        int u=a[i].u,v=a[i].v,w=a[i].w;
                        add(u,v,w);add(v,u,w);
                }

        dfs(s,-1,d[s]);
        ans=d[s][t];
        printf("%lld",ans);

}