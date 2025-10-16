#include<bits/stdc++.h>
using namespace std;
const int N=1<<18,P=998244353;
typedef vector<int> poly;
int n,m,w[N],A[N],B[N],lim,ans;
int ksm(int x,int y){
	int res=1;
	for(;y;y>>=1,x=1ll*x*x%P)if(y&1)res=1ll*res*x%P;
	return res;
}
void cle(int *A){
	for(int i=0;i<lim;++i)A[i]=0;
}
inline int md(int x){
	return x>=P?x-P:x;
}
void init(){
	for(int mid=1,j,wn;mid<N;mid<<=1)
		for(w[j=mid]=1,wn=ksm(3,(P-1)/(mid<<1)),++j;j<mid<<1;++j)w[j]=1ll*w[j-1]*wn%P;
}
void up(int n){
	lim=1;
	while(lim<=n)lim<<=1;
}
void DFT(int *A){
	for(int mid=lim>>1,R,j,k,*a,*b,*W,Y;mid;mid>>=1)
		for(j=0,R=mid<<1;j<lim;j+=R)
			for(k=0,a=A+j,b=a+mid,W=w+mid;k<mid;++k,++a,++b,++W)
				*b=1ll**W*(*a+P-(Y=*b))%P,*a=md(*a+Y);
}
void IDFT(int *A){
	for(int mid=1,R,j,k,*a,*b,*W,Y;mid<lim;mid<<=1)
		for(j=0,R=mid<<1;j<lim;j+=R)
			for(k=0,a=A+j,b=a+mid,W=w+mid;k<mid;++k,++a,++b,++W)
				Y=1ll**b**W%P,*b=md(*a+P-Y),*a=md(*a+Y);
	reverse(A+1,A+lim);
	for(int in=ksm(lim,P-2),i=0;i<lim;++i)A[i]=1ll*A[i]*in%P;
}
poly solve(vector<poly>&  p,int l,int r){
	if(l==r)return p[l];
	int mid=l+r>>1;
	poly pl=solve(p,l,mid),pr=solve(p,mid+1,r),pt;
	up(pl.size()+pr.size()-2);
	cle(A),cle(B);
	for(int i=0;i<pl.size();++i)A[i]=pl[i];
	for(int i=0;i<pr.size();++i)B[i]=pr[i];
	DFT(A),DFT(B);
	for(int i=0;i<lim;++i)A[i]=1ll*A[i]*B[i]%P;
	IDFT(A);
	for(int i=0;i<pl.size()+pr.size()-1;++i)pt.push_back(A[i]);
	return pt;
}
vector<poly>e[N];
int main(){
	init();
	scanf("%d%d",&n,&m);
	for(int i=1,a,x,y;i<=m;++i){
		scanf("%d%d%d",&a,&x,&y);
		x=1ll*x*ksm(y,P-2)%P;
		poly tmp;
		tmp.push_back(md(P+1-x)),tmp.push_back(x);
		e[a].push_back(tmp);
	}
	for(int i=0;i<=n+50;++i)if(e[i].size()){
		poly p=solve(e[i],0,e[i].size()-1),q;
		for(int j=0;j<p.size();++j){
			ans=(1ll*j*p[j]+ans)%P;
			if(j&1)q.back()=md(q.back()+p[j]);
			else q.push_back(p[j]);
		}
		if(q.size()>1)e[i+1].push_back(q);
	}
	printf("%d\n",ans);
	return 0;
}