# include <bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mod=1e9+7;
int k1,k2,C[11][11];
void add(int &x,const auto &y){x=(x+y)%mod;}
struct Node
{
	int x,y,s[11][11];
	Node():x(0),y(0){memset(s,0,sizeof(s));}
	Node operator*(const Node &t)const
	{
		Node ans;
		ans.x=(x+t.x)%mod;
		ans.y=(y+t.y)%mod;
		static int p1[11],p2[11];
		p1[0]=p2[0]=1;
		for(int i=1;i<=k1;i++) p1[i]=(ll)p1[i-1]*x%mod;
		for(int i=1;i<=k2;i++) p2[i]=(ll)p2[i-1]*y%mod;
		for(int i=0;i<=k1;i++) copy(s[i],s[i]+k2+1,ans.s[i]);
		for(int i=0;i<=k1;i++)
			for(int p=0;i+p<=k1;p++)
				for(int j=0;j<=k2;j++)
					for(int q=0;j+q<=k2;q++)
						add(ans.s[i+p][j+q],(ll)C[i+p][i]*C[j+q][j]%mod*p1[p]%mod*p2[q]%mod*t.s[i][j]);
		return ans;
	}
}O,_1,M,D[100];
Node power(Node a,int b)
{
	Node ans;
	for(;b;b>>=1,a=a*a)
		if(b&1) ans=ans*a;
	return ans;
}
Node merge(const Node &L,const Node &R){return L.x && R.x?L*M*R:L*R;}
Node merge_pw(Node a,int b)
{
	Node ans;
	for(;b;b>>=1,a=merge(a,a))
		if(b&1) ans=merge(ans,a);
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(nullptr);
	O.s[0][0]=1;D[0].x=D[1].y=1;
	for(int i=0;i<=10;i++) _1.s[0][i]=(i&1?mod-1:1);
	for(int i=0;i<=10;i++) C[i][0]=1;
	for(int i=1;i<=10;i++)
		for(int j=1;j<=i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	int T,N,A,B,C;
	cin>>T;
	while(T--)
	{
		static int a[100],p[100],q[100];
		cin>>N>>A>>B>>C>>k1>>k2;
		p[0]=q[1]=0;p[1]=q[0]=1;
		int n=1,P=A,Q=C;
		Node ans=power(D[1],B/C)*O;
		while(Q)
		{
			a[++n]=P/Q;
			p[n]=a[n]*p[n-1]+p[n-2];
			q[n]=a[n]*q[n-1]+q[n-2];
			M=(n&1?_1:O);D[n]=merge(D[n-2],merge_pw(D[n-1],a[n]));
			swap(P-=a[n]*Q,Q);
		}
		ll x=0,y=B/C;
		M=_1;
		for(int i=0;i+2<=n;i++)
		{
			if((ll)A*q[i]>=(ll)C*p[i]) continue;
			while(C*(y+p[i+2])<=A*(x+q[i+2])+B)
			{
				ll t=max((C*(y+p[i]-p[i+1])-A*(x+q[i]-q[i+1])-B-1)/((ll)A*q[i+1]-(ll)C*p[i+1]),0ll),dx=q[i]+t*q[i+1],dy=p[i]+t*p[i+1];
				if(x+dx>N || A*dx>=C*dy) break;
				ll c=min((N-x)/dx,(A*x+B-C*y)/(C*dy-A*dx));
				x+=c*dx;y+=c*dy;
				ans=ans*power(merge(D[i],merge_pw(D[i+1],t))*O,c);
			}
		}
		M=O;
		for(int i=n;i>=0;i--)
		{
			if((ll)A*q[i]<(ll)C*p[i]) continue;
			while(x+q[i]<=N)
			{
				int t,dx,dy;
				if(i==n) dx=q[i],dy=p[i];
				else
				{
					t=(N-x-q[i])/q[i+1];
					dx=q[i]+t*q[i+1];dy=p[i]+t*p[i+1];
				}
				int c=(N-x)/dx;
				x+=c*dx;y+=(ll)c*dy;
				ans=ans*power((i==n?D[i]:merge(D[i],merge_pw(D[i+1],t)))*O,c);
			}
		}
		cout<<ans.s[k1][k2]<<"\n";
	}
	return 0;
}