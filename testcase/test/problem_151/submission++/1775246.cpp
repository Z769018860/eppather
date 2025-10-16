#include<iostream>
#include<algorithm>

using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

#define IL __inline__ __attribute__((always_inline))
#define RC(T, x) reinterpret_cast<T>(x)



namespace Setting{
	
	constexpr u32 mod = 998244353;
	
	constexpr u32 G = 3;
	
	constexpr int sta_l_MB = 64;
	
	constexpr int Detail = 1;
}


namespace Montgo{
	
	struct Mont32{
		u32 Mod, Mod2, Inv, NInv, R2;
		constexpr Mont32(u32 n):Mod(n), Mod2(n << 1), Inv(1), NInv(), R2((-u64(n)) % n){
			for (int i = 0; i < 5; ++i){Inv *= 2 - n * Inv;}
			NInv = -Inv;
		}
		constexpr IL u32 reduce (u64 x)const{return (x + u64(u32(x) * NInv) * Mod) >> 32;}
		constexpr IL u32 reduce_s (u64 x)const{
			u32 r = (x >> 32) - ((u64(u32(x) * Inv) * Mod) >> 32);
			return r >> 31 ? r + Mod : r;
		}
		constexpr IL u32 mul(u32 x, u32 y)const{return reduce(u64(x) * y);}
		constexpr IL u32 mul_s(u32 x, u32 y)const{return reduce_s(u64(x) * y);}
		constexpr IL u32 In(u32 x)const{return mul(x, R2);}
		constexpr IL u32 In_s(u32 x)const{return mul_s(x, R2);}
		constexpr IL u32 Out(u32 x)const{
			u32 r = (x + (u64(x * NInv) * Mod)) >> 32;
			return __builtin_expect(r < Mod, 1) ? r : r - Mod;
		}
	};
}


namespace field_Z{
	
	using Setting::mod;
	constexpr Montgo::Mont32 Space(mod);
	constexpr u32 mod2 = Space.Mod2;
	constexpr IL u32 shrink(u32 x){return x >= mod ? x - mod : x;}
	constexpr IL u32 dilate2(u32 x){return x >> 31 ? x + mod2 : x;}
	using Z = u32;
	constexpr bool isgood(Z x){return x < mod2;}
	
	constexpr IL Z InZ(u32 x){return Space.In(x);}
	constexpr IL Z InZs(u32 x){return Space.In_s(x);}
	
	constexpr Z zero_Z(InZs(0)), one_Z(InZs(1));
	
	constexpr Z not_exist_Z(-1);
	
	constexpr IL u32 OutZ(Z x){return Space.Out(x);}
	constexpr bool issame(Z x, Z y){return shrink(x) == shrink(y);}
	namespace calc{
		constexpr IL Z addZ(Z x, Z y){return dilate2(x + y - mod2);}
		constexpr IL Z subZ(Z x, Z y){return dilate2(x - y);}
		constexpr IL Z mulZ(Z x, Z y){return Space.mul(x, y);}
		constexpr Z powZ(Z a, u32 b, Z r = one_Z){
			while(b){
				if(b & 1){r = mulZ(r, a);}
				a = mulZ(a, a), b >>= 1;
			}
			return r;
		}
		constexpr IL Z invZ(Z x){return powZ(x, mod - 2);}
		constexpr IL Z divZ(Z x, Z y){return powZ(y, mod - 2, x);}
		template<bool strict = true>constexpr IL Z mulZs(Z x, Z y){
			if constexpr(strict){
				return Space.mul_s(x, y);
			}
			return mulZ(x, y);
		}
		constexpr Z negZ(Z x){return (!x - 1) & (mod2 - x);}
		namespace extend_{
			constexpr Z absZ(Z x){
				u32 r = OutZ(x);
				return InZs(std::min<u32>(r, mod - r));
			}
			constexpr Z legendre(Z x){return shrink(powZ(x, (mod - 1) >> 1));}
			constexpr bool isQR(Z x){return legendre(x) == one_Z;}
			constexpr Z sqrtZ(Z x){
				if(!isQR(x)){return not_exist_Z;}
				Z a(1), I_mul(0);
				while(isQR(I_mul = subZ(mulZ(a, a), x))){++a;}
				struct dZ{
					Z r, i;
					constexpr void Mul(dZ d, Z I_){
						*this = {addZ(mulZ(r, d.r), mulZ(mulZ(I_, i), d.i)), addZ(mulZ(r, d.i), mulZ(i, d.r))};
					}
				};
				dZ s = {a, one_Z}, r = {one_Z, zero_Z};
				for(u32 b = (mod + 1) >> 1; b; b>>=1){
					if(b & 1){r.Mul(s, I_mul);}
					s.Mul(s, I_mul);
				}
				return absZ(r.r);
			}
            constexpr int _inv(int x, int y){
                return 1 < x ? y - _inv(y % x, x) * y / x : 1;
            }
            constexpr Z cbrtZ(Z x){
                if(x == zero_Z){return zero_Z;}
                if constexpr (((mod - 1) % 3) == 0){
                    
                    return not_exist_Z;
                }
                else{
                    constexpr u32 iv3 = _inv(3, mod - 1);
                    return powZ(x, iv3);
                }
            }
		}
	}
	
	
	template<int fixes = 0>constexpr Z trans(Z x){
		constexpr Z o = fixes > 0 ? calc::powZ(Space.R2, fixes) : calc::powZ(1, -fixes);
		return calc::mulZs(x, o);
	}
	
	
	constexpr Z trans(Z x, int fixes){
		return calc::mulZs(x, fixes > 0 ? calc::powZ(Space.R2, fixes) : calc::powZ(1, -fixes));
	}
	
	namespace Const{
		
		constexpr Z _half = InZs((mod + 1) >> 1);
		
		constexpr Z _neghalf = InZs((mod - 1) >> 1);
		
		constexpr Z neg_one = InZs(mod - 1);
		
		constexpr Z img = calc::extend_::sqrtZ(neg_one);
		
		constexpr Z imgI = mod - img;
		
		constexpr Z _imghalf = calc::mulZs(_half, img);
	}
}
#pragma GCC target("avx2")
#include <immintrin.h>
#define Vec(sz, T) __attribute((vector_size(sz))) T
namespace SIMD{
	using i32x8 = Vec(32, i32);
	using u32x8 = Vec(32, u32);
	using i64x4 = Vec(32, i64);
	using u64x4 = Vec(32, u64);
	using I256 = __m256i;
	constexpr IL u32x8 setu32x8(u32 x){return (u32x8){x, x, x, x, x, x, x, x};}
	template<int typ>IL u32x8 shuffle(const u32x8 &x){return RC(u32x8, _mm256_shuffle_epi32(RC(I256, x), typ));}
	template<int typ>IL u32x8 blend(const u32x8 &x, const u32x8 &y){return RC(u32x8, _mm256_blend_epi32(RC(I256, x), RC(I256, y), typ));}
	IL I256 swaplohi128(const I256 &x){return _mm256_permute2x128_si256(x, x, 1);}	
	IL u32x8& x8(u32 *data){return *RC(u32x8* ,data);}
	IL const u32x8& x8(const u32 *data){return *RC(const u32x8*, data);}
	IL I256 loadu(const void* data){return _mm256_loadu_si256(RC(const __m256i_u*, data));}
	IL void storeu(const I256 &x, void* data){return _mm256_storeu_si256(RC(__m256i_u*, data), x);}
	IL u64x4 mulu32x8_fus(const u32x8 &x, const u32x8 &y){return RC(u64x4, _mm256_mul_epu32(RC(I256, x), RC(I256, y)));}
}
namespace field_Z{
	using SIMD::x8;
	using SIMD::u32x8;
	using SIMD::setu32x8;
	using Zx8 = u32x8;
	constexpr u32x8 modx8 = setu32x8(mod), mod2x8 = setu32x8(mod2), NInvx8 = setu32x8(Space.NInv);
	constexpr Zx8 one_Zx8 = setu32x8(one_Z), zerox8 = setu32x8(0u);
	IL Zx8 dilate2x8(const Zx8 &x){return x + (RC(Zx8, RC(SIMD::i32x8, x) < RC(SIMD::i32x8, zerox8)) & mod2x8);}
	IL Zx8 shrinkx8(const Zx8 &x){return x - ((x >= modx8) & modx8);}
	namespace calc{
		using namespace SIMD;
		IL Zx8 addZx8(const Zx8 &x, const Zx8 &y){return dilate2x8(x + y - mod2x8);}
		IL Zx8 subZx8(const Zx8 &x, const Zx8 &y){return dilate2x8(x - y);}
		IL Zx8 mulZx8(const Zx8 &x, const Zx8 &y){
			u32x8 z = (NInvx8 * x * y);
			return blend<0xaa>(RC(u32x8, (mulu32x8_fus(x, y) + mulu32x8_fus(z, modx8)) >> 32), RC(u32x8, (mulu32x8_fus(u32x8(u64x4(x) >> 32), u32x8(u64x4(y) >> 32)) + mulu32x8_fus(shuffle<0xf5>(z), modx8))));
		}
		IL Zx8 powZx8(Zx8 x, u32 b, Zx8 r = one_Zx8){
			while(b){
				if(b & 1){r = mulZx8(r, x);}
				x = mulZx8(x, x), b >>= 1;
			}
			return r;
		}
		IL Zx8 invZx8(const Zx8 &x){return powZx8(x, mod - 2);}
		IL Zx8 divZx8(const Zx8 &x, const Zx8 &y){return powZx8(y, mod - 2, x);}
		template<bool strict = true>IL Zx8 mulZsx8(const Zx8 &x, const Zx8 &y){
			if constexpr (strict){
				u32x8 z = (NInvx8 * x * y);
				z = blend<0xaa>(RC(u32x8, (mulu32x8_fus(x, y) + mulu32x8_fus(z, modx8)) >> 32), RC(u32x8, (mulu32x8_fus(u32x8(u64x4(x) >> 32), u32x8(u64x4(y) >> 32)) + mulu32x8_fus(shuffle<0xf5>(z), modx8)))) - modx8;
				return z + (RC(Zx8, RC(i32x8, z) < RC(i32x8, zerox8)) & modx8);
			}
			return mulZx8(x, y);
		}
		IL Zx8 negZx8(const Zx8 &x){return (x != zerox8) & (mod2x8 - x);}
	}
}
#undef Vec

namespace poly{
	
	namespace Stat_Info{
		using Setting::Detail;
		
		i64 ntt_size;
		
		i64 fill0_size, copy_size, rev_size;
		
		size_t max_cost_sta_l;

		const char* Author = "QedDust413 & killer_joke";
		const char* Thanks = "negiizhao, chaihf, rogeryoungh, Qdedawsd2233, bh1234666, yosupo, Pulsating_Dust, KKKKa, qdc, and more.";

		template<typename Tf = std::ostream>void report(Tf &outf = std::clog){
			outf << "\n";
			if constexpr(Detail <= 0){outf << "Statistics are turned off.\n";}
			if constexpr(Detail > 0){outf << "ntt_size:" << ntt_size << "\n";}
			if constexpr(Detail > 1){
				outf << "fill0_size:" << fill0_size << " copy_size:" << copy_size << " rev_size:" << rev_size << "\nmax_cost_sta:" << (double(max_cost_sta_l) / double(1 << 20)) << "\n";
			}
			outf << std::endl;
		}
	}
}
#define Stati(ifo, dt, num) if constexpr (Stat_Info::Detail > dt){Stat_Info::ifo += (num);}
namespace poly{
	
	namespace poly_base{
		using namespace field_Z;
		constexpr int bit_ceil(int x){return 1 << (32 - __builtin_clz(x - 1));}
		constexpr int bit_up(int x){return 1 << (32 - __builtin_clz(x));}
		constexpr int cro_32(int x){return __builtin_ctz(~x);}
		inline Z *to_align(void *mem){return RC(Z*, ((RC(u64, mem) + 31) >> 5) << 5);}
		inline bool is_align(const void* mem){return (RC(u64, mem) & 31) == 0;}
		void fl0(Z *f, int l){
			Stati(fill0_size, 1, l);
			std::fill_n(f, l, zero_Z);
		}
		void fl0(Z *bg, Z *ed){
			Stati(fill0_size, 1, ed - bg);
			std::fill(bg, ed, zero_Z);
		}
		void Cpy(const Z *f, int l, Z *g){
			Stati(copy_size, 1, l);
			std::copy_n(f, l, g);
		}
		void Cpy(const Z *bg, const Z *ed, Z *g){
			Stati(copy_size, 1, ed - bg);
			std::copy(bg, ed, g);
		}
		void rev(Z *bg, Z *ed){
			Stati(rev_size, 1, ed - bg);
			std::reverse(bg, ed);
		}
		void rev(Z *f, int l){
			Stati(rev_size, 1, l);
			std::reverse(f, f + l);
		}
		void Cpy_fl0(const Z *f, int n, Z *g, int lim){
			Cpy(f, n, g), fl0(g + n, g + lim);
		}
		void Cpy_rev(const Z *f, int l, Z *g){
			Stati(rev_size, 1, l);
			Stati(copy_size, 1, l);
			std::reverse_copy(f, f + l, g);
		}
		
		void mul_t_s(const Z *A, int l, Z *B, Z t){
			int i = 0;
			if(l > 16){
				Zx8 tx8 = setu32x8(t);
				for(; i + 7 < l; i += 8){
					x8(B + i) = calc::mulZx8(x8(A + i), tx8);
				}
			}
			for(; i < l; ++i){
				B[i] = calc::mulZ(A[i], t);
			}
		}
		#define flx(nam, opt) void nam(Z *A,int l,const Z *B){int i=0;for(;i+7<l;i+=8){x8(A + i)=calc::opt##Zx8(x8(A+i),x8(B+i));}for(;i<l;++i){A[i]=calc::opt##Z(A[i],B[i]);}}  void nam(const Z *A,const Z *B,int l,Z *C){int i=0;for(;i+7<l;i+=8){x8(C+i)=calc::opt##Zx8(x8(A+i),x8(B+i));}for(;i<l;++i){C[i]=calc::opt##Z(A[i],B[i]);}}
		flx(dot, mul)
		flx(addP, add)
		flx(subP, sub)
		#undef flx
		
		void NegP(const Z *A, int l, int r, Z *B){
			int i = l;
			if(r - l >= 16){
				for(; i & 7; ++i){
					B[i] = calc::negZ(A[i]);
				}
				for(; i + 7 < r; i += 8){
					x8(B + i) = calc::negZx8(x8(A + i));
				}	
			}
			for(; i < r; ++i){
				B[i] = calc::negZ(A[i]);
			}
		}
	}

	namespace poly_base{
		namespace cal_helper{
			using namespace calc;
			constexpr Zx8 eight_Zx8 = setu32x8(InZs(8));
			Z *_iv = nullptr, *_mem = nullptr, *_i = nullptr;
			int sz_iv = 0;
			void precal(int n){
				if(n > sz_iv){
					n = ((n + 7) >> 3) << 3;
					{
						Z *nxtm = new Z[n * 2 + 16], *nxtiv = to_align(nxtm), *nxti = to_align(nxtiv + n);
						if(_mem != nullptr){delete[] _mem;}
						Cpy(_iv, sz_iv, nxtiv), Cpy(_i, sz_iv, nxti), _mem = nxtm, _iv = nxtiv, _i = nxti;
					}
					Zx8 *_ix8 = RC(Zx8*, _i), *_ivx8 = RC(Zx8*, _iv);
					if(sz_iv == 0){
						for(int i = 0; i < 8; ++i){_i[i] = InZs(i);}
						*_ivx8 = invZx8(*_ix8), sz_iv = 8;
						if(n == 8){return ;}
					}
					int L = sz_iv >> 3, R = n >> 3;
					for(int i = L; i < R; ++i){_ix8[i] = addZx8(_ix8[i - 1], eight_Zx8);}
					_ivx8[L] = _ix8[L];
					for(int i = L + 1; i < R; ++i){_ivx8[i] = mulZx8(_ivx8[i - 1], _ix8[i]);}
					_ivx8[R - 1] = invZx8(_ivx8[R - 1]);
					for(int i = R - 1; i > L; --i){
						Zx8 ivix8 = _ivx8[i];
						_ivx8[i] = mulZx8(_ivx8[i], _ivx8[i - 1]), _ivx8[i - 1] = mulZx8(ivix8, _ix8[i]);
					}
					sz_iv = n;
				}
			}
			
			void deriv(const Z *g, int n, Z *f){
				precal(n + 1);
				int i = 0;
				if(n > 7){
					for(; i < 7; ++i){
						f[i] = mulZ(g[i + 1], _i[i + 1]);
					}
					for(; i < n - 7; i += 8){
						storeu(RC(I256, mulZx8(x8(g + i + 1), x8(_i + i + 1))), f + i);
					}
				}
				for(; i < n; ++i){
					f[i] = mulZ(g[i + 1], _i[i + 1]);
				}
				f[n] = zero_Z;
			}
			
			void integ(const Z *g, int n, Z *f){
				precal(n + 1);
				int i = n - 1;
				if(i > 7){
					for(; (i & 7) != 6; --i){
						f[i + 1] = mulZ(g[i], _iv[i + 1]);
					}
					for(i -= 7; i >= 0; i -= 8){
						x8(f + i + 1) = mulZx8(RC(Zx8, loadu(g + i)), x8(_iv + i + 1));
					}
					i += 7;
				}
				for(; ~i; --i){
					f[i + 1] = mulZ(g[i], _iv[i + 1]);
				}
				f[0] = zero_Z;
			}
		}
		using cal_helper::precal;
		using cal_helper::deriv;
		using cal_helper::integ;
	}

	namespace poly_base{
		namespace Tools{
			int compP(const Z *f, int l, const Z *g){
				for(int i = 0; i < l; ++i){
					if(!issame(f[i], g[i])){
						return i;
					}
				}
				return -1;
			}
			template<int fixes = 1, typename Tf = std::istream>void scanP(Z *f, int l, Tf &inf = std::cin){
				for(int i = 0; i < l; ++i){
					inf >> f[i], f[i] = trans<fixes>(f[i]);
				}
			}
			template<int fixes = -1, typename Tf = std::ostream>void printP(const Z *f, int l, Tf &outf = std::cout){
				if(l){
					outf << trans<fixes>(f[0]);
					for(int i = 1; i < l; ++i){
						outf << ' ' << trans<fixes>(f[i]);
					}
					outf << '\n';
				}
			}
			template<typename T = int, typename lT = long long>T stoi_m(const std::string &s, const T m){
				T r(0);
				for(auto ch:s){
					r = ((lT)r * 10 + (ch - '0')) % m;
				}
				return r;
			}
			int clzP(const Z *f, int n){
				int i = 0;
				while(i < n && (f[i] == zero_Z)){
					++i;
				}return i;
			}
			int crzP(const Z *f, int n){
				int i = n;
				while(i && (f[i - 1] == zero_Z)){
					--i;
				}return n - i;
			}
		}		
		
		namespace mem_helper{
			using Setting::sta_l_MB;
			char _mem[sta_l_MB << 20];
			void *now = _mem;
			struct pre_aloc{
				void* t;
				pre_aloc(){t = now;}
				~pre_aloc(){now = t;}
			};
			void *aloc(size_t l){
				void *r = now;
				now = RC(char*, r) + l;
				if constexpr(Stat_Info::Detail > 1){
					Stat_Info::max_cost_sta_l = std::max<size_t>(RC(char*, now) - _mem, Stat_Info::max_cost_sta_l);
				}
				return r;
			}
			Z *alocP(int l){
				Z *r = to_align(now);
				now = r + l;
				if constexpr(Stat_Info::Detail > 1){
					Stat_Info::max_cost_sta_l = std::max<size_t>(RC(char*, now) - _mem, Stat_Info::max_cost_sta_l);
				}
				return r;
			}
		}
		using mem_helper::pre_aloc;
		using mem_helper::alocP;
		
		void bit_reverse(Z *A, int lim){
			pre_aloc mem;
			int *rev = RC(int*, mem_helper::aloc(lim * sizeof(int)));
			rev[0] = 0;
			for (int i = 1, l2 = std::__lg(lim) - 1; i < lim; ++i) {
    			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << l2);
    			if(i < rev[i]){
					std::swap<Z>(A[i], A[rev[i]]);
				}
  			}
		}
	}using namespace poly_base;
}
namespace poly{
	
	namespace f_n_t_t_base{
		using namespace calc;
		
		template<bool strict = false>void mul_t(Z *A, int l, Z t){
			for(int j = 0; j < l; ++j){
				A[j] = mulZs<strict>(A[j], t);
			}
		}
		constexpr int mp2 = __builtin_ctz(mod - 1);
		constexpr Z _g(InZ(Setting::G));
		
		struct P_R_Tab{
			Z t[mp2 + 1];
			constexpr P_R_Tab(Z G) : t(){
				t[mp2] = shrink(powZ(G, (mod - 1) >> mp2));
				for(int i = mp2 - 1; ~i; --i){
					t[i] = mulZs(t[i + 1], t[i + 1]);
				}
			}
			constexpr Z operator [] (int i) const {
				return t[i];
			}
		};
		constexpr P_R_Tab rt1(_g), rt1_I(invZ(_g));
		
		struct ntt_info_base2{
			Z rt2[mp2 - 1], rt2_I[mp2 - 1];
			constexpr ntt_info_base2() : rt2(), rt2_I(){
				Z pr = one_Z, pr_I = one_Z;
				for(int i = 0; i < mp2 - 1; ++i){
					rt2[i] = mulZs(pr, rt1[i + 2]), rt2_I[i] = mulZs(pr_I, rt1_I[i + 2]);
					pr = mulZs(pr, rt1_I[i + 2]), pr_I = mulZs(pr_I, rt1[i + 2]);
				}
			}
		};
		
		struct ntt_info_base4x8{
			Zx8 rt3x8[mp2 - 2], rt3x8_I[mp2 - 2], rt4ix8[mp2 - 3], rt4ix8_I[mp2 - 3], pr2, pr4, pr2_I, pr4_I;
			constexpr ntt_info_base4x8():rt3x8(), rt3x8_I(), rt4ix8(), rt4ix8_I(), pr2(), pr4(), pr2_I(), pr4_I()
			{   
				Z pr = one_Z, pr_I = one_Z;
				for(int i = 0; i < mp2 - 2; ++i){
					rt3x8[i] = setu32x8(mulZs(pr, rt1[i + 3]));
					rt3x8_I[i] = setu32x8(mulZs(pr_I, rt1_I[i + 3]));
					pr = mulZs(pr, rt1_I[i + 3]), pr_I = mulZs(pr_I, rt1[i + 3]);
				}
				pr = one_Z, pr_I = one_Z;
				for(int i = 0; i < mp2 - 3; ++i){
					{
						Z a0(one_Z), a1(mulZs(pr, rt1[i + 4])), a2(mulZs(a1, a1)), a3(mulZs(a1, a2)), 
						a4(mulZs(a1, a3)), a5(mulZs(a1, a4)), a6(mulZs(a1, a5)), a7(mulZs(a1, a6));
						rt4ix8[i] = (Zx8){a0, a1, a2, a3, a4, a5, a6, a7};
					}
					{
						Z a0(one_Z), a1(mulZs(pr_I, rt1_I[i + 4])), a2(mulZs(a1, a1)), a3(mulZs(a1, a2)), 
						a4(mulZs(a1, a3)), a5(mulZs(a1, a4)), a6(mulZs(a1, a5)), a7(mulZs(a1, a6));
						rt4ix8_I[i] = (Zx8){a0, a1, a2, a3, a4, a5, a6, a7};
					}
					pr = mulZs(pr, rt1_I[i + 4]), pr_I = mulZs(pr_I, rt1[i + 4]);
				}
				pr2 = (Zx8){one_Z, one_Z, one_Z, rt1[2], one_Z, one_Z, one_Z, rt1[2]};
				pr2_I = (Zx8){one_Z, one_Z, one_Z, rt1_I[2], one_Z, one_Z, one_Z, rt1_I[2]};
				pr4 = (Zx8){one_Z, one_Z, one_Z, one_Z, one_Z, rt1[3], rt1[2], mulZs(rt1[2], rt1[3])};
				pr4_I = (Zx8){one_Z, one_Z, one_Z, one_Z, one_Z, rt1_I[3], rt1_I[2], mulZs(rt1_I[2], rt1_I[3])};
			}
		};
		template<int typ>IL u32x8 Neg(const u32x8 &x){return blend<typ>(x, mod2x8 - x);}
	}
	
    namespace f_n_t_t{
		using namespace f_n_t_t_base;
		constexpr ntt_info_base2 ib2;
		
		template<bool strict = false, int fixes = 0>void dif_base2(Z *A, int lim){
			Stati(ntt_size, 0, lim);
			for(int L = lim >> 1, R = lim; L; L >>= 1, R >>= 1){
				Z r = one_Z;
				for(int i = 0, k = 0; i < lim; i += R, ++k){
					for(int j = 0; j < L; ++j){
						Z x = dilate2(A[i + j] - mod2) , y = mulZ(r, A[i + j + L]);
						A[i + j] = x + y, A[i + j + L] = x - y + mod2;
					}
					r = mulZs(r, ib2.rt2[cro_32(k)]);
				}
			}
			if constexpr(fixes){
				mul_t<strict>(A, lim, trans<fixes>(one_Z));
			}
			else{
				for(int j = 0; j < lim; ++j){
					A[j] = dilate2(A[j] - mod2);
					if constexpr(strict){A[j] = shrink(A[j]);}
				}
			}
		}
		
		template<bool strict = false, int fixes = 0>void dit_base2(Z *A, int lim){
			Stati(ntt_size, 0, lim);
			for(int L = 1, R = 2; L < lim; L <<= 1, R <<= 1){
				Z r = one_Z;
				for(int i = 0, k = 0; i < lim; i += R, ++k){
					for(int j = 0; j < L; ++j){
						Z x = A[i + j], y = A[i + j + L];
						A[i + j] = addZ(x, y), A[i + j + L] = mulZ(x - y + mod2, r);
					}
					r = mulZs(r, ib2.rt2_I[cro_32(k)]);
				}
			}
			mul_t<strict>(A, lim, trans<fixes + 1>(mod - ((mod - 1) / lim)));
		}
		constexpr Zx8 imagx8 = setu32x8(rt1[2]), imag_Ix8 = setu32x8(rt1_I[2]);
		constexpr ntt_info_base4x8 iab4;
		
        template<bool strict = false, int fixes = 0>void dif_base4x8(Z *A, int lim){
			Stati(ntt_size, 0, lim);
			int n = lim >> 3, L = n >> 1;
			Zx8 *f = RC(Zx8*, A);
			if(__builtin_ctz(n) & 1){
				for(int j = 0; j < L; ++j){
					Zx8 x = f[j], y = f[j + L];
					f[j] = x + y, f[j + L] = x - y + mod2x8;
				}
				L >>= 1;
			}
			L >>= 1;
			for(int R = L << 2; L; L >>= 2, R >>= 2){
				Zx8 r = one_Zx8, img = imagx8;
				for(int i = 0, k = 0; i < n; i += R, ++k){
					Zx8 r2 = mulZsx8(r, r), r3 = mulZsx8(r2, r);
					for(int j = 0; j < L; ++j){
						Zx8 f0 = dilate2x8(f[i + j + 0 * L] - mod2x8);
						Zx8 f1 = mulZx8(f[i + j + 1 * L], r);
						Zx8 f2 = mulZx8(f[i + j + 2 * L], r2);
						Zx8 f3 = mulZx8(f[i + j + 3 * L], r3);
						Zx8 f1f3 = mulZx8(f1 - f3 + mod2x8, img);
						Zx8 f02 = addZx8(f0, f2);
						Zx8 f13 = addZx8(f1, f3);
						Zx8 f_02 = subZx8(f0, f2);
						f[i + j + 0 * L] = f02 + f13;
						f[i + j + 1 * L] = f02 - f13 + mod2x8;
						f[i + j + 2 * L] = f_02 + f1f3;
						f[i + j + 3 * L] = f_02 - f1f3 + mod2x8;
					}
					r = mulZsx8(r, iab4.rt3x8[cro_32(k)]);
				}
			}
			{
				constexpr Zx8 _r = setu32x8(trans<fixes>(one_Z));
				Zx8 r = _r, pr4 = iab4.pr4, pr2 = iab4.pr2;
				
				for(int i = 0; i < n; ++i){
					Zx8& fi = f[i];
					fi = mulZx8(fi, r), fi = Neg<0xf0>(fi) + RC(Zx8, swaplohi128(RC(I256, fi)));
					fi = mulZx8(fi, pr4), fi = Neg<0xcc>(fi) + shuffle<0x4e>(fi);
					fi = mulZx8(fi, pr2), fi = addZx8(Neg<0xaa>(fi), shuffle<0xb1>(fi));
					if constexpr(strict){fi = shrinkx8(fi);}
					r = mulZsx8(r, iab4.rt4ix8[cro_32(i)]);
				}
			}
        }
		
		template<bool strict = false, int fixes = 0>void dit_base4x8(Z *A, int lim){
			Stati(ntt_size, 0, lim);
			int n = lim >> 3, L = 1;
			Zx8 *f = RC(Zx8*, A);
			{
				Zx8 r = setu32x8(trans<fixes + 1>(mod - ((mod - 1) / lim))), pr4 = iab4.pr4_I, pr2 = iab4.pr2_I;
				for(int i = 0; i < n; ++i){
					Zx8& fi = f[i];
					fi = Neg<0xaa>(fi) + shuffle<0xb1>(fi), fi = mulZx8(fi, pr2);
					fi = Neg<0xcc>(fi) + shuffle<0x4e>(fi), fi = mulZx8(fi, pr4);
					fi = Neg<0xf0>(fi) + RC(Zx8, swaplohi128(RC(I256, fi))), fi = mulZx8(fi, r);
					r = mulZsx8(r, iab4.rt4ix8_I[cro_32(i)]);
				}
			}

			for (int R = L << 2; L < (n >> 1) ; L <<= 2, R <<= 2){
				Zx8 r = one_Zx8, img = imag_Ix8;
				for(int i = 0, k = 0; i < n; i += R, ++k){
					Zx8 r2 = mulZsx8(r, r), r3 = mulZsx8(r2, r);
					for(int j = 0; j < L; ++j){
						Zx8 f0 = f[i + j + 0 * L];
						Zx8 f1 = f[i + j + 1 * L];
						Zx8 f2 = f[i + j + 2 * L];
						Zx8 f3 = f[i + j + 3 * L];
						Zx8 f2f3 = mulZx8((f2 - f3 + mod2x8), img);
						Zx8 f01 = addZx8(f0, f1);
						Zx8 f23 = addZx8(f2, f3);
						Zx8 f_01 = subZx8(f0, f1);
						f[i + j + 0 * L] = addZx8(f01, f23);
						f[i + j + 1 * L] = mulZx8(f_01 + f2f3 ,r);
						f[i + j + 2 * L] = mulZx8(f01 - f23 + mod2x8, r2);
						f[i + j + 3 * L] = mulZx8(f_01 - f2f3 + mod2x8, r3);
					}
					r = mulZsx8(r, iab4.rt3x8_I[cro_32(k)]);
				}
			}
			if(__builtin_ctz(n) & 1){
				for(int j = 0; j < L; ++j){
					Zx8 x = f[j], y = f[j + L];
					f[j] = addZx8(x, y), f[j + L] = subZx8(x, y);
				}
			}
			if constexpr (strict){
				for(int i = 0; i < n; ++i){
					f[i] = shrinkx8(f[i]);
				}
			}
		}
		
		template<bool strict = false, int fixes = 0>void dif(Z *A, int lim){
			lim >= 16 ? dif_base4x8<strict, fixes>(A, lim) : dif_base2<strict, fixes>(A, lim);
		}
		
		template<bool strict = false, int fixes = 0>void dit(Z *A,int lim){
			lim >= 16 ? dit_base4x8<strict, fixes>(A, lim) : dit_base2<strict, fixes>(A, lim);
		}
    }
	using f_n_t_t::dif;
	using f_n_t_t::dit;
}
#undef Stati
namespace poly{
	
	void Conv(Z *f, int lim, Z *g){
		dif(f, lim), dif(g, lim), dot(f, lim, g), dit(f, lim);
	}

	
	void Inv(const Z *g, int n, Z *f){
        f[0] = calc::invZ(g[0]);
        if(n == 0){
            return ;
        }
		int lim = bit_up(n);
		pre_aloc mem;
		Z *o = alocP(lim), *h = alocP(lim);
		for(int t = 2, mid = 1; t <= lim; t <<= 1, mid <<= 1){
			Cpy(g, t, o), Cpy_fl0(f, mid, h, t), Conv(o, t, h), fl0(o, mid), dif(o, t), dot(o, t, h), dit(o, t), NegP(o, mid, std::min<int>(t, n + 1), f);
		}
	}

	
	void Div_naive(const Z *g, int n, const Z *f, Z *q){
        if(n == 0){
            return *q = calc::divZ(*g, *f), void();
        }
		int lim = bit_up(n) << 1;
		pre_aloc mem;
		Z *o = alocP(lim), *h = alocP(lim);
		Inv(f, n, o), fl0(o + n + 1, o + lim), Cpy_fl0(g, n + 1, h, lim), Conv(h, lim, o), Cpy(h, n + 1, q);
	}

	
	void Div(const Z *g, int n, const Z *f, Z *q){
		using namespace calc;
		if(n <= 64){
			return Div_naive(g, n, f, q);
		}
		int bn = bit_up(n >> 4), bt = (n / bn) + 1, bn2 = bn << 1;
		pre_aloc mem;
		Z *o = alocP(bn2), *jok = alocP(bn2);
		Inv(f, bn - 1, o), fl0(o + bn, bn), Cpy_fl0(g, bn, jok, bn2), Conv(jok, bn2, o);
		Z *nf = alocP(bn2 * bt), *ng = alocP(bn2 * (bt - 1));
		Cpy(jok, bn, q);
		for(int bi = 0; bi < bt; ++bi){
			int xl = std::min<int>(bn, n + 1 - bn * bi);
			Cpy_fl0(f + bi * bn, xl, nf + bi * bn2, bn2), dif(nf + bi * bn2, bn2);
			if(bi == 0){
				continue;
			}
			Cpy_fl0(q + (bi - 1) * bn, bn, ng + (bi - 1) * bn2, bn2), dif<true>(ng + (bi - 1) * bn2, bn2), fl0(jok, bn2);
			for(int j = 0; j < bi; ++j){
				Z *nF = nf + (bi - j) * bn2, *nF1 = nF - bn2, *ngj = ng + j * bn2;
				for(int i = 0; i < bn; i += 8){
					x8(jok + i) = subZx8(x8(jok + i), mulZx8(x8(nF + i) + x8(nF1 + i), x8(ngj + i)));
				}
				for(int i = bn; i < bn2; i += 8){
					x8(jok + i) = subZx8(x8(jok + i), mulZx8(x8(nF + i) - x8(nF1 + i) + mod2x8, x8(ngj + i)));
				}
			}
			dit(jok, bn2), fl0(jok + bn, bn), addP(jok, xl, g + bn * bi), dif(jok, bn2), dot(jok, bn2, o), dit(jok, bn2), Cpy(jok, xl, q + bn * bi);
		}
	}

	
	void Div(const Z *g, int n, const Z *f, int m, Z *q){
		int lim = (((n - m) >> 3) + 1 ) << 3;
		pre_aloc mem;
		Z *o = alocP(lim), *h = alocP(lim);
		Cpy_rev(f + std::max<int>(2 * m - n, 0), std::min<int>(m, n - m) + 1, o), Cpy_rev(g + m, n - m + 1, h), Div(h, n - m, o, q), rev(q, n - m + 1);
	}

	
	void Div(const Z *g, int n, const Z *f, int m, Z *q, Z *r){
		Div(g, n, f, m, q);
		int lim = bit_up(std::min<int>(n, m + m - 1));
		pre_aloc mem;
		Z *o = alocP(lim), *h = alocP(lim);
		Cpy_fl0(f, m, o, lim), Cpy_fl0(q, std::min<int>(n - m + 1, m), h, lim), Conv(o, lim, h), subP(g, o, m, r);
	}

	
	void Ln(const Z *g, int n, Z *f){
		precal(n + 1), dot(g, cal_helper::_i, n + 1, f), Div(f, n, g, f), dot(f, n + 1, cal_helper::_iv);
	}
	
	
	void Exp_naive(const Z *g, int n, Z *f){
		f[0] = one_Z;
		if(n == 0)return ;
		f[1] = g[1];
		if(n == 1)return ;
		int lim = bit_up(n);
		precal(n + 1);
		pre_aloc mem;
		Z *h = alocP(lim), *F = alocP(lim), *H = alocP(lim), *A = alocP(lim), *B = alocP(lim);
		h[0] = one_Z;
		for(int t = 4, mid = 2; t <= lim; t <<= 1, mid <<= 1){
			int xl = std::min<int>(mid, n + 1 - mid);
			Cpy_fl0(f, mid, F, t), dif(F, t), Cpy_fl0(h, mid >> 1, H, t), dif(H, t), dot(H, t, H), dot(H, t, F), dit(H, t), NegP(H, mid >> 1, mid, h), Cpy_fl0(h, mid, H, t), dif(H, t);
            deriv(g, mid - 1, A), dif(A, mid), dot(A, mid, F), dit(A, mid), deriv(f, mid - 1, B), subP(A, B, mid, A), Cpy_fl0(A, mid - 1, B + 1, t - 1), B[0] = A[mid - 1];
			dif(B, t), dot(B, t, H), dit(B, t), fl0(A, mid), dot(cal_helper::_iv + mid, B, xl, A + mid), addP(A + mid, xl, g + mid), dif(A, t), dot(A, t, F), dit(A, t), Cpy(A + mid, xl, f + mid);
		}
	}

	
	void Exp(const Z *g, int n, Z *f){
		using namespace calc;
		if(n <= 64){
			return Exp_naive(g, n, f);
		}
		int bn = bit_up(n >> 4), bt = (n / bn) + 1, bn2 = bn << 1;
		precal(n + 1);
		pre_aloc mem;
		Exp(g, bn - 1, f);
		Z *h = alocP(bn2), *jok = alocP(bn2);
		Inv(f, bn - 1, h), fl0(h + bn, bn), dif(h, bn2);
		Z *nf = alocP(bn2 * bt), *ng = alocP(bn2 * (bt - 1));
		for(int bi = 0; bi < bt; ++bi){
			int xl = std::min<int>(bn, n + 1 - bn * bi);
			dot(g + bi * bn, cal_helper::_i + bi * bn, xl, nf + bi * bn2), fl0(nf + bi * bn2 + xl, bn2 - xl), dif(nf + bi * bn2, bn2);
			if(bi == 0){
				continue;
			}
			Cpy_fl0(f + (bi - 1) * bn, bn, ng + (bi - 1) * bn2, bn2), dif<true>(ng + (bi - 1) * bn2, bn2), fl0(jok, bn2);
			for(int j = 0; j < bi; ++j){
				Z *nF = nf + (bi - j) * bn2, *nF1 = nF - bn2, *ngj = ng + j * bn2;
				for(int i = 0; i < bn; i += 8){
					x8(jok + i) = addZx8(x8(jok + i), mulZx8(x8(nF + i) + x8(nF1 + i), x8(ngj + i)));
				}
				for(int i = bn; i < bn2; i += 8){
					x8(jok + i) = addZx8(x8(jok + i), mulZx8(x8(nF + i) - x8(nF1 + i) + mod2x8, x8(ngj + i)));
				}
			}
			dit(jok, bn2), fl0(jok + bn, bn), dif(jok, bn2), dot(jok, bn2, h), dit(jok, bn2), fl0(jok + bn, bn);
            dot(jok, xl, cal_helper::_iv + bn * bi), dif(jok, bn2), dot(jok, bn2, ng), dit(jok, bn2), Cpy(jok, xl, f + bn * bi);
		}
	}

	
	void Sqrt_naive(const Z *g, int n, Z *f){
		int lim = bit_up(n);
		f[0] = calc::extend_::sqrtZ(g[0]);
		if(n == 0)return ;
		pre_aloc mem;
		Z *o = alocP(lim), *h = alocP(lim), *ff = alocP(lim), *H = alocP(lim);
		h[0] = calc::invZ(f[0]), ff[0] = f[0];
		for(int t = 2, mid = 1; t <= lim; t <<= 1, mid <<= 1){
			int xl = std::min<int>(t, n + 1);
			dot(ff, mid, ff), dit(ff, mid), subP(ff, g, mid, ff + mid), subP(ff + mid, g + mid, mid, ff + mid), fl0(ff, mid), Cpy_fl0(h, mid, H, t), Conv(ff, t, H), mul_t_s(ff + mid, xl - mid, f + mid, Const::_neghalf);
			if(t != lim){
				Cpy(f, t, o), dif(o, t), Cpy(o, t, ff), dot(o, t, H), dit(o, t), fl0(o, mid), dif(o, t), dot(o, t, H), dit(o, t), NegP(o, mid, xl, h);
			}
		}
	}
	
	
	void _Pow_pm_half(const Z *g, int n, Z *f, Z *h){
		int lim = bit_up(n);
		f[0] = calc::extend_::sqrtZ(g[0]), h[0] = calc::invZ(f[0]);
		if(n == 0)return ;
		pre_aloc mem;
		Z *o = alocP(lim), *H = alocP(lim), *ff = alocP(lim);
		ff[0] = f[0];
		for(int t = 2, mid = 1; t <= lim; t <<= 1, mid <<= 1){
			int xl = std::min<int>(t, n + 1);
			dot(ff, mid, ff), dit(ff, mid), subP(ff, g, mid, ff + mid), subP(ff + mid, g + mid, mid, ff + mid), fl0(ff, mid), Cpy_fl0(h, mid, H, t), Conv(ff, t, H), mul_t_s(ff + mid, xl - mid, f + mid, Const::_neghalf);
            Cpy(f, t, o), dif(o, t), Cpy(o, t, ff), dot(o, t, H), dit(o, t), fl0(o, mid), dif(o, t), dot(o, t, H), dit(o, t), NegP(o, mid, xl, h);
		}
	}

	
	void InvSqrt(const Z *g, int n, Z *f){
		int lim = bit_up(n);
		pre_aloc mem;
		Z *o = alocP(lim << 1), *h = alocP(lim << 1);
		f[0] = calc::invZ(calc::extend_::sqrtZ(g[0]));
		for(int t = 2, mid = 1; t <= lim; t <<= 1, mid <<= 1){
			int xl = std::min<int>(t, n + 1);
			Cpy_fl0(f, mid, o, t << 1), Cpy_fl0(g, xl, h, t << 1), dif(o, t << 1), dif(h, t << 1), dot(h, t << 1, o), dot(o, t << 1, o), dot(h, t << 1, o), dit(h, t << 1), mul_t_s(h + mid, xl - mid, f + mid, Const::_neghalf);
		}
	}

	
	void Sqrt(const Z *g, int n, Z *f){
		using namespace calc;
		if(n <= 64){
			return Sqrt_naive(g, n, f);
		}
		int bn = bit_up(n >> 4), bt = (n / bn) + 1, bn2 = bn << 1;
		pre_aloc mem;
		Z *o = alocP(bn2);
		_Pow_pm_half(g, bn - 1, f, o), mul_t_s(o, bn, o, Const::_neghalf), fl0(o + bn, bn), dif(o, bn2);
		Z *jok = alocP(bn2), *ng = alocP(bn2 * (bt - 1));
		for(int bi = 1; bi < bt; ++bi){
			int xl = std::min<int>(bn, n + 1 - bn * bi);
			Cpy_fl0(f + (bi - 1) * bn, bn, ng + (bi - 1) * bn2, bn2), dif<true>(ng + (bi - 1) * bn2, bn2), fl0(jok, bn2);
			for(int j = 0; j < bi; ++j){
				Z *nG = ng + (bi - j) * bn2, *nG1 = nG - bn2, *ngj = ng + j * bn2;
				if(j == 0){
					for(int i = 0; i < bn; i += 8){
						x8(jok + i) = addZx8(x8(jok + i), mulZx8(x8(nG1 + i), x8(ngj + i)));
					}
					for(int i = bn; i < bn2; i += 8){
						x8(jok + i) = subZx8(x8(jok + i), mulZx8(x8(nG1 + i), x8(ngj + i)));
					}
				}
				else{
					for(int i = 0; i < bn; i += 8){
						x8(jok + i) = addZx8(x8(jok + i), mulZx8(x8(nG1 + i) + x8(nG + i), x8(ngj + i)));
					}
					for(int i = bn; i < bn2; i += 8){
						x8(jok + i) = subZx8(x8(jok + i), mulZx8(x8(nG1 + i) - x8(nG + i) + mod2x8, x8(ngj + i)));
					}
				}
			}
			dit(jok, bn2), fl0(jok + bn, bn), subP(jok, xl, g + bi * bn), dif(jok, bn2), dot(jok, bn2, o), dit(jok, bn2), Cpy(jok, xl, f + bi * bn);
		}
	}

	constexpr int good_poly = 1, empty_poly = 0, not_exist_poly = -1;

	
	int safe_Sprt(const Z *g, int n, Z *f){
		int shift = Tools::clzP(g, n + 1);
		if(shift > n){
			return empty_poly;
		}
		if((shift & 1) || (!calc::extend_::isQR(g[shift]))){
			return not_exist_poly;
		}
		if(shift){
			pre_aloc mem;
			Z *h = alocP(n + 1);
			Cpy(g, n - shift + 1, f), Sqrt(f, n - (shift >> 1), h), Cpy(h, n - (shift >> 1) + 1, f + (shift >> 1)), fl0(f, shift >> 1);
		}
		else{
			Sqrt(g, n, f);
		}
		return good_poly;
	}

	
	void Pow(const Z *g, int n, int k, Z *f){
		k = ((k % mod) + mod) % mod;
		if(k == 0){
			f[0] = one_Z, fl0(f + 1, n);
		}
		else if(k == 1){
			Cpy(g, n + 1, f);
		}
		else{
			pre_aloc mem;
			Z *h = alocP(n + 1);
			Ln(g, n, f), mul_t_s(f, n + 1, h, InZ(k)), Exp(h, n, f);
		}
	}

	
	void Pow(const Z *g, int n, int k, int k2, Z *f){
		if(g[0] != one_Z){
			pre_aloc mem;
			Z *h = alocP(n + 1);
            k2 = ((k2 % (mod - 1)) + (mod - 1)) % (mod - 1);
			mul_t_s(g, n + 1, f, calc::invZ(g[0])), Pow(f, n, k, h), mul_t_s(h, n + 1, f, calc::powZ(g[0], k2));
		}
		else{
			Pow(g, n, k, f);
		}
	}

	
	int Safe_Pow(const Z *g, int n, std::string s, Z *f){
        using namespace Tools;
		if(s == std::to_string(0) && g[0] == zero_Z){
			return not_exist_poly;
		}
		int shift = clzP(g, n + 1);
		if(shift){
			if((s.size() > size_t(8)) || ((stoll(s) * shift) > i64(n))){
				return empty_poly;
			}
			int rf = (stoi(s) * shift), l = n + 1 - rf;
			pre_aloc mem;
			Z *h = alocP(l);
			Cpy(g + shift, l, f), Pow(f, l - 1, stoi_m(s, mod), stoi_m(s, mod - 1), h), Cpy(h, l, f + rf), fl0(f, rf);
		}
		else{
			Pow(g, n, stoi_m(s, mod), stoi_m(s, mod - 1), f);
		}
		return good_poly;
	}
}
namespace poly{
	namespace Useless{
		void ChirpZ(const Z *g, int n, Z c, int m, Z *f){
			using namespace calc;
			pre_aloc mem;
			int lim = bit_up((++n) + m), t = std::max<int>(n, m);
			Z *F = alocP(lim), *G = alocP(lim), *ipwc = alocP(t + 1), cI = invZ(c);
			F[0] = F[1] = ipwc[0] = one_Z;
			for(int i = 1; i <= n + m; ++i){F[i + 1] = mulZ(F[i], c);}
			for(int i = 1; i <= n + m; ++i){F[i + 1] = mulZ(F[i], F[i + 1]);}
			fl0(F + n + m + 1, F + lim);
			for(int i = 1; i <= t; ++i){ipwc[i] = mulZ(ipwc[i - 1], cI);}
			for(int i = 1; i <= t; ++i){ipwc[i] = mulZ(ipwc[i - 1], ipwc[i]);}
			for(int i = 1; i < n; ++i){G[i] = mulZ(g[n - i], ipwc[n - i - 1]);}
			G[n] = g[0], G[0] = zero_Z, fl0(G + n + 1, G + lim), Conv(F, lim, G), f[0] = F[n];
			for(int i = 1; i < m; ++i){f[i] = mulZ(F[i + n], ipwc[i - 1]);}
		}
		void Trig(const Z *g, int n, Z *sint, Z *cost){
			pre_aloc mem;
			Z *o = alocP(n + 1), *h = alocP(n + 1);
			mul_t_s(g, n + 1, o, Const::img), Exp(o, n, h), Inv(h, n, o);
			if(sint != nullptr){
				subP(o, h, n + 1, sint), mul_t_s(sint, n + 1, sint, Const::_imghalf);
			}
			if(cost != nullptr){
				addP(h, o, n + 1, cost), mul_t_s(cost, n + 1, cost, Const::_half);
			}
		}
		void Sin(const Z *g, int n, Z *f){
			Trig(g, n, f, nullptr);
		}
		void Cos(const Z *g, int n, Z *f){
			Trig(g, n, nullptr, f);
		}
		void Tan(const Z *g, int n, Z *f){
			pre_aloc mem;
			Z* h = alocP(n + 1);
			Trig(g, n, f, h), Div(f, n, h, f);
		}
		void aSin(const Z *g, int n, Z *f){
			int lim = bit_up(n) << 1;
			pre_aloc mem;
			Z *o = alocP(lim), *h = alocP(lim);
			Cpy_fl0(g, n + 1, o, lim), dif(o, lim), dot(o, lim, o), dit(o, lim);
			NegP(o, 0, n + 1, o), o[0] = calc::addZ(one_Z, o[0]), InvSqrt(o, n, h);
			deriv(g, n, o), fl0(o + n, o + lim), fl0(h + n + 1, h + lim), Conv(o, lim, h), integ(o, n, f);
		}
		void aCos(const Z* g, int n, Z* f){
			aSin(g, n, f), NegP(f, 0, n + 1, f);
		}
		void aTan(const Z *g, int n, Z *f){
			int lim = bit_up(n);
			pre_aloc mem;
			Z *o = alocP(lim << 1);
			Cpy_fl0(g, n + 1, o, lim << 1), dif(o, lim << 1), dot(o, lim << 1, o), dit(o, lim << 1);
			o[0] = calc::addZ(o[0], one_Z), deriv(g, n, o + lim), Div(o + lim, n, o, f), integ(f, n, f);
		}
        void Cbrt(const Z *g, int n, Z *f){
            f[0] = calc::extend_::cbrtZ(g[0]);
            constexpr Z three_Z = InZs(3u);
            if(n == 0)return ;
            int lim = bit_up(n);
            pre_aloc mem;
            Z *o = alocP(lim), *h = alocP(lim);
            for(int t = 2, mid = 1; t <= lim; t <<= 1, mid <<= 1){
                int xl = std::min<int>(mid, n + 1 - mid);
                Cpy(f, mid, o), dif(o, t), dot(o, o, t, h), dot(o, t, h), mul_t_s(h, t, h, three_Z), dit(h, t);
                dit(o, t), subP(g + mid, o + mid, xl, o + mid), Div(o + mid, xl - 1, h, f + mid);
            }
        }
	}
}
namespace Command{
	void cut_string(){
		_Exit(0);
	}
}

using poly::alocP;
using poly::pre_aloc;
using namespace poly::Tools;
using namespace field_Z;

#include <sys/mman.h>
#include <sys/stat.h>
#include <cstring>
namespace QIO_base{
		constexpr int O_buffer_default_size = 1 << 18;
	constexpr int O_buffer_default_flush_threshold = 40;
	struct _int_to_char_tab{
		char tab[40000];
		constexpr _int_to_char_tab():tab(){
			for(int i=0;i!=10000;++i){
				for(int j=3,n=i;~j;--j){
					tab[i*4+j]=n%10+48,n/=10;
				}
			}
		}
	}constexpr _otab;
}
namespace QIO_I {
	using namespace QIO_base;
	struct Qinf{
		FILE* f;
		char *bg,*ed,*p;
		struct stat Fl;
		Qinf(FILE *fi):f(fi)
		{
			int fd = fileno(f);
			fstat(fd,&Fl);
			bg = (char*)mmap(0,Fl.st_size + 1,PROT_READ,MAP_PRIVATE,fd,0);
			p = bg,ed = bg + Fl.st_size;
			madvise(p,Fl.st_size + 1,MADV_SEQUENTIAL);
		}
		~Qinf(){
			munmap(bg,Fl.st_size + 1);
		}
		void skip_space(){
			while(*p <= ' '){
				++p;
			}
		}
		char get(){
			return *p++;
		}
		char seek(){
			return *p;
		}
		bool eof(){
			return p == ed;
		}
		Qinf& read(char* s,size_t count){
			return memcpy(s,p,count),p+=count,*this;
		}
		Qinf& operator >> (u32 &x){
			skip_space(),x=0;
			for(;*p > ' ';++p){
				x = x * 10 + (*p & 0xf);
			}
			return *this;
		}
		Qinf& operator >> (int &x){
			skip_space();
			if(*p == '-'){
                for(++p, x = 48 - *p++;*p > ' ';++p){
					x = x * 10 - (*p ^ 48);
				}	
			}
			else{
				for(x = *p++ ^ 48;*p > ' ';++p){
					x = x * 10 + (*p ^ 48);
				}
			}
			return *this;
		}
		
	}qin(stdin);
}
namespace QIO_O{
	using namespace QIO_base;
	struct Qoutf{
		FILE *f;
		char *bg,*ed,*p;
		char *ed_thre;
		int fp;
		u64 _fpi;
		Qoutf(FILE *fo,size_t sz = O_buffer_default_size):
			f(fo),
			bg(new char[sz]),ed(bg+sz),p(bg),
			ed_thre(ed - O_buffer_default_flush_threshold),
			fp(6),
			_fpi(1000000ull){
		}
		void flush(){
			fwrite_unlocked(bg,1,p - bg,f),p=bg;
		}
		void chk(){
			if(__builtin_expect(p > ed_thre,0)){
				flush();
			}
		}
		~Qoutf(){
			flush();delete[] bg;
		}
		void put4(u32 x){
			if(x > 99u){
				if(x > 999u){
					memcpy(p,_otab.tab + (x << 2) + 0,4),p += 4;
				}
				else{
					memcpy(p,_otab.tab + (x << 2) + 1,3),p += 3;
				}
			}
			else{
				if(x > 9u){
					memcpy(p,_otab.tab + (x << 2) + 2,2),p += 2;
				}
				else{
					*p++ = x^48;
				}
			}
		}
		void put2(u32 x){
			if(x > 9u){
				memcpy(p,_otab.tab + (x << 2) + 2,2),p += 2;
			}
			else{
				*p++ = x^48;
			}
		}
		Qoutf& write(const char* s,size_t count){
			if(count > 1024 || p + count > ed_thre){
				flush(),fwrite_unlocked(s,1,count,f);
			}
			else{
				memcpy(p,s,count),p+=count,chk();
			}
			return *this;
		}
        Qoutf& operator << (char ch){
            return *p++ = ch, *this;
        }
		Qoutf& operator << (u32 x){
			if(x > 99999999u){
				put2(x / 100000000u),x %= 100000000u;
				memcpy(p,_otab.tab + ((x / 10000u) << 2),4),p += 4;
				memcpy(p,_otab.tab + ((x % 10000u) << 2),4),p += 4;
			}
			else if(x > 9999u){
				put4(x / 10000u);
				memcpy(p,_otab.tab + ((x % 10000u) << 2),4),p += 4;
			}
			else{
				put4(x);
			}
			return chk() ,*this;
		}
		Qoutf& operator << (int x){
			if(x < 0){
				*p++ = '-', x = -x;
			}
			return *this << static_cast<u32>(x);
		}
	}qout(stdout);
}
namespace QIO{
	using QIO_I::Qinf;
	using QIO_I::qin;
	using QIO_O::Qoutf;
	using QIO_O::qout;
}

using namespace QIO;

void solve(){
	int n;
    qin >> n;
    auto F = alocP(n + 1), G = alocP(n + 1);
    scanP(F, n + 1, qin);
    poly::Useless::Cbrt(F, n, G);
    printP(G, n + 1, qout);
	poly::Stat_Info::report();
}

int main(){
	std::cin.tie(nullptr) -> sync_with_stdio(false);
	solve();
	return 0;
}