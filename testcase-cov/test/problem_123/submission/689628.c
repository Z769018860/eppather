#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    int v1;
    int v2;
    int Wi;
}edge;
edge Arc[500005];
int vecnum,arcnum,link[200005];
long long res=0;
int comp(const void* a,const void* b)
{
    return (*(edge*)a).Wi-(*(edge*)b).Wi;
}
int find(int k)
{
    return (link[k]==k)?k:(link[k]=find(link[k]));
}
int main()
{
    scanf("%d%d",&vecnum,&arcnum);
    for(int k=0;k<arcnum;k++)
    {
        scanf("%d%d%d",&Arc[k].v1,&Arc[k].v2,&Arc[k].Wi);
    }
    qsort(Arc,arcnum,sizeof(edge),comp);
    for(int i=0;i<vecnum;i++)
        link[i]=i;
    int num=0;
    for(int i=0;i<arcnum&&num<vecnum;i++)
    {
        int v1=find(Arc[i].v1);
        int v2=find(Arc[i].v2);
        if(v1!=v2)
        {
            link[v1]=v2;
            res+=Arc[i].Wi;
            num++;
        }
    }
    printf("%lld",res);
    return 0;
}