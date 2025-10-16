#include <bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,a[N],b[N],qu,tot,x,ans,y;
set<int> s[N];
struct ques{
	int x,y;
}q[N];
int meand[N];
signed main()
{
	
	
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>qu;
	for(int i=1;i<=n;i++)
		cin>>a[i],b[i]=a[i];
	tot=n;
	for(int i=1;i<=qu;i++)
		cin>>q[i].x>>q[i].y,b[++tot]=q[i].x,b[++tot]=q[i].y;
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	ans=2147483647;
	for(int i=1;i<=n;i++)
	{
		a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
		if(s[a[i]].size())
		{
			set<int>::iterator it=s[a[i]].upper_bound(i);
			if(it!=s[a[i]].end())ans=min(ans,(*it)-i);
			if(it!=s[a[i]].begin())ans=min(ans,i-(*--it));
		}
		s[a[i]].insert(i);
	}
	
	for (int i=1;i<=tot;i++) meand[i]=i;
	for(int i=1;i<=qu;i++)
	{
		int byd=0;
		x=lower_bound(b+1,b+tot+1,q[i].x)-b;
		y=lower_bound(b+1,b+tot+1,q[i].y)-b;
		int xx=x,yy=y;
		x=meand[x],y=meand[y];
		if(x==y)
		{
			cout<<ans<<"\n";
			continue;
		}
		if(s[x].size()>s[y].size())
		{
			swap(meand[xx],meand[yy]);
			swap(x,y);
		}
		for(auto i:s[x])
		{
			if(s[y].size())
			{
				set<int>::iterator it=s[y].upper_bound(i);
				if(it!=s[y].end())ans=min(ans,(*it)-i);
				if(it!=s[y].begin())ans=min(ans,i-(*--it));
			}
			s[y].insert(i);
		}
		s[x].clear();
		cout<<ans<<"\n";
	}
}