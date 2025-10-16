#include <stdio.h>
typedef long long _64;
_64 prefix[1000001];
_64 n;

_64 bit2(_64 x)
{
	return x&-x;
}

void modify(int place,_64 variant)
{
	for(int i=place;i<=n;i+=bit2(i))
	prefix[i]+=variant;
}

_64 find(int place)
{
	_64 ans=0;
	while(place)
	{
		ans+=prefix[place];
		place-=bit2(place);
	}
	return ans;
}

void change(int left,int right,_64 variant)
{
	modify(left,variant);
	modify(right+1,-variant);
}

int main()
{
	_64 m,p;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%lld",&p),
	change(i,i,p);
	while(m--)
	{
		_64 idea,a,b,c;
		scanf("%lld",&idea);
		if(idea==1ll)
		{
			scanf("%lld%lld%lld",&a,&b,&c);
			change(a,b,c);
		}
		if(idea==2ll)
		{
			scanf("%lld",&a);
			printf("%lld\n",find(a));
		}
	}
}