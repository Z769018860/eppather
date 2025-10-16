#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q;
int k[400005];
int s[400005];
int snum,fnum;
unordered_map<int,int>f,mp,mp1,b,g,ans;
const int MOd=998244353;
int cnt;
int prime[24];
int p,x;
int fb[400005];
int ksm(int x,int y){
	int sum=1;

	while(y){
		if(y&1)sum*=x;
		sum%=MOd;
		x*=x;
		x%=MOd;
		y>>=1;
	}
	return sum;
}
void dfs(int t,int val){
	if(t==cnt+1){
		s[++snum]=val;
		mp1[val]=1;
		return ;
	}
	while(val<=n){
		dfs(t+1,val);
		val*=prime[t];
	}
	return ;
}























signed main(){
	ios::sync_with_stdio(0);
	
	
	cin>>n>>m>>q;
	for(int i=1;i<=m;++i){
		cin>>p>>x;
		if(!b[p]){

			int tp=p;
			for(int i=1;i<=cnt;++i){
				while(tp%prime[i]==0)tp/=prime[i];
			}
			for(int i=2;i*i<=n and tp!=1;++i){
				if(tp%i==0){
					prime[++cnt]=i;
					while(tp%i==0)tp/=i;
				}
			}
			if(tp!=1)prime[++cnt]=tp;
		}
		b[p]+=x;
		b[p]%=MOd;
	}
	for(int i=1;i<=q;++i){
		cin>>k[i];

		int tp=k[i];
		for(int i=1;i<=cnt;++i){
			while(tp%prime[i]==0)tp/=prime[i];
		}
		for(int i=2;i*i<=n and tp!=1;++i){
			if(tp%i==0){
				prime[++cnt]=i;
				while(tp%i==0)tp/=i;
			}
		}
		if(tp!=1)prime[++cnt]=tp;
	}
	dfs(1,1);

	for(auto tp=b.begin();tp!=b.end();++tp){
		tp->second=tp->second*ksm(tp->first,MOd-2)%MOd;

	}
	sort(s+1,s+snum+1);

	for(int i=1;i*i<=n;++i){
		fb[++fnum]=i;
		if(n/i!=i){
			fb[++fnum]=n/i;
		}
	}
	sort(fb+1,fb+fnum+1);
	for(int i=1;i<=fnum;++i){
		int tp=fb[i];
		f[tp]=tp*(tp+1)%MOd*(2*tp+1)%MOd*ksm(6,MOd-2)%MOd;
	}
	for(int i=1;i<=cnt;++i){
		for(int j=fnum;j>=1;--j){
			int tp=fb[j];
			f[tp]=((f[tp]-f[tp/prime[i]]*prime[i]%MOd*prime[i]%MOd)%MOd+MOd)%MOd;
		}
	}





	for(int i=1;i<=snum;++i){
		int tp=s[i];
		g[tp]=b[tp];
	}


	for(int i=1;i<=cnt;++i){
		for(int j=1;j<=snum;++j){
			int tp=s[j];
			if(tp%prime[i]==0)g[tp]=(g[tp]+g[tp/prime[i]])%MOd;
		}
	}





	for(int i=1;i<=snum;++i){
		int tp=s[i];
		ans[tp]=tp*tp%MOd*(f[n/tp])%MOd*g[tp]%MOd;

	}
	for (int i=1;i<=cnt;++i)
        for (int j=snum;j>=1;--j)
            if (1ll*s[j]*prime[i]<=n)
				ans[s[j]]=(ans[s[j]]+ans[s[j]*prime[i]])%MOd;






	for(int i=1;i<=q;++i){
		cout<<ans[k[i]]*ksm(k[i],MOd-2)%MOd<<'\n';
	}












	return 0;
}