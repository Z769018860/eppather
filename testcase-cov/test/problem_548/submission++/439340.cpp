#include <bits/stdc++.h>

int bufin;char chr;
inline int read(){
	while (!isdigit(chr=getchar()));bufin=chr-'0';
	while (isdigit(chr=getchar()))(bufin*=10)+=chr-'0';
	return bufin;
}

inline int readmod(int MOD){
	while (!isdigit(chr=getchar()));bufin=(chr-'0')%MOD;
	while (isdigit(chr=getchar()))
		bufin=(bufin*10LL+chr-'0')%MOD;
	return bufin;
}

inline int Pow(int x,int P,int MOD){
	int ans=1;
	for (;P;P>>=1,x=1LL*x*x%MOD)
		if (P&1)
			ans=1LL*ans*x%MOD;
	return ans;
}

const int G=71;
const int MOD=232792561;
const int maxn=5e5+10;

inline int add(int a,int b){return (a+=b)>=MOD?(a-MOD):a;}
inline int minus(int a,int b){return (a-=b)<0?(a+MOD):a;}

int N,M,L,K;
int a[23][23];
int b[23][23];
int w[23][23];
int trans[23][23];
int v[maxn];
int tmp[maxn];

bool Gauss(){
	int c[23][23];
	memcpy(c,a,sizeof(c));
	for (int i=0;i<M;i++)
		b[i][i]=1;
	for (int i=0,p;i<M;i++){
		bool ok=false;
		for (int j=i;j<M;j++)
			if (a[p=j][i]){
				ok=true;
				break;
			}
		if (ok==false)
			abort();
		if (p!=i)
			std::swap(a[p],a[i]),std::swap(b[p],b[i]);
		for (int j=0,inv=Pow(a[i][i],MOD-2,MOD);j<M;j++)
			if (i!=j){
				int rate=1LL*a[j][i]*inv%MOD;
				for (int k=0;k<M;k++){
					a[j][k]=minus(a[j][k],1LL*rate*a[i][k]%MOD);
					b[j][k]=minus(b[j][k],1LL*rate*b[i][k]%MOD);
				}
			}
	}
	for (int i=0,inv;i<M;i++){
		inv=Pow(a[i][i],MOD-2,MOD);
		for (int j=0;j<M;j++)
			b[i][j]=1LL*b[i][j]*inv%MOD;
	}
	memcpy(a,c,sizeof(a));
	return true;
}

int line;
int ord[23];
bool dfs(int cur){
	if (cur==M){
		bool ALL0=true;
		for (int i=0;i<M;i++)
			ALL0&=a[line][i]==0;
		if (ALL0)
			return false;
		for (int i=0;i<line;i++)
			if (memcmp(a[i],a[line],sizeof(a[i]))==0)
				return false;
		return true;
	}
	for (int k=0,ok;k<=ord[cur];k++){
		ok=true,a[line][cur]=w[ord[cur]][k];
		for (int i=0,v;i<=cur&&ok;i++)
			for (int j=0;j<=cur&&ok;j++){
				v=trans[i][j];
				if (v<=cur&&1LL*a[line][i]*a[line][j]%MOD!=a[line][v])
					ok=false;
			}
		if (ok&&dfs(cur+1))
			return true;
	}
	return false;
}

void Trans(int* f){
	static int tmp[23];
	memset(tmp,0,sizeof(tmp));
	for (int i=0;i<M;i++)
		for (int j=0;j<M;j++)
			tmp[i]=add(tmp[i],1LL*f[j]*a[i][j]%MOD);
	for (int i=0;i<M;i++)
		f[i]=tmp[i];
}

void ITrans(int* f){
	static int tmp[23];
	memset(tmp,0,sizeof(tmp));
	for (int i=0;i<M;i++)
		for (int j=0;j<M;j++)
			tmp[i]=add(tmp[i],1LL*f[j]*b[i][j]%MOD);
	for (int i=0;i<M;i++)
		f[i]=tmp[i];
}

int main (){
#ifdef LOCAL
	freopen("input","r",stdin);
#endif
	N=read(),M=read(),K=(readmod(MOD-1)+1)%(MOD-1);
	L=1;
	for (int i=1;i<=N;i++)
		L*=M;
	for (int i=0;i<M;i++)
		for (int j=0;j<M;j++)
			trans[i][j]=read();
	for (int i=0,cur;i<M;i++){
		cur=i;
		do {
			++ord[i];
			cur=trans[cur][i];
		}while (cur!=i);
	}
	for (int i=1,wn;i<=22;i++){
		w[i][0]=1;
		wn=Pow(G,(MOD-1)/i,MOD);
		for (int j=1;j<i;j++)
			w[i][j]=1LL*w[i][j-1]*wn%MOD;
	}
	for (line=0;line<M;line++)
		assert(dfs(0));
	Gauss();
	for (int i=0;i<L;i++)
		v[i]=read();
	for (int i=1,s=M;i<L;i=s,s*=M)
		for (int j=0;j<L;j+=s)
			for (int k=0;k<i;k++){
				for (int h=0,p=j+k;h<M;h++,p+=i)
					tmp[h]=v[p];
				Trans(tmp);
				for (int h=0,p=j+k;h<M;h++,p+=i)
					v[p]=tmp[h];
			}
	for (int i=0;i<L;i++)
		v[i]=Pow(v[i],K,MOD);
	for (int i=1,s=M;i<L;i=s,s*=M)
		for (int j=0;j<L;j+=s)
			for (int k=0;k<i;k++){
				for (int h=0,p=j+k;h<M;h++,p+=i)
					tmp[h]=v[p];
				ITrans(tmp);
				for (int h=0,p=j+k;h<M;h++,p+=i)
					v[p]=tmp[h];
			}
	for (int i=0;i<L;i++)
		printf("%d\n",v[i]);
	return 0;
}

