#include<stdio.h>
#include<algorithm>
#define inf 232792561
int a[102][202],ts[102],st[102],l=0;
int p[102][102],q[102][102],w[102][102],t[102][102];
int n,m;long long k;
int A[1048576],B[1048576];
inline int ksm(long long a,long long b){int ans=1;while(b)(b&1)&&(ans=a*ans%inf),a=a*a%inf,b>>=1;return ans;}
inline void gs(int n,int m){
	for(int i=0;i<n;i++){
		int pos=i;
		while(pos<n&&!a[pos][i])pos++;
		if(pos>=n)exit(-1);
		if(pos!=i)
			for(int j=i;j<m;j++)
				a[i][j]^=a[pos][j]^=a[i][j]^=a[pos][j];
		int val=ksm(a[i][i],inf-2);
		for(int j=i;j<m;j++)a[i][j]=1ull*val*a[i][j]%inf;
		for(int j=0;j<n;j++)
			if(i!=j&&a[j][i])
				for(int k=m-1;k>=i;k--)
					a[j][k]=(1ull*(inf-a[j][i])*a[i][k]+a[j][k])%inf;
	}
}
void dfs(int pos){
	if(l==m)return;
	if(pos==m){
		for(int i=0;i<m;i++)p[l][i]=st[i];
		l++;return;
	}bool ff=st[pos]=0;
	for(int i=0;i<pos;i++){
		for(int j=i;j<pos;j++){
			if(t[i][j]==pos){
				if(!ff)st[pos]=1ll*st[i]*st[j]%inf,ff=1;
				else if(st[pos]!=1ll*st[i]*st[j]%inf)return;
			}
		}
	}if(ff){
		for(int j=0;j<=pos;j++){
			if(t[j][pos]<=pos&&1ll*st[j]*st[pos]%inf!=st[t[j][pos]])return;
		}dfs(pos+1);
	}
	else{
		for(int i=0;i<=ts[pos];i++){
			st[pos]=w[ts[pos]][i];
			bool f=1;
			for(int j=0;j<=pos;j++){
				if(t[j][pos]<=pos&&1ll*st[j]*st[pos]%inf!=st[t[j][pos]])f=0;
			}if(f)dfs(pos+1);
		}
	}
}
void ntt(int a[],int b[],int n,bool typ){
	int dt=n/m,p1,p2;
	if(dt!=1)for(int i=0;i<n;i+=dt)ntt(a+i,b,dt,typ);
	for(int i=0;i<n;i++)b[i]=0;
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			for(int k=0;k<dt;k++){
				int p1=i*dt+k,p2=j*dt+k;
				b[p1]=(1ll*a[p2]*(typ?q[i][j]:p[i][j])+b[p1])%inf;
			}
	for(int i=0;i<n;i++)a[i]=b[i];
}
int main(){
	scanf("%d%d%lld",&n,&m,&k);
	n=ksm(m,n);
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			scanf("%d",&t[i][j]);
	for(int i=1;i<=m;i++){
		w[i][0]=1;
		if(i!=1)w[i][1]=ksm(71,(inf-1)/i);
		for(int j=2;j<i;j++)
			w[i][j]=1ll*w[i][j-1]*w[i][1]%inf;
	}for(int i=0;i<m;i++){
		int P=i;ts[i]=0;
		while(1){
			ts[i]++;
			P=t[P][i];
			if(P==i)break;
		}
	}dfs(0);
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			a[i][j]=p[i][j];
	for(int i=0;i<m;i++)
		a[i][i+m]=1;
	gs(m,m+m);
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			q[i][j]=a[i][j+m];
	for(int i=0;i<n;i++)scanf("%d",&A[i]);
	ntt(A,B,n,0);
	for(int i=0;i<n;i++)A[i]=ksm(A[i],k+1);
	ntt(A,B,n,1);
	for(int i=0;i<n;i++)printf("%d\n",A[i]);
}