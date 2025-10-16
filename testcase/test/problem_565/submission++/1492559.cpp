#include<cstdio>
#include<cctype>
#include<vector>
#define IMP(lim,act) for(int qwq=(lim),i=0;i^qwq;++i)act
const int M=1e6+5,mod=998244353;
int n,m,k,F[M],G[M],P[M],*T[M<<2];std::vector<int>p[M];
int buf[M<<2],*w[25];
inline int Getlen(const int&n){
	int len(0);while((1<<len)<n)++len;return len;
}
inline int Add(const int&a,const int&b){
	return a+b>=mod?a+b-mod:a+b;
}
inline int Del(const int&a,const int&b){
	return b>a?a-b+mod:a-b;
}
inline void swap(int&a,int&b){
	int c=a;a=b;b=c;
}
inline int pow(int a,int b=mod-2){
	int ans(1);for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;return ans;
}
inline void init(const int&n){
	const int&m=Getlen(n);int*now=buf;w[m]=now;now+=1<<m;
	w[m][0]=1;w[m][1]=pow(3,mod-1>>m+1);for(int i=2;i^1<<m;++i)w[m][i]=1ll*w[m][i-1]*w[m][1]%mod;
	for(int k=m-1;k>=0&&(w[k]=now,now+=1<<k);--k)IMP(1<<k,w[k][i]=w[k+1][i<<1]);
}
inline void DFT(int*f,const int&M){
	const int&n=1<<M;
	for(int len=n>>1,d=M-1;d>=0;--d,len>>=1){
		for(int k=0;k^n;k+=len<<1){
			int*W=w[d],*L=f+(k),*R=f+(k|len),x,y;IMP(len,(x=*L,y=*R)),*L++=Add(x,y),*R++=1ll**W++*Del(x,y)%mod;
		}
	}
}
inline void IDFT(int*f,const int&M){
	const int&n=1<<M;
	for(int len=1,d=0;d<M;++d,len<<=1){
		for(int k=0;k^n;k+=len<<1){
			int*W=w[d],*L=f+(k),*R=f+(k|len),x,y;IMP(len,(x=*L,y=1ll**W++**R%mod)),*L++=Add(x,y),*R++=Del(x,y);
		}
	}
	const int&k=pow(n);IMP(n,f[i]=1ll*f[i]*k%mod);for(int i=1;(i<<1)<n;++i)swap(f[i],f[n-i]);
}
inline void Build(const int&u,const int&L,const int&R){
	static int F[M],G[M];T[u]=new int[R-L+2];
	if(L==R)return T[u][0]=(mod+1-P[L])%mod,T[u][1]=P[L],void();
	const int&mid=L+R>>1,&len=Getlen(R-L+2);Build(u<<1,L,mid);Build(u<<1|1,mid+1,R);
	IMP(mid-L+2,F[i]=T[u<<1][i]);IMP(R-mid+1,G[i]=T[u<<1|1][i]);
	DFT(F,len);DFT(G,len);IMP(1<<len,F[i]=1ll*F[i]*G[i]%mod);IDFT(F,len);
	IMP(R-L+2,T[u][i]=F[i]);IMP(1<<len,F[i]=G[i]=0);delete[]T[u<<1];delete[]T[u<<1|1];
}
inline int read(){
	int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
}
signed main(){
	int X(0),Y(0);n=read();m=read();init(m<<1);F[0]=1;k=1;
	for(int a,x,y,i=1;i<=m;++i)a=read(),x=read(),y=read(),p[a].push_back(1ll*x*pow(y)%mod);
	for(int i=0;i<=n+m;++i){
		IMP(k,G[i>>1]=(G[i>>1]+F[i])%mod);IMP(k,F[i]=0);k=k+1>>1;IMP(k,F[i]=G[i]),G[i]=0;
		if(!p[i].empty()){
			for(int qwq=(p[i].size()),k=0;k^qwq;++k)P[k+1]=p[i][k],X=(X+2ll*P[k+1])%mod;
			Build(1,1,p[i].size());IMP(p[i].size()+1,G[i]=T[1][i]);delete[]T[1];
			const int&len=Getlen(k+=p[i].size());DFT(F,len);DFT(G,len);IMP(1<<len,F[i]=1ll*F[i]*G[i]%mod);
			IDFT(F,len);IMP(1<<len,G[i]=0);
		}
		if(k)IMP(k,i&1&&(Y=(Y+F[i])%mod));
	}
	printf("%d",(X+mod-Y)%mod);
}