#include <iostream>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const int maxn=1e5+5;
struct P{
	int v,p,rk;
}a[maxn];
int n,cnt,len,sum[maxn];
ll ans;
char s[20];
bool cmp(P a,P b){return a.v<b.v;}
bool cmp2(P a,P b){return a.p<b.p;}
int lowb(int x){return x&(-x);}
void upd(int x)
{
	while(x<=n) sum[x]++,x+=lowb(x);
}
int qr(int r)
{
	int re=0;
	while(r) re+=sum[r],r-=lowb(r);
	return re;
}
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>(s+1);
		if(s[1]=='X') cnt++;
		else
		{
			len=strlen(s+1);
			int st=1;if(s[1]=='-') st=2;
			for (int j=st;j<=len;j++) a[i].v=a[i].v*10+(s[j]^48);
			if(st==2) a[i].v=-a[i].v;
			a[i].p=i;
		}
	}
	if(n==1){cout<<"L"<<endl;return 0;}
	if(cnt)
	{
		if(cnt%2) cout<<"W"<<endl;
		else cout<<"L"<<endl;
		return 0;
	}
	sort(a+1,a+n+1,cmp);
	for (int i=1;i<=n;i++) a[i].rk=i;
	sort(a+1,a+n+1,cmp2);
	for (int i=n;i;i--) ans+=qr(a[i].rk-1),upd(a[i].rk);
	if(ans%2) cout<<"W"<<endl;
	else cout<<"L"<<endl;
	return 0;
}