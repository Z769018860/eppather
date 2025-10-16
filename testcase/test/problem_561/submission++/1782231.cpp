#include <bits/stdc++.h>
typedef long long ll;typedef unsigned long long ull; typedef double db;typedef long double ldb;
#define fre(x) freopen(#x ".in","r",stdin),freopen(#x ".out","w",stdout)
#define Rep(i,a,b) for(int i=a;i<=b;++i) 
#define Dwn(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define mair make_pair
#define fir first
#define sec second
using namespace std;

const int maxn=5e5+10,Mod=998244353;

constexpr int pw(int x,int p){int res=1,base=x;while(p){if(p&1)res=1LL*res*base%Mod;base=1LL*base*base%Mod;p>>=1;}return res;}
constexpr int Inv(int x){return pw(x,Mod-2);}

constexpr int inv6=Inv(6);

int prime[maxn],cnt;
bool vis[maxn];

void Seive(const int n=1e5){ Rep(i,2,n){ if(!vis[i])prime[++cnt]=i; for(int j=1;j<=cnt && i*prime[j]<=n;++j){ vis[i*prime[j]]=true; if(i%prime[j]==0)break; } } }

int n,m,q;
unordered_map<int,int>f;
vector<int>Num,vec;
int Q[maxn];

void Div(int x){
	for(int j=1;j<=cnt && prime[j]*prime[j]<=x;++j)if(x%prime[j]==0){
		Num.emplace_back(prime[j]);while(x%prime[j]==0)x/=prime[j];
	}if(x>1)Num.emplace_back(x);
}

void Dfs(int step,int val){
	if(step==Num.size())return vec.emplace_back(val),void();
	Dfs(step+1,val);
	for(ll tmp=1LL*val*Num[step];tmp<=n;tmp*=Num[step])Dfs(step+1,tmp);
}

unordered_map<int,int>Mem;

int Sum(int x){ return 1LL*x*(x+1)%Mod*(x+x+1)%Mod*inv6%Mod; }

int Calc(int n){
	if(Mem.count(n))return Mem[n];
	int V=(1<<Num.size()),res=0;
	for(int s=0;s<V;++s){
		ll v=1;
		for(int i=0;i<Num.size();++i)if((s>>i)&1){
			if(v*Num[i]>n){v=-1;break;}
			else v*=Num[i];
		}if(v==-1)continue;
		if(!__builtin_parity(s))res=(res+1LL*v*v%Mod*Sum(n/v))%Mod;
		else res=(res-1LL*v*v%Mod*Sum(n/v))%Mod;
	}
	return Mem[n]=res;
}

void solve(){Seive();
	cin>>n>>m>>q;Rep(i,1,m){ int p,x;cin>>p>>x;f[p]=(f[p]+1LL*x*Inv(p))%Mod;Div(p); }
	Rep(i,1,q)cin>>Q[i],Div(Q[i]);
	sort(Num.begin(),Num.end());Num.erase(unique(Num.begin(),Num.end()),Num.end());
	Dfs(0,1);sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());
	for(auto p : Num)for(auto it : vec)if(1LL*it*p<=n)f[it*p]=(f[it*p]+f[it])%Mod;
	for(auto it : vec)f[it]=1LL*it*it%Mod*f[it]%Mod*Calc(n/it)%Mod;
	
	reverse(vec.begin(),vec.end());
	for(auto p : Num)for(auto it : vec)if(it%p==0)f[it/p]=(f[it/p]+f[it])%Mod;
	for(auto it : vec)f[it]=(1LL*f[it]*Inv(it)%Mod+Mod)%Mod;
	Rep(i,1,q)cout<<f[Q[i]]<<"\n";
}

int main (){ ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);return solve(),0; }