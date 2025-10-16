#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int T,n,k,ps,ls,a[Maxn+5],s[Maxn+5],p[Maxn+5],l[Maxn+5];
inline void F() {puts("No"); exit(0);}
inline void Print(int &it,int k)
{while(k && it<=n) if(a[it++]) a[it-1]=0,k--,printf("%d ",it-1);}
inline int Check1()
{
    int it=0,pos=0; For(i,1,k-1)
    {
        it+=k-2; while(it<s[p[i+1]]) it+=k;
        if(it>s[l[i]]) return 0;
    } printf("Yes\n%d\n",k),it=0;
    For(i,1,k-1)
    {
        int pr=it; it+=k-2; while(it<s[p[i+1]]) it+=k;
        printf("%d %d ",it-pr+2,p[i]),Print(pos,it-pr),printf("%d\n",l[i]);
    } printf("%d %d ",s[n]-it+2,p[k]),Print(pos,s[n]-it),printf("%d\n",l[k]);
    return 1;
}
inline int Check2()
{
    int it=0,pos=0; For(i,2,k)
    {
        it=max(it,s[p[i]]),it+=k-2;
        if(it>s[l[i-1]]) return 0;
    } printf("Yes\n%d\n",k),it=0;
    For(i,2,k)
    {
        it=max(it,s[p[i]]),it+=k-2;
        while(s[pos]<=s[p[i]]) pos++;
        printf("%d %d ",k,p[i]),Print(pos,k-2),printf("%d\n",l[i-1]);
    } printf("%d %d ",n-k*(k-1),p[1]),pos=0;
    Print(pos,n-k*(k-1)-2),printf("%d\n",l[k]); return 1;
}

int main()
{
    

    T=read(),n=read(),k=read();
    For(i,1,n) a[i]=(read()%k!=0);
    if(n<1ll*k*k || n%k || a[1] || a[n]) F();
    For(i,1,n) if(!a[i]) p[++ps]=i;
    Rof(i,n,1) if(!a[i]) l[++ls]=i;
    if(ps<k || ls<k || p[k]>=l[k]) F();
    ps=ls=k,reverse(l+1,l+k+1);
    For(i,p[k]+1,l[1]-1) a[i]=1;
    For(i,1,n) s[i]=s[i-1]+a[i];
    if(Check1() || Check2()) return 0; else F();
    return 0;
}