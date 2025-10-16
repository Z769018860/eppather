# include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	cout<<(n*n+1)/2<<endl;
	for(int i=1;i<=n;i+=2)
		for(int j=1,k=i;j<=n;j+=2,k+=2,k>n && (k=1))
			printf("%d %d %d\n",j,i,k);
	for(int i=2;i<=n;i+=2)
		for(int j=2,k=i;j<=n;j+=2,k+=2,k>n && (k=2))
			printf("%d %d %d\n",j,i,k);
	return 0;
}