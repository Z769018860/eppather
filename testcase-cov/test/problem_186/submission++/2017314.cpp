#include<bits/stdc++.h>
using namespace std ; 
inline void fire(){freopen("data.in","r",stdin);freopen("data.out","w",stdout);}
namespace Fread{const int SIZE=(1<<18);char buf[SIZE],*S,*T;inline char getchar(){if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}}
namespace Fwrite{const int SIZE=(1<<18);char buf[SIZE],*S=buf,*T=buf+SIZE;inline void flush(){fwrite(buf,1,S-buf,stdout),S=buf;}inline void putchar(char c){*S++=c;if(S==T)flush();}struct NTR{ ~NTR(){flush();}}ztr;}
#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif
namespace Fastio{struct Reader{template<typename T>Reader&operator>>(T&x){char c=getchar();bool f=false;while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}x=0;while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}if(f)x=-x;return *this;}Reader&operator>>(double & x){char c=getchar();short f=1,s=0;x=0;double t=0;while((c<'0'||c>'9')&&c!='.'){if(c=='-')f*=-1;c=getchar();}while(c>='0'&&c<='9'&&c!='.')x=x*10+(c^48),c=getchar();if(c=='.')c=getchar();else return x*=f,*this;while(c>='0'&&c<='9')t=t*10+(c^48),s++,c=getchar();while(s--)t/=10.0;x=(x+t)*f;return*this;}Reader&operator>>(long double&x){char c=getchar();short f=1,s=0;x=0;long double t=0;while((c<'0'||c>'9')&&c!='.'){if(c=='-')f*=-1;c=getchar();}while(c>='0'&&c<='9'&&c!='.')x=x*10+(c^48),c=getchar();if(c=='.')c=getchar();else return x*=f,*this;while(c>='0'&&c<='9')t=t*10+(c^48),s++,c=getchar();while(s--)t/=10.0;x=(x+t)*f;return*this;}Reader&operator>>(__float128&x){char c=getchar();short f=1,s=0;x=0;__float128 t=0;while((c<'0'||c>'9')&&c!='.'){if(c=='-')f*=-1;c=getchar();}while(c>='0'&&c<='9'&&c!='.')x=x*10+(c^48),c=getchar();if(c=='.') c = getchar();else return x*=f,*this;while(c>='0'&&c<='9')t=t*10+(c^48),s++,c=getchar();while(s--)t/=10.0;x=(x+t)*f;return *this;}Reader&operator>>(char&c){c=getchar();while(c=='\n'||c==' '||c=='\r')c=getchar();return *this;}Reader&operator>>(char*str){int len=0;char c=getchar();while(c=='\n'||c==' '||c=='\r')c=getchar();while(c!='\n'&&c!=' '&&c!='\r')str[len++]=c,c=getchar();str[len]='\0';return *this;}Reader&operator>>(string&str){char c=getchar();str.clear();while(c=='\n'||c==' '||c=='\r')c=getchar();while(c!='\n'&&c!=' '&&c!='\r')str.push_back(c),c=getchar();return *this;}template<class _Tp>Reader&operator>>(vector<_Tp>&vec){for(unsigned i=0;i<vec.size();i++)cin>>vec[i];return *this;}template<class _Tp,class _tp>Reader&operator>>(pair<_Tp,_tp>&a){cin>>a.first>>a.second;return *this;}Reader(){}}cin;struct Writer{static const int set_precision = 6;typedef int mxdouble;template<typename T>Writer&operator<<(T x){if(x==0)return putchar('0'),*this;if(x<0)putchar('-'),x=-x;static int sta[45];int top=0;while(x)sta[++top]=x%10,x/=10;while(top)putchar(sta[top]+'0'),--top;return*this;}Writer&operator<<(double x){if(x<0)putchar('-'),x=-x;mxdouble _=x;x-=(double)_;static int sta[45];int top=0;while(_)sta[++top]=_%10,_/=10;if(!top)putchar('0');while(top)putchar(sta[top]+'0'),--top;putchar('.');for(int i=0;i<set_precision;i++)x*=10;_=x;while(_)sta[++top]=_%10,_/=10;for(int i=0;i<set_precision-top;i++)putchar('0');while(top)putchar(sta[top]+'0'),--top;return*this;}Writer&operator<<(long double x){if(x<0)putchar('-'),x=-x;mxdouble _=x;x-=(long double)_;static int sta[45];int top=0;while(_)sta[++top]=_%10,_/=10;if(!top)putchar('0');while(top)putchar(sta[top]+'0'),--top;putchar('.');for(int i=0;i<set_precision;i++)x*=10;_=x;while(_)sta[++top]=_%10,_/=10;for(int i=0;i<set_precision-top;i++)putchar('0');while(top)putchar(sta[top]+'0'),--top;return*this;}Writer&operator<<(__float128 x){if(x<0)putchar('-'),x=-x;mxdouble _=x;x-=(__float128)_;static int sta[45];int top=0;while(_)sta[++top]=_%10,_/=10;if(!top)putchar('0');while(top)putchar(sta[top]+'0'),--top;putchar('.');for(int i=0;i<set_precision;i++)x*=10;_=x;while(_)sta[++top]=_%10,_/=10;for(int i=0;i<set_precision-top;i++)putchar('0');while(top)putchar(sta[top]+'0'),--top;return*this;}Writer&operator<<(char c){putchar(c);return*this;}Writer&operator<<(char*str){int cur=0;while(str[cur])putchar(str[cur++]);return *this;}Writer&operator<<(const char*str){int cur=0;while(str[cur])putchar(str[cur++]);return *this;}Writer&operator<<(string str){int fir=0,ed=str.size();while(fir<ed) putchar(str[fir++]);return *this;}template<class _Tp>Writer&operator<<(vector<_Tp>vec){for(unsigned i=0;i<vec.size()-1;i++)cout<<vec[i]<<" ";cout<<vec[vec.size()-1];return *this;}template<class _Tp,class _tp>Writer&operator<<(pair<_Tp,_tp>a){cout<<a.first<<" "<<a.second;return *this;}Writer(){}}cout;}
#define FastI  Fastio::cin
#define FastO  Fastio::cout
#define ull unsigned long long
#define int long long
#define INF (0x66ccff0712ll)
#define M (0x6cf)
#define N (0x66ccff)
#define maxn (2000010)
#define MAXN (int)(1e6+5)
#define MAXM (int)(1e5+5)
#define re register
#define lower_bound std::lower_bound
#define upper_bound std::upper_bound
#define unique std::unique
#define string std::string
#define pair std::pair
#define vector std::vector
#define map std::map
#define set std::set
#define queue std::queue
#define make_pair std::make_pair
#define priority_queue std::priority_queue
#define bitset std::bitset
#define deque std::deque
#define array std::array
#define unordered_set std::unordered_set
#define unordered_map std::unordered_map
#define list std::list
#define it map<int,int>::iterator
#define min(a,b) (a)>(b)?(b):(a)
#define endl "\n"
#define PII pair<int,int>
#define swap std::swap 
#define mid ((l+r)>>1)
#define lc son[x][0]
#define rc son[x][1]
int fa[N],son[N][2],val[N],ans[N],st[N];
bool rev[N];
inline bool isroot(int x){
	return ((son[fa[x]][0]==x)||(son[fa[x]][1]==x));
}
inline void push_up(int x){
	ans[x]=ans[lc]^ans[rc]^val[x];
}
inline void reserve(int x){
    swap(lc,rc);
	rev[x]^=1;
}
inline void push_down(int x){
	if(rev[x]){
		if(lc)reserve(lc);
		if(rc)reserve(rc);
		rev[x]=0;
	}
}
inline void rotate(int x){
	int y=fa[x],z=fa[y],k=son[y][1]==x,w=son[x][!k];
	if(isroot(y))
        son[z][son[z][1]==y]=x;
    son[x][!k]=y;
	son[y][k]=w;
	if(w)
        fa[w]=y;
    fa[y]=x;fa[x]=z;
	push_up(y);
}
inline void splay(int x){
	int y=x,z=0;
	st[++z]=y;
	while(isroot(y))
        st[++z]=y=fa[y];
	while(z)
        push_down(st[z--]);
	while(isroot(x)){
		y=fa[x],z=fa[y];
		if(isroot(y))
			rotate((son[y][0]==x)^(son[z][0]==y)?x:y);
		rotate(x);
	}
	push_up(x);
}
inline void access(int x){
	for(int y=0;x;x=fa[y=x]){
		splay(x);
		rc=y;
        push_up(x);
    }
}
inline void toroot(int x){
	access(x);
	splay(x);
	reserve(x);
}
inline int Find(int x){
	access(x);
	splay(x);
	while(lc){
        push_down(x);
        x=lc;
    }
    splay(x);
	return x;
}
inline void split(int x,int y){
	toroot(x);
	access(y);
    splay(y);
}
inline void link(int x,int y){
	toroot(x);
	if(Find(y)!=x)
        fa[x]=y;
}
inline void cut(int x,int y){
	toroot(x);
	if(Find(y)==x&&fa[y]==x&&!son[y][0]){
		fa[y]=son[x][1]=0;
		push_up(x);
	}
}
signed main(){
	int n,m;FastI>>n>>m;
	for(int i=1;i<=n;++i)
		FastI>>val[i];
	while(m--){
		int opt,x,y;
        FastI>>opt>>x>>y;
		if(opt==0){
			split(x,y);
			FastO<<ans[y]<<endl;
		}
		else if(opt==1){
			link(x,y);
		}
		else if(opt==2){
			cut(x,y);
		}
		else if(opt==3){
			splay(x);
			val[x]=y;
		}
	}
}