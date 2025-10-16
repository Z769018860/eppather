


#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int primes[]
{
	2, 3, 5, 7, 11, 13, 17, 19, 23,
	29, 31, 37, 41, 43, 47, 53, 59,
	61, 67, 71, 73, 79, 83, 89, 97,
	101, 103, 107, 109, 113, 127, 131, 137,
	139, 149, 151, 157, 163, 167, 173, 179,
	181, 191, 193, 197, 199, 211, 223, 227,
	229, 233, 239, 241, 251, 257, 263, 269,
	271, 277, 281, 283, 293, 307, 311, 313,
	317, 331, 337, 347, 349, 353, 359, 367,
	373, 379, 383, 389, 397, 401, 409, 419,
	421, 431, 433, 439, 443, 449, 457, 461,
	463, 467, 479, 487, 491, 499, 503, 509,
	521, 523, 541, 547, 557, 563, 569, 571
};
int countfac(int const n,int const pr)
{
	int ans=0;
	for(int i=n/pr;i;i/=pr)
		ans+=i;
	return ans;
}
int requirement(int pri,int ei,int l)
{
	int r=1e18;
	for(;r-l>0;)
	{

		int mid=(l+r)>>1,emid=countfac(mid,primes[pri]);
		if(emid>=ei)
			r=mid;
		else
			l=mid+1;
	}



	return l;
}
int sum[105][70]{},ssum[105][70];
int requirement(int const pri,int ei)
{
	int const p=primes[pri];
	int len=0;
	for(int cnt=ei;cnt>0;cnt-=sum[pri][len])
		++len;
	++len;
	int n=0;
	for(int i=len;i>1;--i)
	{
		int now=(ceil(static_cast<double>(ei-ssum[pri][i-2])/(sum[pri][i-1]/(p-1))));
		now=max(now,0ll);
		n+=now;
		n*=p;
		ei-=now*(sum[pri][i-1]/(p-1));
	}
	return n;
}
int T,m;
main()
{

	


















	for(int i=0;i<105;++i)
	{
		sum[i][1]=primes[i]-1;
		for(int j=2;j<70;++j)
			sum[i][j]=sum[i][j-1]*primes[i]+primes[i]-1;
		partial_sum(sum[i],sum[i]+70,ssum[i]);
	}
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	cin>>T;
	for(int i=0,mx;i<T;++i)
	{
		cin>>m;
		mx=0;
		for(int j=0,ei;j<m;++j)
		{
			cin>>ei;
			mx=max(mx,requirement(j,ei));
		}
		cout<<max(mx,1ll)<<'\n';
	}
	return 0;
}