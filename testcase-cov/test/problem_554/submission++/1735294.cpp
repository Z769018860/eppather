#include<bits/stdc++.h>
#define int long long
#define fir first
#define sec second
#define pii pair<int,int>
using namespace std;

const int maxn=300005;
const int inf=0x3f3f3f3f;

namespace Solve {
	int n,m;
	int cnt;
	int a[maxn];
	int b[maxn];
	int d[4][maxn];
	int r2[maxn];
	int r4[maxn];
	int sr2[maxn];
	int sr4[maxn];
	vector<int> del[maxn];
	bool invalid(int x) {
		return ((d[0][x]+d[1][x]+d[2][x]+d[3][x])&1)&&d[0][x]&&d[1][x]&&d[2][x]&&d[3][x];
	}
	void add(int x,int t,int v) {
		cnt-=invalid(x);
		d[t][x]+=v;
		cnt+=invalid(x);
	}
	void dedge(int x,int y,int v) {
		add(x,(x>y)*2+(a[x]>a[y]),v);
	}
	void edge(int x,int y,int v) {
		dedge(x,y,v);
		dedge(y,x,v);
		assert(x<y);
		if(v==1) {
			del[x].push_back(y);
		}
	}
	deque<int> sd,su;
	void ins(int x) {
		if(x==n+1) {
			cnt=inf;
		} else {
			if(a[x]<a[sd.back()]) {
				sd.push_back(x);
			} else {
				while(sd.size()&&a[sd.back()]<a[x]) {
					edge(sd.back(),x,1);
					sd.pop_back();
				}
				if(sd.size()) {
					edge(sd.back(),x,1);
				}
				sd.push_back(x);
			}
			if(a[x]>a[su.back()]) {
				su.push_back(x);
			} else {
				while(su.size()&&a[su.back()]>a[x]) {
					edge(su.back(),x,1);
					su.pop_back();
				}
				if(su.size()) {
					edge(su.back(),x,1);
				}
				su.push_back(x);
			}
		}
	}
	void prepare() {
		sd.push_back(1);
		su.push_back(1);
		int r=1;
		bool ok=false;
		for(int l=1;l<=n;l++) {
			while(r<=n&&!cnt) {
				ins(++r);
			}
			if(l==1&&r==n+1) {
				ok=true;
			}
			for(int p:del[l]) {
				edge(l,p,-1);
			}
			if(su.front()==l) {
				su.pop_front();
			}
			if(sd.front()==l) {
				sd.pop_front();
			}
			r4[l]=r;
		}
		if(n==1) {
			cout<<"1\n";
		} else if(is_sorted(a+1,a+n+1)||is_sorted(b+1,b+n+1)) {
			cout<<"2\n";
		} else {
			cout<<(ok?"3":"4")<<"\n";
		}
		r=1;
		for(int l=1;l<=n;l++) {
			while((a[l]<a[l+1])==(a[r]<a[r+1])&&r+1<=n) {
				r++;
			}
			r2[l]=r;
		}
		for(int i=1;i<=n;i++) {
			sr2[i]=sr2[i-1]+r2[i];
			sr4[i]=sr4[i-1]+r4[i];
		}
	}
	void main() {


		ios::sync_with_stdio(false);
		cin.tie(0),cout.tie(0);
		cin>>n;
		for(int i=1;i<=n;i++) {
			cin>>a[i];
			b[n-i+1]=a[i];
		}
		prepare();
		cin>>m;
		for(int i=1;i<=m;i++) {
			int l,r;
			cin>>l>>r;
			if(l==r) {
				cout<<"1 1\n";
			} else {
				if(r2[l]>=r) {
					cout<<"2 "<<(r-l+1)*(r-l)/2<<"\n";
				} else {
					if(r4[l]>r) {
						int t=upper_bound(r2+l,r2+r+1,r)-r2-1;
						cout<<"3 "<<((r-l+1)*(r-l+2)/2)-(((sr2[t]-sr2[l-1])+(r-t)*r)-((r-l+1)*(l+r-2)/2))<<"\n";
					} else {
						int t=upper_bound(r4+l,r4+r+1,r)-r4-1;
						cout<<"4 "<<(t-l+1)*(r+1)-(sr4[t]-sr4[l-1])<<"\n";
					}
				}
			}
		}
		
	}
}

signed main() {
	Solve::main();
}