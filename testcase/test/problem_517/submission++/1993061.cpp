#include<bits/stdc++.h>

using namespace std;
namespace fast_IO{
#define IOSIZE 100000
int precision=3,POW[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};char ibuf[IOSIZE],obuf[IOSIZE],*p1=ibuf,*p2=ibuf,*p3=obuf;
#ifdef ONLINE_JUDGE
#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#define isdigit(ch) (ch>47&&ch<58)
#define isspace(ch) (ch<33)
#endif
template<typename T>inline T read(){T s=0;int w=1;char ch;while(ch=getchar(),!isdigit(ch)&&(ch!=EOF))if(ch==45)w=-1;if(ch==EOF)return 0;while(isdigit(ch))s=s*10+ch-48,ch=getchar();return s*w;}template<typename T>inline bool read(T&s){s=0;int w=1;char ch;while(ch=getchar(),!isdigit(ch)&&(ch!=EOF))if(ch==45)w=-1;if(ch==EOF)return 0;while(isdigit(ch))s=s*10+ch-48,ch=getchar();return s*=w,1;}inline bool read(char&s){while(s=getchar(),isspace(s));return 1;}inline bool read(char*s){char ch;while(ch=getchar(),isspace(ch));if(ch==EOF)return 0;while(!isspace(ch))*s++=ch,ch=getchar();*s='\000';return 1;}template<typename T>inline void print(T x){if(x<0)putchar(45),x=-x;if(x>9)print(x/10);putchar(x%10+48);}inline void print(char x){putchar(x);}inline void print(char*x){while(*x)putchar(*x++);}inline void print(const char*x){for(int i=0;x[i];i++)putchar(x[i]);}inline bool read(std::string&s){s="";char ch;while(ch=getchar(),isspace(ch));if(ch==EOF)return 0;while(!isspace(ch))s+=ch,ch=getchar();return 1;}inline void print(std::string x){for(int i=0,n=x.size();i<n;i++)putchar(x[i]);}inline bool read(bool&b){char ch;while(ch=getchar(),isspace(ch));b=ch^48;return 1;}inline void print(bool b){putchar(b+48);}inline bool read(double&x){int a=0,b=0;char ch=getchar();bool f=0;while(ch<48||ch>57){if(ch==45)f=1;ch=getchar();}while(47<ch&&ch<58){a=(a<<1)+(a<<3)+(ch^48);ch=getchar();}if(ch!=46){x=f?-a:a;return 1;}ch=getchar();while(47<ch&&ch<58){b=(b<<1)+(b<<3)+(ch^48),ch=getchar();}x=b;while(x>1)x/=10;x=f?-a-x:a+x;return 1;}inline void print(double x){if(x<0){putchar(45),x=-x;}x=round((long double)x*POW[precision])/POW[precision],print((long long)x),putchar(46),x-=(long long)(x);for(int i=1;i<=precision;i++)x*=10,putchar(x+48),x-=(int)x;}template<typename T,typename...T1>inline int read(T& a,T1&...other){return read(a)+read(other...);}template<typename T,typename...T1>inline void print(T a,T1...other){print(a),print(other...);}struct Fast_IO{~Fast_IO(){fwrite(obuf,p3-obuf,1,stdout);}}io;template<typename T>Fast_IO& operator>>(Fast_IO&io,T&b){return read(b),io;}template<typename T>Fast_IO& operator<<(Fast_IO&io,T b){return print(b),io;}
#define cout io
#define cin io
#define endl '\n'
}using namespace fast_IO;
namespace TYX_YNXK{
    #define il inline
    #define bl bool
    #define ll long long
    #define vd void
    #define N 100005
    #define M 35
    #define INF 0x3f3f3f3f
    #define mod 1919891
    #define DEBUG cout<<"You are right,but you are wrong"<<'\n'
    #define END cout<<"You are right,but you are right now"<<'\n'
    int n,s[N],pre[N][M],ans[M],rt;
    int m,tag,lst;
    int tot;
	struct node{
    	int son[2];
    	int sz;
    	int sum[M];
	}t[N*M];
	il vd pushup(int k){
		t[k].sz=t[t[k].son[0]].sz+t[t[k].son[1]].sz;
		for(int i=0;i<=30;i++) t[k].sum[i]=t[t[k].son[0]].sum[i]+t[t[k].son[1]].sum[i];
	}
	vd ins(int &k,int x,int base){
		if(!k) k=++tot;
		if(!~base){
			++t[k].sz;
			for(int i=0;i<=30;i++){
				t[k].sum[i]+=x>>i&1;
			}
			return;
		}
		ins(t[k].son[x>>base&1],x,base-1);
		pushup(k);
	}
	vd query(int k,int pos,int base){
		if(!k||!~base){
			for(int i=0;i<=30;i++) ans[i]+=t[k].sum[i]?pos:0;
			return;
		}
		int v=lst>>base&1;
		if(pos<=t[t[k].son[v]].sz){
			query(t[k].son[v],pos,base-1);
		}else{
			for(int i=0;i<=30;i++) ans[i]+=t[t[k].son[v]].sum[i];
			query(t[k].son[v^1],pos-t[t[k].son[v]].sz,base-1);
		}
	}
    signed main(){


    	cin>>n;
    	for(int i=1;i<=n;i++){
    		cin>>s[i];
    		for(int j=0;j<=30;j++){
    			pre[i][j]=pre[i-1][j]+(s[i]>>j&1);
			}
		}
		cin>>m;
		while(m--){
			int opt;
			cin>>opt;
			switch(opt){
				case 1:{
					int x;
					cin>>x;
					x^=tag;
					s[++n]=x;
					for(int j=0;j<=30;j++){
						pre[n][j]=pre[n-1][j]+(x>>j&1);
					}
					break;
				}
				case 2:{
					int l,r,len;
					cin>>l>>r;len=r-l+1;
					for(int i=0;i<=30;i++) ans[i]=0;
					if(r<=t[rt].sz){
						query(rt,l-1,30);
						for(int i=0;i<=30;i++) ans[i]=-ans[i];
						query(rt,r,30);
					}else if(l<=t[rt].sz){
						query(rt,l-1,30);
						for(int i=0;i<=30;i++) ans[i]=-ans[i];
						query(rt,t[rt].sz,30);
						r-=t[rt].sz;
						for(int j=0;j<=30;j++){
							ans[j]+=pre[r][j];
						}
					}else{
						l-=t[rt].sz;
						r-=t[rt].sz;
						for(int j=0;j<=30;j++){
							ans[j]+=pre[r][j]-pre[l-1][j];
						}
					}
					ll res=0;
					for(int j=0;j<=30;j++){
						if(tag>>j&1){
							res+=1ll*(len-ans[j])<<j;
						}else{
							res+=1ll*ans[j]<<j;
						}
					}
					cout<<res<<'\n';
					break;
				}
				case 3:{
					int x;
					cin>>x;
					tag^=x;
					break;
				}
				case 4:{
					for(int i=1;i<=n;i++){
						ins(rt,s[i],30);
					}
					lst=tag;
					n=0;
					break;
				}
			}
		}
        return 0;
    }
}
signed main(){
    TYX_YNXK::main();
    return 0;
}