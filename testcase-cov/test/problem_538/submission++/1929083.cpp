#include <bits/stdc++.h>
#define ffor(i,l,r) for(ll i=(l),i##_end=(r);i<=i##_end;i++)
using namespace std;
using ll = long long;
const ll INF = 1e12;
struct Matrix {
	ll d[2][2];
	Matrix friend operator *(const Matrix &a,const Matrix &b) {
		Matrix res = Matrix::None();
		for(ll k=0; k<2; k++) {
			for(ll i=0; i<2; i++) {
				for(ll j=0; j<2; j++) {
					auto &o = res.d[i][j];
					ll tmp = res.d[i][j]+1ll*a.d[i][k]*b.d[k][j];
					if(tmp>INF) o = INF;
					else if(tmp<-INF) o = -INF;
					else o = tmp;
				}
			}
		}
		return res;
	}
	static Matrix None() {
		return Matrix{0,0,0,0};
	}
	static Matrix Zero(){
		return Matrix{1,0,0,1};
	}
	static Matrix Begin(ll a0,ll a1){
		return Matrix{a1-a0,a0,0,0};
	}
	static Matrix Move(ll k){
		return Matrix{0,k,1,1};
	}
};
Matrix qpow(Matrix base,ll v){
	Matrix ret = Matrix::Zero();
	while(v){
		if(v&1) ret = ret*base;
		base = base*base;
		v>>=1;
	}
	return ret;
}
ll m,n,k; 
ll s[300010];
ll a[300010];
bool m2;
int main() {
	cin>>m;
	ffor(i,1,m) cin>>s[i];
	sort(s+1,s+m+1,less<ll>());
	cin>>n;

	while (n--) {
		cin>>a[0]>>a[1]>>k;
		ll minn = INF, maxx = -INF, mni = 0,mxi = 0;

		if (a[0]==0 && a[1]==0) {
			cout<<s[1]<<" "<<s[1]<<"\n";
			continue;
		}
		int j;
		for(j=2;j<=200;j++){
			a[j] = k * a[j - 1] + a[j - 2];

			if (a[j] >= INF || a[j] <= -INF)
				break;
		}

		ffor(i,1,m) {
			if (s[i] <= j) {
				if (a[s[i]] < minn)
					minn = a[s[i]], mni = s[i];

				if (a[s[i]] > maxx)
					maxx = a[s[i]], mxi = s[i];
			} else
				break;
		}

		if (s[m] > j) {
			if (a[j] > a[j - 1] && a[j - 1] > a[j - 2])
				mxi = s[m];
			else if (a[j] < a[j - 1] && a[j - 1] < a[j - 2])
				mni = s[m];
		}

		if (!mxi)
			mxi = s[1];

		if (!mni)
			mni = s[1];

		cout<<mxi<<" "<<mni<<"\n";
	}

	return 0;
}