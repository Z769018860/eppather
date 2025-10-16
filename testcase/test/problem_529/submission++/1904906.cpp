


#include <bits/stdc++.h>
using namespace std;
int T;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	cin>>T;
	for(int i=0,a,b;i<T;++i)
	{
		string S;
		cin>>S;
		if(S=="V")
		{
			cout<<"0 0\n";
			continue;
		}
			
		a=b=1;
		if(S.starts_with('V'))
			b=0;
		for(int j=1;j<S.size();++j)
		{
			if(S[j-1]=='N'&&S[j]=='N')
			{
				a=b=0;
				break;
			}
		}
		cout<<a<<' '<<b<<'\n';
	}
	return 0;
}