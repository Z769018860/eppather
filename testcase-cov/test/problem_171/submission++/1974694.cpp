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
string s[21];
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
int mn[maxn],mx[maxn],ans;
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
		mx[p]=max(mx[p],l);vis[p]=1;
	}
	mx[p]=max(mx[p],l);vis[p]=1;

}
void work(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i];
	if(n==1){printf("%lld\n",s[1].size());return ;}
	int p=1;for(int i=2;i<=n;i++)if(s[i].size()<s[p].size())p=i;
	swap(s[1],s[p]);
	for(auto c:s[1])insert(c-'a');
	mems(mn,0x3f);
	for(int i=2;i<=n;i++){
		int nd=1,l=0;
		for(auto c:s[i])go(nd,c-'a',l);
		for(int j=1;j<=cur;j++){
			if(vis[j]){
				if(i==2||bk[j])mn[j]=min(mn[j],mx[j]),bk[j]=1;
				mx[j]=0;vis[j]=0;

			}
			else if(bk[j])bk[j]=0;
		}


	}
	for(int i=1;i<=cur;i++)if(bk[i])ans=max(ans,mn[i]);
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