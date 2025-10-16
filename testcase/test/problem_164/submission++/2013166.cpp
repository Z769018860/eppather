#include <bits/stdc++.h>
#define __builtin_ia32_adc(x, y, flag) __asm__("addb   %3, %0\n\t" "adcq   %2, %1\n\t" "setc   %0":"+r"(flag),"+r"(x):"r"(y),"i"(-1):"cc")

using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u128 = unsigned __int128;

u64 *copy_new(u64 *start, u64 size){
	u64 *res = new u64[size];
	copy(start, start+size, res);
	return res;
}

class bigint {
	
friend inline bigint operator<<(const bigint &a, const u64 b);
friend inline bigint operator>>(const bigint &a, const u64 b);
friend inline bigint operator&(const bigint &a, const bigint &b);
friend inline bigint operator|(const bigint &a, const bigint &b);
friend inline bigint operator^(const bigint &a, const bigint &b);
friend inline bigint operator+(const bigint &a, const bigint &b);
friend inline bigint operator-(const bigint &a, const bigint &b);
friend inline bigint operator*(const bigint &a, const bigint &b);
friend inline bigint operator/(const bigint &a, const bigint &b);
friend inline bigint operator%(const bigint &a, const bigint &b);
friend inline bigint operator~(const bigint &a);
friend inline bigint operator+(const bigint &a);
friend inline bigint operator-(const bigint &a);
friend inline bool operator<(const bigint &a, const bigint &b);
friend inline bool operator>(const bigint &a, const bigint &b);
friend inline bool operator==(const bigint &a, const bigint &b);
friend inline bool operator!=(const bigint &a, const bigint &b);
friend inline bool operator<=(const bigint &a, const bigint &b);
friend inline bool operator>=(const bigint &a, const bigint &b);
friend inline ostream &operator<<(ostream &os, const bigint &a);
friend inline istream &operator>>(istream &is, bigint &a);

friend bigint pow(bigint a, u64 b);

public:	
	bigint();
	bigint(i64 x);
	bigint(const string &s);
	bigint(const bigint &p);
	~bigint();

	explicit operator string() const;
	explicit operator bool() const;
	explicit operator i64() const;

	u64 digit() const;

	bigint &operator=(const bigint& p);
	bigint &operator<<=(const u64 n);
	bigint &operator>>=(const u64 n);
	bigint &operator&=(const bigint &a);
	bigint &operator|=(const bigint &a);
	bigint &operator^=(const bigint &a);
	bigint &operator+=(const bigint &a);	
	bigint &operator-=(const bigint &a);
	bigint &operator*=(const bigint &a);
	bigint &operator/=(const bigint &a);
	bigint &operator%=(const bigint &a);
	bigint &operator++();
	bigint &operator--();
	bigint operator++(int);
	bigint operator--(int);
	
private:
	bool sign = true;  
	u64 *data, size, capacity;
	
	bigint(bool sign, u64 *data, u64 size);
	void resize(u64 n, u64 val = 0);
	void push(u64 n);
	void clear();
	void change_sign();
	bigint &change();
	bigint &make(const string &s);
	bigint getitem(u64 start, u64 end) const;
};

bigint::bigint(): data(new u64[0]), size(0), capacity(0){}
bigint::bigint(i64 x): sign(x >= 0), data(new u64[x?1:0]), size(x?1:0), capacity(x?1:0){if (x) data[0] = abs(x);}

bigint::bigint(const string &s): data(new u64[0]), size(0), capacity(0){
	if (s.empty()) {
		clear();
		return;
	}
	if (s.size() >= 1 && (s[0] == '+' || s[0] == '-')){
		make(s.substr(1));
		if (s[0] == '-') sign = !sign;
	} else {
		make(s);
	}
}

bigint::bigint(bool sign, u64 *data, u64 size): sign(sign), data(copy_new(data, size)), size(size), capacity(size){}
bigint::bigint(const bigint &p): bigint(p.sign, p.data, p.size){}
bigint::~bigint(){delete[] data;}

bigint::operator string() const {
	if (!size) return "0";
	if (!sign) return string("-") += string(-*this);
	if (size == 1) return to_string(data[0]);
	u64 cnt = (digit()*1000/3322)>>1;  
	bigint p = pow(bigint(10), cnt);
	bigint lval = (*this)/p, rval = *this-lval*p;
	string l = string(lval), r = string(rval), m(cnt-r.size(), '0');
	return l += m += r;
}

bigint::operator bool() const {return size;}
bigint::operator i64() const {return size?(sign?data[0]:-data[0]):0;}

u64 bigint::digit() const {return size?(size<<6)-__builtin_clzll(data[size-1]):0;}

bigint &bigint::operator=(const bigint& p){
	if (data == p.data) return *this;
	delete[] data;
	sign = p.sign, data = copy_new(p.data, p.size), size = p.size, capacity = p.size;
	return *this;
}

bigint &bigint::operator<<=(const u64 n){
	if (!size) return *this;
	u64 w = n&63, z = n>>6, i = size;
	bool flg = 0;
	if (w&&(data[size-1]>>(64-w))) push(0), flg = 1;
	resize(size+z);
	while (i){
		--i;
		if (flg) data[i+z+1] |= data[i]>>(64-w);
		data[i+z] = data[i]<<w, flg |= bool(w);
	}
	fill(data, data+z, 0);
	return *this;
}

bigint &bigint::operator>>=(const u64 n){
	if (!sign) return sign = !sign, *this >>= n, sign = !sign, --*this; 
	u64 z = n >> 6, i = 0;
	for(u64 w = n&63; i+z<size; ++i){
		if (w && i) data[i-1] |= data[i+z]<<(64-w);
		data[i] = data[i+z] >> w;
	}
	resize(i);
	while (size&&!data[size-1]) size -= 1;
	return *this;
}

bigint &bigint::operator&=(const bigint &a){
	if (!sign) return change() &= a, change_sign(), *this;
	if (!a.sign) return *this &= bigint(a).change(), change_sign(), *this;
	u64 n = min(size, a.size);
	resize(n);
	for (u64 i = 0; i<n; ++i) data[i] &= a.data[i];
	return *this;
}

bigint &bigint::operator|=(const bigint &a){
	if (!sign) return change() |= a, change_sign(), *this;
	if (!a.sign) return *this |= bigint(a).change(), change_sign(), *this;
	u64 n = max(size, a.size);
	resize(n);
	for (u64 i = 0; i<n; ++i) data[i] |= a.data[i];
	return *this;
}

bigint &bigint::operator^=(const bigint &a){
	if (!sign) return change() ^= a, change_sign(), *this;
	if (!a.sign) return *this ^= bigint(a).change(), change_sign(), *this;
	u64 n = max(size, a.size);
	resize(n);
	for (u64 i = 0; i<n; ++i) data[i] ^= a.data[i];
	return *this;
}

bigint &bigint::operator+=(const bigint &a){
	if (!a.sign) return *this -= -a;
	if (!sign){
		bigint p = a;
		swap(sign, p.sign), swap(data, p.data), swap(size, p.size), swap(capacity, p.capacity);
		return *this += p, *this;
	}
	resize(max(size, a.size));
	bool carry = 0;
	for (u64 i = 0; i<size; ++i){
		u64 rg = 0;
		if (i<a.size) rg = a.data[i];
		__builtin_ia32_adc(data[i], rg, carry);
	}
	if (carry) push(1);
	return *this;
}

bigint &bigint::operator-=(const bigint &a){
	if (!a.sign) return *this += -a;
	if (!sign) return sign = true, *this += a, sign = false, *this;
	if (*this < a){
		bigint p = a;
		swap(data, p.data), swap(size, p.size), swap(capacity, p.capacity);
		return *this -= p, sign = false, *this;
	}
	bool carry = 1;
	for(u64 i = 0; i<size; ++i){
		u64 rg = -1;
		if (i<a.size) rg = ~a.data[i];
		__builtin_ia32_adc(data[i], rg, carry);
	}
	while (size&&!data[size-1]) size -= 1;
	return *this;
}

bigint &bigint::operator*=(const bigint &a){
	if (!a.sign) return *this *= -a, sign = !sign, *this;
	if (!sign) return sign = true, *this *= a, sign = !sign, *this;
	if (!*this || !a) return clear(), *this;
	if ((size <= 80 && a.size <= 80) || (size <= 8) || (a.size <= 8)){
		u64 sz = size+a.size, *res = new u64[sz];
		fill(res, res+sz, 0);
		for (u64 i = 0, j; i<size; ++i){
			u64 carry = 0;
			bool wcarry = 0;
			for (j = 0; j<a.size; ++j){
				u128 r = data[i]*(u128)a.data[j]+carry;
				u64 cur = r;
				carry = r>>64;
				__builtin_ia32_adc(res[j+i], cur, wcarry);
			}
			if (carry||wcarry) __builtin_ia32_adc(res[j+i], carry, wcarry);
		}
		delete[] data;
		size = sz, capacity = sz, data = res;
		if (!data[size-1]) --size;
		return *this;
	} else {
		u64 n = (max(size, a.size)+1)>>1;  
		bigint l = getitem(n, n*2), r = getitem(0, n);
		bigint l2 = a.getitem(n, n*2), r2 = a.getitem(0, n);
		while (r.size&&!r.data[r.size-1]) --r.size;
		while (r2.size&&!r2.data[r2.size-1]) --r2.size;
		bigint m = (l+r) *= (l2+r2);
		return l *= l2, r *= r2, (*this = (l <<= (n<<7))) += (((m -= l) -= r) <<= (n<<6)) += r, *this;
	}
}

bigint &bigint::operator/=(const bigint &a){
	if (!a.sign) return *this /= -a, sign = !sign, *this;
	if (!sign) return sign = true, *this /= a, sign = !sign, *this;
	if (!a) throw runtime_error("Zero cannot be divisor.");
	if (a.digit()>digit()) return clear(), *this;
	bigint x = 1, p;
	u64 bit = a.digit(), cnt = 64-__builtin_clzll(digit()-a.digit())+1;
	for (u64 i = 0; i<cnt; ++i) (x *= (bigint(1) <<= (bit+1)) -= x*a) >>= bit-(u64(1)<<i), bit += 1<<i;
	bigint res = *this*x>>bit;
	while ((res+1)*a <= *this) ++res;
	return *this = res;
}

bigint &bigint::operator%=(const bigint &a){
	return *this -= *this/a*a;
}

bigint &bigint::operator++(){return *this += 1;}
bigint &bigint::operator--(){return *this -= 1;}

bigint bigint::operator++(int){
	bigint res = *this;
	return ++*this, res;
}

bigint bigint::operator--(int){
	bigint res = *this;
	return --*this, res;
}

void bigint::resize(u64 n, u64 val){
	if (n > capacity){
		while (capacity < n) capacity = ((capacity*3)>>1)+1;
		u64 *arr = new u64[capacity];
		copy(data, data+size, arr);
		delete[] data;
		data = arr;
	}
	if (n > size) fill(data+size, data+n, val);
	size = n;
}

void bigint::push(u64 n){
	if (size == capacity){
		capacity = ((capacity*3)>>1)+1;
		u64 *arr = new u64[capacity];
		copy(data, data+size, arr);
		delete[] data;
		data = arr;
	}
	data[size++] = n;
}

void bigint::clear(){
	delete[] data;
	sign = true, data = new u64[0], size = 0, capacity = 0;
}

void bigint::change_sign(){
	if (*this && sign && ~data[size-1] < data[size-1]){
		sign = false;
		for (u64 i = 0; i < size; ++i) data[i] = ~data[i];
		--*this;
	}
}

bigint &bigint::change(){
	if (!(digit()&63)) push(sign?0:~u64(0));
	++*this;
	sign = true;
	for (u64 i = 0; i < size; ++i) data[i] = ~data[i];
	return *this;
}

bigint bigint::getitem(u64 start, u64 end) const {return start >= size?0:bigint(sign, data+start, min(end, size)-start);}

bigint &bigint::make(const string &s){
	if (s.empty()) return clear(), *this;
	if (s.size() <= 19) return clear(), push(stoull(s)), *this;
	u64 cnt = s.size()>>1;
	bigint p = pow(bigint(10), s.size()-cnt), l, r;
	return ((*this = l.make(s.substr(0, cnt))) *= p) += r.make(s.substr(cnt));
}

inline bigint operator<<(const bigint &a, const u64 b){return bigint(a) <<= b;}
inline bigint operator>>(const bigint &a, const u64 b){return bigint(a) >>= b;}
inline bigint operator+(const bigint &a, const bigint &b){return bigint(a) += b;}
inline bigint operator-(const bigint &a, const bigint &b){return bigint(a) -= b;}
inline bigint operator*(const bigint &a, const bigint &b){return bigint(a) *= b;}
inline bigint operator/(const bigint &a, const bigint &b){return bigint(a) /= b;}
inline bigint operator%(const bigint &a, const bigint &b){return bigint(a) %= b;}
inline bigint operator&(const bigint &a, const bigint &b){return bigint(a) &= b;}
inline bigint operator|(const bigint &a, const bigint &b){return bigint(a) |= b;}
inline bigint operator^(const bigint &a, const bigint &b){return bigint(a) ^= b;}
inline bigint operator~(const bigint &a){return --(-a);}
inline bigint operator+(const bigint &a){return bigint(a.sign, a.data, a.size);}
inline bigint operator-(const bigint &a){return bigint(!a.sign, a.data, a.size);}

inline bool operator<(const bigint &a, const bigint &b) {
	if (!a.size && !b.size) return false;
	if (a.sign != b.sign) return a.sign < b.sign;
	if (!a.sign) return (-a)>(-b);
	if (a.size != b.size) return a.size < b.size;
	u64 i = a.size;
	while (i)
		if (--i, a.data[i] != b.data[i]) return a.data[i]<b.data[i];
	return false;
}

inline bool operator>(const bigint &a, const bigint &b){return b<a;}
inline bool operator==(const bigint &a, const bigint &b){return a.sign == b.sign && a.size == b.size && equal(a.data, a.data+a.size, b.data);}
inline bool operator!=(const bigint &a, const bigint &b){return a.sign != b.sign || a.size != b.size || !equal(a.data, a.data+a.size, b.data);}
inline bool operator<=(const bigint &a, const bigint &b){return !(a>b);}
inline bool operator>=(const bigint &a, const bigint &b){return !(a<b);}

inline ostream &operator<<(ostream &os, const bigint &a){return os << (string)(a);}

inline istream &operator>>(istream &is, bigint &a){
	string s;
	try {return is >> s, a = s, is;}
	catch (...) {return a.clear(), is;}	
}

bigint pow(bigint a, u64 b){
	bigint res = 1;
	while (b){
		if (b&1) res *= a;
		b >>= 1, a *= a;
	}
	return res;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    bigint a, b;
    cin >> a >> b;
    cout << a/b;
    return 0;
}