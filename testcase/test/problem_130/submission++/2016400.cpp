#include<bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;
const LL INF=0x3f3f3f3f3f3f3f3f;
const double EPS=1e-10;

const int N=2e6+10;

class HashedString {
private:
	bool _overflow;
    
    LL _n;
    LL _mo;
    LL _base;
    
    std::vector<LL> _hash;
    
    std::vector<LL> _pow;

public:
    HashedString(const std::string &s, bool overflow=false, LL mo = (1LL << 61) - 1, LL base = 13131) : 
	_overflow(overflow),
	_n(s.size()), 
	_mo(mo), 
	_base(base), 
	_hash(_n + 1), 
	_pow(_n + 1) {
        assert(s.size());
        _pow[0] = 1;
        _hash[0] = 0;
        for (size_t i = 1; i <= _n; i++) {
            if (_overflow){
				_hash[i] = _hash[i-1] * _base + s[i-1];
            	_pow[i] = _pow[i-1] * _base;
			}else{
	            _pow[i] = ((__int128)_pow[i-1] * _base) % _mo;
	            _hash[i] = (((__int128)_hash[i-1] * _base) % _mo + s[i-1]) % _mo;
			}
        }
    }

    LL get_hash(int l, int r) {
        assert(1<=l && l<=_n);
        assert(1<=r && r<=_n);
        assert(l<=r);
        if (_overflow){
			return _hash[r] - _hash[l-1] * _pow[r - l + 1];
		}else{
			return ((_hash[r] - ((__int128)_hash[l-1] * _pow[r - l + 1]) % _mo) + _mo) % _mo;
		} 
    }
};


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
            int pos, x;
            cin>>pos>>x;
            bit.modify(pos,pos,x);
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
