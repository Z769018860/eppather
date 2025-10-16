#include<bits/stdc++.h>
using namespace std;
typedef unsigned u32;
typedef unsigned short u16;
const u32 r = 258;
const int N = 1<<16;
template<typename T>
void read(T &x){
	int ch = getchar(); x = 0;
	for(;ch < '0' || ch > '9';ch = getchar());
	for(;ch >= '0' && ch <= '9';ch = getchar()) x = x * 10 + ch - '0';
} int T; u32 SA, SB, SC, lans, pw[N], pos[N];
u32 rng(){
    SA ^= SA << 16; SA ^= SA >> 5; SA ^= SA << 1;
    u32 t = SA; SA = SB; SB = SC; SC ^= t ^ SA;
    return SC;
} u16 mulp(u16 x, u16 y, u16 n = 16){
	if(x <= 1 || y <= 1) return x * y;
	u16 a = x>>n, b = x&(1<<n)-1, c = y>>n, d = y&(1<<n)-1, bd = mulp(b, d, n>>1);
	return ((mulp(a^b, c^d, n>>1)^bd)<<n)^bd^mulp(mulp(a, c, n>>1), 1<<n-1, n>>1);
} u16 mul16(u16 x, u16 y){
	if(x <= 1 || y <= 1) return x * y;
	int tmp = pos[x]+pos[y];
	if(tmp >= 65535) tmp -= 65535;
	return pw[tmp];
} u32 mul32(u32 x, u32 y){
	u16 a = x>>16, b = x&65535, c = y>>16, d = y&65535, bd = mul16(b, d);
	return ((mul16(a^b, c^d)^bd)<<16)^bd^mul16(mul16(a, c), 32768);
} int main(){
	read(T); read(SA); read(SB); read(SC);
	for(int i = 0, x = 1;i < 65535;++ i, x = mulp(x, r)){
		pw[i] = x; pos[x] = i;
	} while(T --){
		u32 x = rng() + lans, y = rng();
		lans = mul32(x, y);
	} printf("%u", lans);
}