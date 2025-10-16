







#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 1e6 + 10;

struct node{
	int len, link;
	map <char, int> nxt;
}; node sam[MAX << 1];
int psz, lst;


void sam_init(){
	psz = 1;
	sam[1].len = 0, sam[1].link = 0;
	lst = 1;
}

void insert(char c){
	int cur = ++psz;
	sam[cur].len = sam[lst].len + 1;
	int now = lst;
	while(now and !sam[now].nxt.count(c)){
		sam[now].nxt[c] = cur;
		now = sam[now].link;
	}
	if(!now){
		sam[cur].link = 1;
		lst = cur;
		return ;
	}
	int v = sam[now].nxt[c];
	if(sam[v].len == sam[now].len + 1){
		sam[cur].link = v;
		lst = cur;
		return ;
	}
	int clone = ++psz;
	sam[clone].len = sam[now].len + 1;
	sam[clone].nxt = sam[v].nxt;
	sam[clone].link = sam[v].link;
	while(now and sam[now].nxt[c] == v){
		sam[now].nxt[c] = clone;
		now = sam[now].link;
	}
	sam[cur].link = sam[v].link = clone;
	lst = cur;
}

int maxn[MAX];
int minn[MAX];
bool vis[MAX];
int vis2[MAX];


void solve(){
	int fw = read();
	string s;
	cin>>s;
	int n = s.length();
	sam_init();
	for(int i = 0; i < n; i++){
		insert(s[i]);
	}
	string t;
	int cnt = 0;
	for(int i = 1; i <= psz; i++)	minn[i] = inf;
	while(cin>>t){
		cnt++;
		int m = t.length();
		int p = 1, len = 0;
		for(int i = 0; i < m; i++){
			while(p != 1 and !sam[p].nxt[t[i]])	p = sam[p].link, len = sam[p].len;
			if(sam[p].nxt[t[i]]){
				p = sam[p].nxt[t[i]];
				len++;
			}
			vis[p] = 1, maxn[p] = max(maxn[p], len);
		}
		for(int i = 1; i <= psz; i++)	if(vis[i])	minn[i] = min(minn[i], maxn[i]);
		for(int i = 1; i <= psz; i++)	vis2[i] += vis[i];
		for(int i = 1; i <= psz; i++)	vis[i] = maxn[i] = 0;
	}
	if(!cnt)	write(n), endl;
	else{
		int ans = 0;
		for(int i = 1; i <= psz; i++){
			if(vis2[i] == cnt)	ans = max(ans, minn[i]);
		}
		write(ans), endl;
	}
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}