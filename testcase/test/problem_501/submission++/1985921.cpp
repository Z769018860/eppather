#include<cstdio>
#include<algorithm>
#include<cmath>
#define fo(i,a,b) for(i=a;i<=b;i++)
using namespace std;
typedef long long ll;
ll a[100000+10],sta[100000+10],b[100000+10];
ll i,j,k,l,t,m,tot,top,now,cnt;
ll n;
bool czy;
ll random(ll x){
    ll t=rand()%10000;
    t=t*10000+rand()%10000;
    t=t*10000+rand()%10000;
    t=t*10000+rand()%10000;
    return t%x;
}
ll mul(ll a,ll b,ll p){
    if (!b) return 0;
    ll t=mul(a,b/2,p);
    t=(t+t)%p;
    if (b%2) t=(t+a)%p;
    return t;
}
ll qsm(ll x,ll y,ll mo){
    if (!y) return 1;
    ll t=qsm(x,y/2,mo);
    t=mul(t,t,mo);
    if (y%2) t=mul(t,x,mo);
    return t;
}
bool Miller_Rabin(ll n){
    if (n==1) return 0;
    int s=5,t=0,i;
    ll a,p,k=n-1;
    while (k%2==0) k/=2,t++;
    while (s--){
        a=random(n-1)+1;
        p=a=qsm(a,k,n);
        fo(i,1,t){
            a=mul(a,a,n);
            if (a==1&&p!=1&&p!=n-1) return 0;
            p=a;
        }
        if (a!=1) return 0;
    }
    return 1;
}
ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
ll Pollard_Rho(ll n){
    ll k,x,y,c,d,i=1;
    while (1){
        c=random(n-1);
        k=2;y=x=random(n);
        i=1;
        while (1){
            y=(mul(y,y,n)+c)%n;
            d=gcd(abs(x-y),n);
            if (i==k) x=y,k<<=1;
            i++;
            if (d!=1) break;
        }
        if (d!=n) return d;
    }
}
void work(ll n){
    if (Miller_Rabin(n)){
        sta[++top]=n;
        return;
    }
    ll p=Pollard_Rho(n);
    ll q=n/p;
    work(p);work(q);
}
bool pd(ll n){
    while (n%2==0) n/=2;
    if (n==1) return 1;else return 0;
}
void dfs(ll n){
    if (pd(n)){
        cnt=0;
        while (n%2==0) cnt++,n/=2;
        czy=1;
        return;
    }
    ll t=4,l=2;
    while (t-1<=n){
        if (n%(t-1)==0){
            top++;
            b[top]=l;
            dfs(n/(t-1));
            if (czy) return;
            top--;
        }
        t*=2;
        l++;
    }
}
int main(){
    czy=0;
    scanf("%lld",&n);
    if (n==1){
        printf("1\n");
        printf("1\n");
        return 0;
    }
    dfs(n);
        if (!czy){
        printf("qnq\n");
        return 0;
    }
    a[tot=1]=1;
    now=3;
    fo(i,1,top){
        k=b[i];
        while (k){
            a[++tot]=now;
            k--;
        }
        if (now==1) now=3;else now=1;
    }
    while (cnt){
        a[++tot]=2;
        cnt--;
    }
    a[++tot]=now;
    printf("%lld\n",tot);
    fo(i,1,tot) printf("%lld ",a[i]);
}