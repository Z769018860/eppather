#include<bits/stdc++.h>
#define int long
using namespace std;
bool vis[1010];
int gs[1010],tot;
int a[1010];
signed main(){
	for(int i=2;i<=1000;i++){
		if(vis[i]) continue;
		gs[++tot]=i;
		for(int j=2;i*j<=1000;j++){
			vis[i*j]=1;
		}
	}
	int t,m,base,cur=0,val=0,tmp=0,ans=0;
	cin>>t;
	while(t--){
		cin>>m;
		ans=1;
		for(int i=1;i<=m;i++){
			cin>>a[i];
			val=1;
			base=1; 
			cur=0;
			tmp=0;
			while(base*gs[i]+1<a[i]){
				base=base*gs[i]+1;
				val*=gs[i];
				cur++;
			}
			for(int j=cur;j>=0;j--){
				tmp+=val*(a[i]/base)*gs[i];
				a[i]-=base*(a[i]/base);
				base/=gs[i],val/=gs[i];
			}
			ans=max(ans,tmp);
		}
		cout<<ans<<endl;
	}
}