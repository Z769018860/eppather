#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define fi first
#define se second
#define pb push_back
#define pii pair<LL,LL>
#define mem(a,x) memset((a),(x),sizeof(a))


#define LLL __int128

template<typename type>
inline void read(type &x)
{
	x=0;bool flag(0);char ch=getchar();
	while(!isdigit(ch)) flag=ch=='-',ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	flag?x=-x:0;
}

template<typename type>
inline void write(type x,bool mode=1)
{
	x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
	do Stack[++top]=x%10,x/=10; while(x);
	while(top) putchar(Stack[top--]|48);
	mode?putchar('\n'):putchar(' ');
}

LL qsm(LL a,LL b,LL mod){
	LL ans=1,sum=a;
	while(b){
		if(b&1) ans=ans*sum%mod;
		sum=sum*sum%mod;
		b>>=1;
	}
	return ans;
}

const LL N=1e5+10;

LL n,a[N];

string s[N];

LL tree[N];

LL lowbit(LL x){
	return x&-x;
}

void add(LL x){
	for(LL i=x;i<=n;i+=lowbit(i)) tree[i]++;
}

LL ask(LL x){
	LL ans=0;
	for(LL i=x;i;i-=lowbit(i)) ans+=tree[i];
	return ans;
}

LL tot[N],cnt;
map<LL,LL> mp;

LL query(LL l,LL r){
	return ask(r)-ask(l-1);
}

void solve(){
	read(n);
	for(LL i=1;i<=n;i++) cin>>s[i];
	LL cnt=0;
	for(LL i=1;i<=n;i++) if(s[i]=="X") cnt++;
	if(cnt>0){
		if(n==1){
			printf("L\n");
			return ;
		}
		if(cnt&1) printf("W\n");
		else printf("L\n");
		return ;
	}
	for(LL i=1;i<=n;i++){
		LL sum=1,len=s[i].length();
		for(LL j=len-1;j>=0;j--){
			if(s[i][j]=='-'){
				a[i]*=-1;
				break;
			}
			a[i]+=(s[i][j]-'0')*sum;
			sum*=10;
		}
	}
	for(LL i=1;i<=n;i++) tot[i]=a[i];
	sort(tot+1,tot+n+1);
	tot[0]=tot[1]-1;
	for(LL i=1;i<=n;i++){
		if(tot[i]!=tot[i-1]){
			mp[tot[i]]=++cnt;
		}
	}
	for(LL i=1;i<=n;i++) a[i]=mp[a[i]];
	LL ans=0;
	for(LL i=1;i<=n;i++){
		ans+=query(a[i]+1,n);
		add(a[i]);
	}
	if(ans&1) printf("W\n");
	else printf("L\n");
	return ;
}

int main(){
	LL T=1;

	while(T--){
		solve();
	}
}