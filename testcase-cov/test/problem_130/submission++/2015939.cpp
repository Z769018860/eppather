#include<iostream>
using namespace std;
const int Max=1e6+1;
long long c[Max];
int n,q;
long long ask(int x){
	long long ans=0;
	for(;x;x-=x&-x){
		ans+=c[x];
	}
	return ans;
}
void add(int x,int y){
	for(;x<=n;x+=x&-x){
		c[x]+=y;
	}
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		int x;cin>>x;add(i,x);
	}
	for(int i=1;i<=q;i++){
		int opt,l,k;
		cin>>opt>>l>>k; 
		if(opt==1){
			add(l,k);
		}else{
			cout<<ask(k)-ask(l-1)<<"\n";
		}		
	}
} 