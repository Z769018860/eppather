#include<bits/stdc++.h>
#define ll long long
#define N 3000
#define lowbit(x) (-x&x)
using namespace std;
ll shu1[N][N],shu2[N][N],shu3[N][N],shu4[N][N],n,m;
ll read(){char c=getchar();
    if(c==EOF)return 0;
    ll n=0;
    bool p=true;
    while(c!='-'&&(c<'0'||c>'9'))c=getchar();
    if(c=='-')p=false,c=getchar();
    while(c<='9'&&c>='0')n=(n<<1)+(n<<3)+c-'0',c=getchar();
    return p?n:-n;
}
void add(ll a,ll b,ll w,ll shu[][N]){ll i,k;
    for(i=a;i<=n;i+=lowbit(i)){
        for(k=b;k<=m;k+=lowbit(k)){
            shu[i][k]+=w;
        }
    }
}
ll query(ll a,ll b,ll shu[][N]){ll i,k,ans=0;
    for(i=a;i;i-=lowbit(i)){
        for(k=b;k;k-=lowbit(k)){
            ans+=shu[i][k];
        }
    }
    return ans;
}
ll getsum(ll x,ll y){
    return query(x,y,shu1)*(x+1)*(y+1)-query(x,y,shu2)*(y+1)-query(x,y,shu3)*(x+1)+query(x,y,shu4);
}
int main(){ll i,k,a,b,c,d,e,p,w;
    n=read(),m=read();
    while(1){p=read();
        if(p==0)break;
        a=read(),b=read(),c=read(),d=read();
        if(p==1){w=read();
            add(a,b,w,shu1),add(a,d+1,-w,shu1),add(c+1,b,-w,shu1),add(c+1,d+1,w,shu1);
            add(a,b,w*a,shu2),add(a,d+1,-w*a,shu2),add(c+1,b,-w*(c+1),shu2),add(c+1,d+1,w*(c+1),shu2);
            add(a,b,w*b,shu3),add(a,d+1,-w*(d+1),shu3),add(c+1,b,-w*b,shu3),add(c+1,d+1,w*(d+1),shu3);
            add(a,b,w*a*b,shu4),add(a,d+1,-w*a*(d+1),shu4),add(c+1,b,-w*(c+1)*b,shu4),add(c+1,d+1,w*(c+1)*(d+1),shu4);
        }
        else printf("%lld\n",getsum(c,d)-getsum(c,b-1)-getsum(a-1,d)+getsum(a-1,b-1));
    }
}