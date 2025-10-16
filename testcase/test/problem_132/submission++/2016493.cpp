#include<bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;
const LL INF=0x3f3f3f3f3f3f3f3f;
const double EPS=1e-10;

const int N=2e6+10;


template <class T> struct BIT{
public:
    BIT(int n){
        _n = n;
        _bit1.assign(_n+1, 0);
        _bit2.assign(_n+1, 0);
    }
    
    BIT(const std::vector<T> a) : BIT(a.size()){
        for(size_t i=1; i<=_n; i++){
            modify(i, a[i]-a[i-1]);
        }
    }
    
    void modify(int l, int r, T val){
        assert(0 <= l && l <= _n);
        assert(0 <= r && r < _n);
        assert(l <= r);
        modify(l, val);
        modify(r+1, -val);
    }
    
    T query(int pos){
        assert(0 <= pos && pos <= _n);
        T ret =0;
        for (int i=pos; i>=1; i-=lowbit(i)){
            ret += (pos+1)*_bit1[i]-_bit2[i];
        }
        return ret;
    }
    
    T query(int l, int r){
        assert(0 <= l && l <= _n);
        assert(0 <= r && r < _n);
        assert(l <= r);
        return query(r)-query(l-1);
    }

private:
    
    void modify(int pos, T val){
        assert(0 <= pos && pos <= _n);
        for (int i=pos; i<=_n; i+=lowbit(i)){
            _bit1[i] += val;
            _bit2[i] += pos*val;
        }
    }

    int lowbit(int x){
        return x&-x;
    }

private:
    std::vector<T> _bit1;
    std::vector<T> _bit2;
    int _n;
};

void solve() {
    int n,q;
    cin>>n>>q;
    vector<LL> a(n+1, 0);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    BIT<LL> bit(a);
    for(int i=1;i<=q;i++){
        int op;
        cin>>op;
        if(op==1){
            int l, r, x;
            cin>>l>>r>>x;
            bit.modify(l,r,x);
        }else if(op==2){
            int l,r;
            cin>>l>>r;
            cout<<bit.query(l,r)<<"\n";
        }
    }
}

int main() {
#if 1
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie (0);
#endif

	
	

	int T=1;
	
	for (int i=1; i<=T; i++) {
		
	    solve();
	}
	return 0;
}
