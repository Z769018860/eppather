#include<iostream>
using namespace std;
const int Max=1000002;
long long c[Max];
int n,q;
void add(int x,int y){
	for(;x<=n;x+=x&-x){
		c[x]+=y;
	}
}
long long ask(int x){
	long long ans=0;
	for(;x;x-=x&-x){
		ans+=c[x];
	}
	return ans;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		int tmp;cin>>tmp;
		add(i,tmp);add(i+1,-tmp);
	}
	for(int i=1;i<=q;i++){
		int opt;cin>>opt;
		if(opt==1){
			int x,y,z;cin>>x>>y>>z;
			add(x,z);
			add(y+1,-z);
		}else{
			int x;cin>>x;
			cout<<ask(x)<<"\n";
		}
	}
} 