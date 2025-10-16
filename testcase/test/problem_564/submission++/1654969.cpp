#include<bits/stdc++.h>
#define ll long long
#define endl '\n'
#define pb push_back
#define inf 4557430888798830399
using namespace std;
ll n,a,b;
void work(ll a,ll b){
	for(ll i=1;i<=a;i++){
		for(ll j=1;j<=a;j++){
			cout<<i+b<<" "<<j+b<<" "<<(i+j)%a+1+b<<endl;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	a=n/2;
	b=n-a;
	cout<<a*a+b*b<<endl;
	work(a,0);
	work(b,a);
	return 0;
}