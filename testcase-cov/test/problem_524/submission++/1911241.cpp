#include"algorithm"
#include"iostream"
#include"cstring"
#include"climits"
#include"cstdio"
#include"random"
#include"string"
#include"bitset"
#include"ctime"
#include"queue"
#include"map"
#include"set"
#define ls o<<1
#define rs o<<1|1
#define db double

using ll = long long;


#define  f(i,a,b) for(int i=a;i<=b;i++)
#define ff(i,a,b) for(int i=a;i>=b;i--)

using namespace std;

ll rd()<%ll x=0,w=1;char c=getchar();while(c<'0'||c>'9')<%if(c=='-')w=-1;if(c=='X')return 1000001223;c=getchar();%>while(c<='9'&&c>='0')<%x=x*10+(c-'0');c=getchar();%>return x*w;%>


int n;

ll a[1000010],b[1000010];
int cnt;
ll ans=0;


namespace STT{

    ll t[100001];
    
    int lowbit(int x){
        return x&-x;
    }
    
    void update(int x,int y){
        while(x<=n){
            t[x]+=y;
            x+=lowbit(x);
        }
        return ;
    }
    
    ll query(int x){
        ll sum=0;
        while(x>0){
            sum+=t[x];
            x-=lowbit(x);
        }
        return sum;
    }

}

using namespace STT;

namespace Wunsch{

void work(ll l,ll r){
    if(l==r)return ;
    ll mid=l+r>>1;
    ll i=l,j=mid+1,k=l;
    work(l,mid);work(mid+1,r);
    while(i<=mid&&j<=r){
        if(a[i]<=a[j]){
            b[k++]=a[i++];
        }
        else{
            b[k++]=a[j++];
            ans+=mid-i+1;
        }
    }
    while(i<=mid){
        b[k++]=a[i++];
    }
    while(j<=r){
        b[k++]=a[j++];
    }
    f(i,l,r){
        a[i]=b[i];
    }
    return ;
}

    bool main(){
        
        
        n=rd();
        f(i,1,n){
            a[i]=rd();
            
            if(a[i]==1000001223){
                cnt++;
            }
        }
        if(n==1){
                printf("L\n"); 
            return 1;
        }
        if(cnt&1){
            printf("W\n");
        }
        else if(cnt){
            printf("L\n");
        }
        else{
            work(1,n);
            if(ans&1){
                printf("W\n");
            }
            else{
                printf("L\n");
            }
        }
        
        fclose(stdin);
        fclose(stdout);
        return 1;
    }
    
}

bool ztt=Wunsch::main();

main(){;}