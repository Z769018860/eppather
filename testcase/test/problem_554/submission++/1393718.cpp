#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int Mxdt=100000,mod=998244353,INF=1e9;
char gc(){
	return getchar();static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
int read(){
	int a=0;bool opt=0;char c=gc();
	while(c<'0'||c>'9')opt|=c=='-',c=gc();
	while(c>='0'&&c<='9')a=(a<<3)+(a<<1)+(c^48),c=gc();
	return opt?-a:a;
}
int n,p[300005],s1[300005],top1,s2[300005],top2,L[300005],R[300005],ls[300005],Ls[300005],q,l,r;
vector<int>v[300005],A[300005],D[300005];
void add(int x,int y){v[x].push_back(y);v[y].push_back(x);}
int rd[300005],opt[300005],cnt;
void add(int x){
	for(int y:v[x]){
		if(l<=y&&y<=r){
			++rd[x];++rd[y];
			if(opt[y]){
				if(rd[y]&1)++cnt;else --cnt;
			}
		}
	}
	for(int y:A[x]){
		if(l<=L[y]&&R[y]<=r){
			opt[y]=1;
			if(rd[y]&1)++cnt;
		}
	}
}
void del(int x){
	for(int y:v[x]){
		if(l<=y&&y<=r){
			--rd[x];--rd[y];
			if(opt[y]){
				if(rd[y]&1)++cnt;else --cnt;
			}
		}
	}
	for(int y:D[x]){
		if(opt[y])
		if(l>=L[y]||R[y]>r){
			opt[y]=0;
			if(rd[y]&1)--cnt;
		}
	}
}
long long sum2[300005],sum3[300005];
int cal1(int l,int r){return r-l+1;}
long long cal2(int l,int r){
	long long ans=0;
	int L=l,R=r;
	while(L<=R){
		int mid=L+R>>1;
		if(Ls[mid]>=l)R=mid-1;
		else L=mid+1;
	}
	return 1ll*(l+r)*(r-l+1)/2-(sum2[r]-sum2[R])-1ll*(l-1)*(R-l+1);
}
long long cal3(int l,int r){
	long long ans=0;
	int L=l,R=r;
	while(L<=R){
		int mid=L+R>>1;
		if(ls[mid]>=l)R=mid-1;
		else L=mid+1;
	}
	return 1ll*(l+r)*(r-l+1)/2-(sum3[r]-sum3[R])-1ll*(l-1)*(R-l+1);
}
long long cal4(int l,int r){
	return 1ll*(r-l+1)*(r-l+2)/2;
}
int main(){



	n=read();
	for(int i=1;i<=n;++i)p[i]=read();
	for(int i=1;i<=n;++i){
		while(top1&&p[s1[top1]]<p[i])--top1;
		while(top2&&p[s2[top2]]>p[i])--top2;
		if(top1)add(i,s1[top1]);if(top2)add(i,s2[top2]);
		L[i]=min(s1[top1],s2[top2]);s1[++top1]=i;s2[++top2]=i;
	}
	top1=top2=0;s1[top1]=s2[top2]=n+1;
	for(int i=n;i;--i){
		while(top1&&p[s1[top1]]<p[i])--top1;
		while(top2&&p[s2[top2]]>p[i])--top2;
		if(top1)add(i,s1[top1]);if(top2)add(i,s2[top2]);
		R[i]=max(s1[top1],s2[top2]);s1[++top1]=i;s2[++top2]=i;
	}
	for(int i=1;i<=n;++i){
		D[L[i]].push_back(i);A[R[i]].push_back(i);
	}
	for(int i=1;i<=n;++i){
		if(v[i].size()){
			sort(v[i].begin(),v[i].end());
			v[i].resize(unique(v[i].begin(),v[i].end())-v[i].begin());
		}
	}
	int up=0,down=0;
	for(int i=1;i<=n;++i){
		if(p[i]>p[i-1])Ls[i]=i-up,++up,down=1;
		else Ls[i]=i-down,++down,up=1;
	}
	for(l=1,r=1;r<=n;++r){
		add(r);while(cnt)del(l),++l;ls[r]=l;
	}
	for(int i=1;i<=n;++i){
		sum2[i]=sum2[i-1]+Ls[i]-1;sum3[i]=sum3[i-1]+ls[i]-1;
	}
	if(n==1)puts("1");
	else if(Ls[n]==1)puts("2");
	else if(ls[n]==1)puts("3");
	else puts("4");
	q=read();
	for(int i=1;i<=q;++i){
		l=read();r=read();
		if(r-l+1==1)cout<<"1 "<<cal1(l,r)<<"\n";
		else if(Ls[r]<=l)cout<<"2 "<<cal2(l,r)-cal1(l,r)<<"\n";
		else if(ls[r]<=l)cout<<"3 "<<cal3(l,r)-cal2(l,r)<<"\n";
		else cout<<"4 "<<cal4(l,r)-cal3(l,r)<<"\n";
	}
	return 0;
}