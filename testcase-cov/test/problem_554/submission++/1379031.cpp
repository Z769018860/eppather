#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;
typedef pair<int,int> P;
int n,q,in1,in2,p[300010],sta[300010],L[300010],R[300010],deg[300010],ll[300010],lll[300010],rs1[300010];
long long num[2][300010],rs2[300010];
vector<int>ed[300010];
vector<P>qr1[300010],qr2[300010];
bool vis[300010];
void wkot()
{
    int cn(0);
    for(int i=1,j=1;i<=n;i++)
    {
        vis[i]=true;
        for(vector<int>::iterator ite=ed[i].begin();ite!=ed[i].end();ite++)if(*ite>=j&&*ite<=i)deg[i]^=1,cn-=vis[*ite]?0:deg[*ite],vis[*ite]=L[*ite]<j||R[*ite]>i,deg[*ite]^=1,cn+=vis[*ite]?0:deg[*ite];
        while(cn){j++;for(vector<int>::iterator ite=ed[j-1].begin();ite!=ed[j-1].end();ite++)if(*ite>=j&&*ite<=i)deg[j-1]^=1,cn-=vis[*ite]?0:deg[*ite],vis[*ite]=L[*ite]<j||R[*ite]>i,deg[*ite]^=1,cn+=vis[*ite]?0:deg[*ite];}
        lll[i]=j;
    }
    ll[1]=ll[2]=1;for(int i=3;i<=n;i++)ll[i]=(p[i]>p[i-1])^(p[i-1]>p[i-2])?i-1:ll[i-1];
}
void init()
{
    int tp=0;sta[0]=0;memset(L,0x3f,sizeof(L));
    for(int i=1;i<=n;i++)
    {
        while(tp&&p[sta[tp]]<p[i])tp--;L[i]=min(L[i],sta[tp]);
        if(tp)ed[sta[tp]].push_back(i),ed[i].push_back(sta[tp]);sta[++tp]=i;
    }
    for(int i=1;i<=tp;i++)vis[i]=true;tp=0;sta[0]=n+1;
    for(int i=n;i;i--)
    {
        while(tp&&p[sta[tp]]<p[i])tp--;R[i]=max(R[i],sta[tp]);
        if(tp)ed[sta[tp]].push_back(i),ed[i].push_back(sta[tp]);sta[++tp]=i;
    }
    for(int i=1;i<=tp;i++)vis[i]=true;tp=0;sta[0]=0;
    for(int i=1;i<=n;i++)
    {
        while(tp&&p[sta[tp]]>p[i])tp--;L[i]=min(L[i],sta[tp]);
        if(tp)ed[sta[tp]].push_back(i),ed[i].push_back(sta[tp]);sta[++tp]=i;
    }
    for(int i=1;i<=tp;i++)vis[i]=true;tp=0;sta[0]=n+1;
    for(int i=n;i;i--)
    {
        while(tp&&p[sta[tp]]>p[i])tp--;R[i]=max(R[i],sta[tp]);
        if(tp)ed[sta[tp]].push_back(i),ed[i].push_back(sta[tp]);sta[++tp]=i;
    }
    for(int i=1;i<=tp;i++)vis[i]=true;
    for(int i=1;i<=n;i++)sort(ed[i].begin(),ed[i].end()),ed[i].erase(unique(ed[i].begin(),ed[i].end()),ed[i].end());
}
void add(int x,int y,bool op){while(x<=n)num[op][x]+=y,x+=x&-x;}
long long gt(int x,bool op){long long r(0);while(x)r+=num[op][x],x-=x&-x;return r;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&p[i]);
    }
    init();wkot();
    if(n==1)printf("1\n");
    else if(ll[n]==1)printf("2\n");
    else if(lll[n]==1)printf("3\n");
    else printf("4\n");
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&in1,&in2);
        if(in1==in2)rs1[i]=rs2[i]=1;
        else
        {
            if(ll[in2]<=in1)rs1[i]=2,rs2[i]=1ll*(in2-in1+1)*(in2-in1)>>1;
            else 
            {
                if(lll[in2]<=in1)rs1[i]=3,qr1[in2].push_back(P(in1,i));
                else rs1[i]=4,qr2[in2].push_back(P(in1,i));
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        add(n-ll[i]+1,1,0);add(n-ll[i]+1,ll[i],1);
        for(vector<P>::iterator ite=qr1[i].begin();ite!=qr1[i].end();ite++)rs2[ite->second]=gt(n-ite->first+1,1)-gt(n-ite->first+1,0)*ite->first;
    }
    memset(num,0,sizeof(num));
    for(int i=1;i<=n;i++)
    {
        add(n-lll[i]+1,1,0);add(n-lll[i]+1,lll[i],1);
        for(vector<P>::iterator ite=qr2[i].begin();ite!=qr2[i].end();ite++)rs2[ite->second]=gt(n-ite->first+1,1)-gt(n-ite->first+1,0)*ite->first;
    }
    for(int i=1;i<=q;i++)printf("%d %lld\n",rs1[i],rs2[i]);
    return 0;
}