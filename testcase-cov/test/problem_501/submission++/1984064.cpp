#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int k,ans[N],tot=0;
signed main(){
	cin >>k;
	ans[++tot]=1;
	while(k%2==0){
		ans[++tot]=2;
		k/=2;
	}
	ans[++tot]=3;
	int flag=1,p=1;
	for(int i=1;i<=60;i++)p*=2;
	p--;
	int i=60;
	while(p>1){
		if(p==1)break;
		while(k%p==0&&p!=63){
			for(int j=1;j<=i;j++){
				ans[++tot]=flag;
			}
			flag=flag^2;
			k/=p;
		}
		p/=2;i--;
	}
	if(k>1){
		cout <<"qnq";
		return 0;
	}
	cout <<tot<<endl;
	for(int i=1;i<=tot;i++){
		cout <<ans[i]<<" ";
	}
	return 0;
}
