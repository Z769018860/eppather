
#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define mset multiset
#define ll long long
#define ui unsigned int
#define ull unsigned ll
#define ret return
#define il inline
#define tpcTi template<class T>il
#define cst const
#define db double
#define ld long db
#define gc getchar
#define pc putchar
#define spe pc(' ')
#define edl pc('\n')
cst ll INF=9223372036854775807;
cst int inf=2147483647;
cst db pi=acos(-1.0),eps=1e-12;
namespace mySTL{
	tpcTi T _max(T a,T b){ret a>b?a:b;}
	tpcTi T _min(T a,T b){ret a<b?a:b;}
	tpcTi T _abs(T a){ret a<0?-a:a;}
	il ll mod(ll a,ll p){ret (a>=p?a-p:a);}
	il ll madd(ll a,ll b,ll p){ret mod(a+b,p);}
	il ll msub(ll a,ll b,ll p){ret mod(a-b+p,p);}
	il ll exmul(ll a,ll b,ll p){ll ans=0;while(b){if(b&1)ans=madd(ans,a,p);a=madd(a,a,p);b>>=1;}ret ans;}
	il ll expow(ll a,ll b,ll p){ll ans=1;while(b){if(b&1)ans=exmul(ans,a,p);a=exmul(a,a,p);b>>=1;}ret ans;} 
	il ll pw(ll a,ll b,ll p=INF){if(b==0)ret 1;if(b==1)ret a%p;ll mid=pw(a,b/2,p)%p;if(b&1)ret mid*mid%p*a%p;else{ret mid*mid%p;}}
	il ll pinv(ll a,ll p){ret pw(a,p-2,p);}
	il ll pdiv(ll a,ll b,ll p){ret a*pinv(b,p)%p;}
	il ll expdiv(ll a,ll b,ll p){ret exmul(a,pinv(b,p),p);}
	tpcTi T read(){char c=gc();T f=1,ans=0;while(c<'0'||c>'9'){if(c=='-') f=-1;c=gc();}while(c>='0'&&c<='9')ans=(ans*10+c-'0'),c=gc();ret ans*f;}
	tpcTi void _swap(T &a,T &b){a^=b,b^=a,a^=b;}
	il void write(int x){if(x<0){pc('-');x=-x;}if(x>=10){write(x/10);}pc(x%10+'0');}
	il void write(ll x){if(x<0){pc('-');x=-x;}if(x>=10){write(x/10);}pc(x%10+'0');}
	tpcTi T gcd(T a,T b){ret b?gcd<T>(b,a%b):a;}
	tpcTi T lcm(T a,T b){ret a/gcd<T>(a,b)*b;}
	il void write(string s){int len=s.length();for(int i=0;i<len;i++) pc(s[i]);}
	il void bwrite(int x,int n=-1){stack<int>stk;int len=0;while(x){stk.push(x&1);x>>=1;len++;}if(n!=-1){for(int i=1;i<=n-len;i++){pc('0');}}while(!stk.empty()){write(stk.top());stk.pop();}}
	il char readc(){char c=getchar();while(c==' '||c=='\n'||c=='\r'){c=getchar();}ret c;}
	il int lowbit(int x){ret x&-x;}
	il int countbit(ll x){int cnt=0;while(x){cnt+=x&1,x>>=1;}ret cnt;}
	il bool isprime(ll x){if(x<2){ret 0;}for(ll i=2;i<=x/i;i++){if(x%i==0){ret 0;}}ret 1;}
	il int dcmp(db x){ret (fabs(x)<=eps?0:(x>0?1:-1));}
}
using namespace mySTL;
namespace myDS{
	class DSU{public:vector<int>father_of_DSU;int size_of_DSU;
		il void init_DSU(int n){size_of_DSU=n;father_of_DSU.push_back(0);for(int i=1;i<=n;i++){father_of_DSU.push_back(i);}}
		il int search_father_of_node(int x){ret (x==father_of_DSU[x]?x:father_of_DSU[x]=search_father_of_node(father_of_DSU[x]));}
		il void merge_two_nodes(int x,int y){int f1=search_father_of_node(x),f2=search_father_of_node(y);if(f1!=f2){father_of_DSU[f1]=f2;}}
		il bool check_two_nodes(int x,int y){ret search_father_of_node(x)==search_father_of_node(y);}};
	class Point{public:db x,y;
		Point(){}Point(cst db& x,cst db& y):x(x),y(y){}	
		il db len(){ret sqrt(x*x+y*y);}	
		il db len2(){ret x*x+y*y;}};
	#define Vector Point
	il Point operator+(cst Point& a,cst Point& b){ret Point{a.x+b.x,a.y+b.y};}
	il Point operator-(cst Point& a,cst Point& b){ret Point{a.x-b.x,a.y-b.y};}
	il Point operator*(cst Point& a,cst db x){ret Point{a.x*x,a.y*x};} 
	il Point operator*(cst db x,cst Point& a){ret Point{a.x*x,a.y*x};} 
	il db cross(cst Point& a,cst Point& b){ret a.x*b.y-a.y*b.x;}
	il db dot(cst Point& a,cst Point& b){ret a.x*b.x+a.y*b.y;}
	il Vector rorate90(cst Vector& a){ret Vector{-a.y,a.x};}
	il Point projection(cst Point& a,cst Point& b,cst Point& p){Vector v=b-a;db projlen=dot(v,p-a)/v.len();ret a+projlen/v.len()*v;}
	class Line{public:Point a;Vector v;db pol;
		Line(){}Line(cst Point& a,cst Point& b):a(a),v(b-a),pol(atan2(v.y,v.x)){}
		il bool notleft(cst Point& b) cst{ret dcmp(cross(v,b-a))<=0;}};
	il Point lineins(cst Line& l,cst Line& r){db a1=cross(r.v,l.a-r.a);db a2=cross(r.v,l.a+l.v-r.a);db lam=a1/(a1-a2);ret l.a+lam*l.v;}
}
using namespace myDS;

cst int N=1e4;
int n,m,a[N+10],x,ans[N+10];
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	memset(ans,-0x3f,sizeof(ans));
	n=read<int>();
	m=read<int>();
	for(int i=1;i<=n;i++){
		a[i]=read<int>();
		a[i]+=a[i-1];
	}
	for(int l=1;l<=n;l++){
		for(int r=l;r<=n;r++){
			ans[r-l+1]=_max<int>(ans[r-l+1],a[r]-a[l-1]);
		}
	}
	for(int i=n;i>=1;i--){
		ans[i]=_max<int>(ans[i],ans[i+1]);
	}
	while(m--){
		x=read<int>();
		write(ans[x]);
		edl;
	}
	ret 0;
}