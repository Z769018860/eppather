#include<cstring>
#include<iostream>
int rk[1000001],sa[1000001];
int SA(char*s)
{
	int n=std::strlen(s);
	static int cnt[1000001],id[1000001];
	for(int i=0;i<n;i++)
		cnt[s[i]+1]++;
	for(int i=1;i<128;i++)
		cnt[i]+=cnt[i-1];
	for(int i=0;i<n;i++)
		sa[cnt[rk[i]=s[i]]++]=i;
	for(int w=1,m=128,p=0;p<n&&w<=n;w<<=1,m=p)
	{
		p=0;
		for(int i=n-1;i>=n-w;i--)
			id[p++]=i;
		for(int i=0;i<n;i++)
			if(sa[i]>=w)
				id[p++]=sa[i]-w;
		for(int i=0;i<m;i++)
			cnt[i]=0;
		for(int i=0;i<n;i++)
			cnt[rk[id[i]]+1]++;
		for(int i=1;i<m;i++)
			cnt[i]+=cnt[i-1];
		for(int i=0;i<n;i++)
			sa[cnt[rk[id[i]]]++]=id[i];
		for(int i=0;i<n;i++)
			id[i]=rk[i];
		rk[sa[0]]=0,p=1;
		for(int i=1;i<n;i++)
			if(id[sa[i]]==id[sa[i-1]]&&(sa[i]+w<n?id[sa[i]+w]:-1)==(sa[i-1]+w<n?id[sa[i-1]+w]:-1))
				rk[sa[i]]=p-1;
			else
				rk[sa[i]]=p++;
	}
	return n;
}
int main()
{
	std::cin.tie(nullptr)->sync_with_stdio(0);
	static char s[1000001];
	std::cin>>s;
	int n=SA(s);
	for(int i=0;i<n;i++)
		std::cout<<sa[i]+1<<' ';
	return 0;
}