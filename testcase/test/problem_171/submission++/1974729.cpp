#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
char s[maxn],c[maxn];
int len[maxn],lnk[maxn],sum[maxn];
int a[maxn][26];
int p=1,cur=1;
void insert(int c){
	int nd=++cur;
	len[nd]=len[p]+1;
	while(p&&!a[p][c])a[p][c]=nd,p=lnk[p];
	if(!p){lnk[p=nd]=1;return ;}
	int q=a[p][c];
	if(len[p]+1==len[q])lnk[nd]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1;lnk[cl]=lnk[q];
		memcpy(a[cl],a[q],sizeof(a[q]));
		lnk[q]=lnk[nd]=cl;
		while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
	}
	p=nd;
}
int mn[maxn],ans;
int ed[maxn];
bool vis[maxn],bk[maxn];
void go(int &p,int c,int &l){
	while(1){
		if(a[p][c]){
			p=a[p][c],l++;
			break;
		}
		if(!l)break;
		l--;
		if(l==len[lnk[p]])p=lnk[p];
	}
}
void clr(){
	while(cur){
		len[cur]=lnk[cur]=0;
		mems(a[cur],0);
		cur--;
	}
	p=cur=1;
}
void work(){
	cin>>n>>s+1;n--;int ll=strlen(s+1);
	for(int i=1;i<=ll;i++)mn[i]=i;
	while(n--){
		cin>>c+1;int m=strlen(c+1);
		clr();
		for(int i=1;i<=m;i++)insert(c[i]-'a');
		int nd=1,l=0;
		for(int i=1;i<=ll;i++){
			go(nd,s[i]-'a',l);
			mn[i]=min(mn[i],l);
		}
	}
	for(int i=1;i<=ll;i++)ans=max(ans,mn[i]);
	printf("%lld\n",ans);
}

bool Med;
int T;
signed main(){


	
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	

	
	T=1;
	while(T--)work();
}