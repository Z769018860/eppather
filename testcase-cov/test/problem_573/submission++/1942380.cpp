#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l);i<=(r);++i)
#define ReFor(i,r,l) for(int i=(r);i>=(l);--i)
const int N=1000010;
const int mod=998244353;
typedef long long ll;
using namespace std;
int n,m,Type;
ll a[N];
template<typename T1,typename T2>
void Add(T1 &a,T2 b){a+=b;if(a>=mod)a-=mod;return;}
struct Matrix{ll a[2][2];}prod[N],inv_prod[N],I;
Matrix operator * (const Matrix &a,const Matrix &b)
{
	Matrix res;For(i,0,1){For(j,0,1)res.a[i][j]=0;}
	For(k,0,1)
	{
		For(i,0,1)
		{
			For(j,0,1)
			{
				ll delta=a.a[i][k];(delta*=b.a[k][j])%=mod;
				Add(res.a[i][j],delta);
			}
		}
	}
	return res;
}
int main()
{
	I.a[0][0]=1;I.a[0][1]=0;
	I.a[1][0]=0;I.a[1][1]=1;
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m>>Type;For(i,1,n)cin>>a[i];
	For(i,1,n)
	{
		prod[i].a[0][0]=a[i];prod[i].a[0][1]=1;
		prod[i].a[1][0]=1;prod[i].a[1][1]=0;
		if(i>=2)prod[i]=(prod[i-1]*prod[i]);
		inv_prod[i].a[0][0]=0;inv_prod[i].a[0][1]=1;
		inv_prod[i].a[1][0]=1;inv_prod[i].a[1][1]=(mod-a[i]);
		if(i>=2)inv_prod[i]=(inv_prod[i]*inv_prod[i-1]);
	}
	int Ansx=0,Ansy=0;
	while(m--)
	{
		int opt;
		cin>>opt;
		if(opt==1)
		{
			int x;cin>>x;
			if(Type==1){int _=(Ansx^Ansy);x^=_;}
			++n;a[n]=x;
			prod[n].a[0][0]=x;prod[n].a[0][1]=1;
			prod[n].a[1][0]=1;prod[n].a[1][1]=0;
			if(n>=2)prod[n]=(prod[n-1]*prod[n]);
			inv_prod[n].a[0][0]=0;inv_prod[n].a[0][1]=1;
			inv_prod[n].a[1][0]=1;inv_prod[n].a[1][1]=(mod-x);
			if(n>=2)inv_prod[n]=(inv_prod[n]*inv_prod[n-1]);
		}
		if(opt==2)
		{
			int l,r;
			cin>>l>>r;
			if(Type==1){int _=(Ansx^Ansy);l^=_;r^=_;}
			Matrix res=I;
			if(r>=2)res=(res*prod[r-1]);
			if(l>=2)res=(inv_prod[l-1]*res);
			{
				ll new_Ansx=(((1ll*res.a[0][0]*a[r])+res.a[0][1])%mod);
				ll new_Ansy=(((1ll*res.a[1][0]*a[r])+res.a[1][1])%mod);
				cout<<new_Ansx<<" "<<new_Ansy<<"\n";
				Ansx=new_Ansx;Ansy=new_Ansy;
			};
		}
	}
	return 0;
}