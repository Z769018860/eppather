#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
int n,a,b,c,d;
unsigned int seed;
unsigned int randnum()
{
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;	
}
queue<unsigned int>q;
deque<unsigned int>q1;
int vis[4000010],now;
static int p[4000010];
const static unsigned int mod=998244353;
int main()
{
	int t,i;
	cin>>t;
	while(t--)
	{
		unsigned int sum=0,ans=0;
		cin>>n>>seed>>a>>b>>c>>d;
		for(i=1;i<=n;i++)
		{
			if(randnum()%c==0)
			{
				p[i]=-1;
			}
			else
			{
				p[i]=randnum()%b;
			}
		}
		while(!q.empty())
		{
			q.pop();
		}
		while(!q1.empty())
		{
			q1.pop_back();
		}
		memset(vis,0,sizeof(vis));
		b=max(a+1,b);
		if(a!=-1)
		{
			for(i=0;i<=a;i++)
			{
				vis[i]=1;
			}
		}
		now=a+1;	
		for(i=1;i<=n;i++)
		{	
			if(p[i]==-1)
			{
				if(q.empty()||d==1)
				{
					continue;
				}
				int t=q.front();
				vis[t]=1;
				q.pop();
				if(!q1.empty()&&t==q1.front())
				{
					q1.pop_front();
				}
				sum=now;
				if(!q1.empty()) 
				{
					sum=min(sum,q1.front());
				}
			}
			else if(!vis[p[i]])
			{
				vis[p[i]]=1;
				while(vis[now])
				{
					now++;
				}
				sum=now;
				if(!q1.empty())
				{
					sum=min(sum,q1.front());
				}
			}
			else if(vis[p[i]]==1)
			{
				if(d==1)
				{
					continue;
				}
				q.push(p[i]);
				vis[p[i]]=2;
				while(!q1.empty()&&q1.back()>p[i])
				{
					q1.pop_back();
				}
				q1.push_back(p[i]);
				sum=now;
				if(!q1.empty())
				{
					sum=min(sum,q1.front());
				}
			}
			else
			{
				if(q.empty()||d==1)
				{
					continue;
				}
				int t=q.front();
				vis[t]=1;
				q.pop();
				if(!q1.empty()&&t==q1.front())
				{
					q1.pop_front();
				}
				sum=now;
				if(!q1.empty()) 
				{
					sum=min(sum,q1.front());
				}
			}
			ans^=(long long)i*(i+7)%mod*sum%mod;
		}
		cout<<ans<<endl;
	}
	return 0;
 } 