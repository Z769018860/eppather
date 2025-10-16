

#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e4+10;
int const M=2500+10;
int const mod=998244353;
int n,p,top,f[2*M][M],ans[M],x[N],y[N],z[N];
inline int qpow(int a,int b){int r=1;while (b){if (b&1) r=1ll*r*a%mod;a=1ll*a*a%mod,b>>=1;}return r;}
inline vector<int> BM(vector<int>vec){
	vector<int>res,las;
	res.push_back(1),las.push_back(1);
	int lasv=1,lasp=-1;
	for (int i=0;i<(int)vec.size();++i){
		int val=0;
        for (int j=0;j<(int)res.size();++j) val=(val+res[j]*vec[i-j]%mod)%mod;
		if (!val) continue;
		vector<int>tmp=res;
		int g=(mod-val)*qpow(lasv,mod-2)%mod;
		for (int j=0;j<(int)las.size();++j){
			int k=i+j-lasp;
			if (k>=(int)res.size()) res.resize(k+1);
			res[k]=(res[k]+g*las[j]%mod)%mod;
		}
		las=tmp,lasv=val,lasp=i;
	}
    return res;
}
inline vector<int> BM(){
    mt19937 rng(time(0));
    while (1){
        vector<int>rnd(n+1),tmp;
        for (int i=1;i<=n;++i) rnd[i]=rng();
        for (int i=1;i<=2*n;++i){
            int val=0;
            for (int j=1;j<=n;++j) val+=rnd[j]*f[i][j]%mod,val%=mod;
            tmp.push_back(val);
        }
        vector<int>res=BM(tmp);
        int m=res.size(),tag=0;
        for (int i=1;i<=n;++i){
            int val=0;
            for (int j=0;j<m;++j) val+=f[2*n-j][i]*res[j]%mod,val%=mod;
            if (val){tag=1;break;}
        }
        if (!tag) return res;
    }
}
void solve(){
    cin>>n;
    for (int i=1;i<=n;++i){
        for (int j=1;j<=n;++j){
            int val;cin>>val;
            if (val) x[++top]=i,y[top]=j,z[top]=val;
        }
        cin>>f[0][i];
    }
    for (int i=1;i<=2*n;++i)
        for (int j=1;j<=top;++j)
            f[i][x[j]]+=f[i-1][y[j]]*z[j]%mod,f[i][x[j]]%=mod;
    vector<int>r=BM();int m=r.size();
    int inv=qpow(mod-r[m-1],mod-2);
    for (int i=1;i<=n;++i){
        for (int j=0;j<m-1;++j)
            ans[i]+=r[m-2-j]*f[j][i]%mod,ans[i]%=mod;
        ans[i]*=inv,ans[i]%=mod,cout<<ans[i]<<' ';
    }
    cout<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t=1;
    
    while (t--) solve();
    return 0;
}