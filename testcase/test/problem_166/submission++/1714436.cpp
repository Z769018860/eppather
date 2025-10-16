#include<bits/stdc++.h>
using namespace std;
#define rd(i,n) for(int i=0;i<n;i++)
#define rp(i,n) for(int i=1;i<=n;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=b;i>=a;i--)
#define st string
#define vt vector
#define pb push_back

#define ll long long
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
namespace poly{
	int rvs[4000005],P=998244353;
	inline int to_binary(int x){
		int y=__lg(x);
		return 1<<(y+1);
	}
	inline int fpow(int a,int b,int P){
		if(!b)return 1;
		int res=fpow(a,b>>1,P);
		if(b&1)return 1ll*res*res%P*a%P;
		return 1ll*res*res%P;
	}
	inline void change(vt<int>&res){
		for(int i=0;i<(int)res.size();i++){
			rvs[i]=rvs[i>>1]>>1;
			if(i&1)rvs[i]|=res.size()>>1;
		}
		for(int i=0;i<(int)res.size();i++)if(i<rvs[i]){
			swap(res[i],res[rvs[i]]);
		}
	}
	inline void ntt(vt<int>&res,int rev){
		change(res);
		for(int p=2;p<=(int)res.size();p<<=1){
			int syf=fpow(3,(998244352)/p,P);
			for(int i=0;i<(int)res.size();i+=p){
				int cyr=1;
				for(int j=i;j<i+p/2;j++){
					int g=res[j],t=1ll*cyr*res[j+p/2]%P;
					res[j]=(g+t)%P,res[j+p/2]=(g-t+P)%P;
					cyr=1ll*cyr*syf%P;
				}
			}
		}if(rev==-1){
			reverse(res.begin()+1,res.end());
			int inv=fpow((int)res.size(),P-2,P);
			for(int i=0;i<(int)res.size();i++)res[i]=1ll*res[i]*inv%P;
		}
	}
	vt<int>convolution(vt<int>&a,vt<int>&b){
		int rsize=to_binary(a.size()+b.size()+1);
		while((int)a.size()<rsize)a.pb(0);
		while((int)b.size()<rsize)b.pb(0);
		ntt(a,1);ntt(b,1);
		vt<int>res;
		rd(i,rsize)res.pb(1ll*a[i]*b[i]%P);
		ntt(res,-1);
		return res;
	}
}
const int P=998244353;
vt<int>va,vb,vc;
int x,n,m,f[160005],fac[160005],bi[160005],ifac[160005];
const int N=160000;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	fac[0]=ifac[0]=1;
	rp(i,N)fac[i]=1ll*fac[i-1]*i%P;
	rp(i,N)ifac[i]=poly::fpow(fac[i],P-2,P);
	rep(i,0,N)bi[i]=(i&1)?(998244352):(1);
	cin>>n>>m;
	rep(i,0,n)cin>>f[i];
	rep(i,0,n)va.pb(1ll*f[i]*bi[n-i]%P*ifac[i]%P*ifac[n-i]%P);
	rep(i,0,2*n)vb.pb(poly::fpow(m-n+i,P-2,P));
	vc=poly::convolution(va,vb);
	ll coe=1;
	rep(i,0,n)coe=1ll*coe*(m-i)%P;
	rep(k,0,n){
		cout<<vc[n+k]*coe%P<<" ";
		coe=coe*poly::fpow(m+k-n,P-2,P)%P;
		coe=coe*(m+k+1)%P;
	}cout<<endl;
	return 0;
}
