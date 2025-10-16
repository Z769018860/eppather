#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,q;
vector<pair<ll,int> >f,g;
int calc(int x,int y){
	int res=x|y;
	for(int i=29;~i;--i)if((x&y)>>i&1){
		res|=(1<<i)-1;
		break;
	}
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	f.push_back(make_pair(0,0));
	for(int i=1,x,y;i<=n;++i){
		scanf("%d%d",&x,&y);
		for(auto v:f){
			g.push_back(v);
			g.push_back(make_pair(x+v.first,calc(y,v.second)));
		}
		sort(g.begin(),g.end());
		f.clear(),f.push_back(make_pair(0,0));
		for(auto v:g)if(v.second>f.back().second)f.push_back(v);
		g.clear();
	}
	scanf("%d",&q);
	for(int i=1,x;i<=q;++i){
		scanf("%d",&x);
		ll ans=-1;
		for(auto v:f)if(v.second>=x){
			ans=v.first;
			break;
		}
		printf("%lld\n",ans);
	}
	return 0;
}