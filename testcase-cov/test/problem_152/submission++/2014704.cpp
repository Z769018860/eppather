


#if IN_LOCAL
import local;
#endif 
#include<cmath>
#include<cstdio>
#include<fstream>
#include<iostream>
#include<type_traits>
class FileIO
{
	static constexpr const size_t size_buffer = 33554432; const bool mode; char buffer[size_buffer], temp[22], * pin, * pout; int preci; double d; std::ofstream out;
	using ull = unsigned long long; inline void JumpUpper(const char val) { for (; *pin <= val; ++pin); return; } inline void JumpLower(const char val) { for (; *pin < val; ++pin); return; }
public:
	FileIO() :mode(1), buffer{}, temp{}, pin(buffer), pout(buffer), preci(-1), d(1e6), out() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cin.read(buffer, size_buffer); }
	FileIO(const char* const input, const char* const output) :mode(0), buffer{}, temp{}, pin(buffer), pout(buffer), preci(-1), d(1e6), out(output) { std::ifstream(input).read(buffer, size_buffer); }
	~FileIO() { if (mode) { std::cout.tie(nullptr); std::cout.write(buffer, pout - buffer); } else out.write(buffer, pout - buffer); }
	template<class T> inline FileIO& GetUnsigned(T& val) { JumpLower('0'); for (val = *pin ^ '0'; *(++pin) >= '0'; val = val * 10 + *pin - '0'); return *this; }
	template<class T> inline typename std::enable_if<std::is_unsigned<T>::value, FileIO&>::type operator>>(T& val) { return GetUnsigned(val); }
	template<class T> inline FileIO& GetSigned(T& val)
	{
		JumpLower('-'); const bool f = (*pin == '-'); for (val = *(pin += f) ^ '0'; *(++pin) >= '0'; val = val * 10 + *pin - '0'); val = (f ? -val : val); return *this;
	}
	template<class T> inline typename std::enable_if<std::is_integral<T>::value& std::is_signed<T>::value, FileIO&>::type operator>>(T& val) { return GetSigned(val); }
	template<class T> inline FileIO& GetChar(T& val) { JumpUpper(' '); val = *(pin++); return *this; } inline char GetChar() { JumpUpper(' '); return *(pin++); }
	inline FileIO& operator>>(char& val) { return GetChar(val); } inline FileIO& operator>>(char* val) { JumpUpper(' '); for (*val = *pin; *(pin++) > ' '; *(++val) = *pin); return *this; }
	inline char* GetString() { JumpUpper(' '); char* const ans = pin; for (; *pin > ' '; ++pin); return ans; }
	template<class T> inline char* GetString(const T length) { JumpUpper(' '); char* const ans = pin; pin += length; return ans; }
	template<class T> inline FileIO& GetFloatingPoint(T& val)
	{
		JumpLower('-'); const bool f = (*pin == '-');
		if (*(pin += f) != '.') { for (val = *pin ^ '0'; *(++pin) >= '0'; val = val * 10 + (*pin ^ '0')); if (*pin != '.') return val = (f ? -val : val), *this; }
		else val = 0; for (T w = 1; *(++pin) >= '0'; val += (w *= 0.1) * (*pin - '0')); return val = (f ? -val : val), *this;
	}
	template<class T> inline typename std::enable_if<std::is_floating_point<T>::value, FileIO&>::type operator>>(T& val) { return GetFloatingPoint(val); }
	template<class T> inline typename std::enable_if<std::is_unsigned<T>::value, FileIO&>::type operator<<(T val)
	{
		if (val > 9) { unsigned char len = 0; do temp[len++] = val % 10; while ((val /= 10) > 9); for (*pout = static_cast<char>(val ^ '0'); len; *(++pout) = temp[--len] ^ '0'); }
		else *pout = static_cast<char>(val ^ '0'); ++pout; return *this;
	}
	template<class T> inline typename std::enable_if<std::is_integral<T>::value& std::is_signed<T>::value, FileIO&>::type operator<<(const T val)
	{
		return *this << static_cast<typename std::make_unsigned<T>::type>(val < 0 ? *(pout++) = '-', -val : val);
	}
	inline FileIO& operator<<(const char val) { *(pout++) = val; return *this; } inline FileIO& operator<<(const char* val) { for (; *val; *(pout++) = *(val++)); return *this; }
	inline FileIO& operator<<(const bool val) { return *this << (val ? '1' : '0'); } static constexpr struct {}endl{}; inline FileIO& operator<<(const decltype(endl)) { return *this << '\n'; }
	inline FileIO& SetPrecision(const unsigned char new_preci) { d = ((preci = new_preci) < 0 ? 1e6 : pow(10, preci)); return *this; }
	inline FileIO& WriteFloatingPointSafe(const float val) { return pout += (preci < 0 ? sprintf(pout, "%.32767g", val) : sprintf(pout, "%.*f", preci, val)), *this; }
	inline FileIO& WriteFloatingPointSafe(const double val) { return pout += (preci < 0 ? sprintf(pout, "%.32767lg", val) : sprintf(pout, "%.*lf", preci, val)), *this; }
	inline FileIO& WriteFloatingPointSafe(const long double val) { return pout += (preci < 0 ? sprintf(pout, "%.32767Lg", val) : sprintf(pout, "%.*Lf", preci, val)), *this; }
	template<class T> inline typename std::enable_if<std::is_floating_point<T>::value, FileIO&>::type operator<<(T val)
	{
		const ull t = static_cast<ull>(val = static_cast<ull>((val < 0 ? *(pout++) = '-', -val : val) * d + 0.5) / d); *this << t; if ((val -= t) == 0) return *this; *(pout++) = '.';
		for (unsigned i = (preci < 0 ? 6 : preci); i > 1; --i) { char v = static_cast<char>(val *= 10); *(pout++) = v ^ '0'; if ((val -= v) == 0) return *this; }
		*(pout++) = static_cast<char>(val * 10) ^ '0'; return *this;
	}
}IO;
using ull = unsigned long long;
constexpr const unsigned mod = 1000000009;
unsigned length, f[21][1048576], g[21][1048576], h[21][1048576];
inline void FWT(unsigned(&a)[1048576])
{
	const unsigned* const end_p = a + length;
	for (unsigned i = 1; i < length; i *= 2)
	{
		for (unsigned* p = a; p != end_p; p += i)
		{
			for (unsigned j = 0; j < i; ++j, ++p)
			{
				if ((*(p + i) += *p) >= mod)
				{
					*(p + i) -= mod;
				}
			}
		}
	}
	return;
}

int get_die(int total, int now) {
  if (total >= now * 2 + 1) return now * 2 + 1;
  return now;
}

int main()
{
	unsigned n;
	IO >> n;
	length = 1u << n;
	for (unsigned i = 0; i < length; IO >> f[__builtin_popcount(i)][i], ++i);
	for (unsigned i = 0; i < length; IO >> g[__builtin_popcount(i)][i], ++i);
	for (unsigned i = 0; i <= n; FWT(f[i++]));
	for (unsigned i = 0; i <= n; ++i)
	{
		auto& g_i = g[i];
		FWT(g_i);
		for (unsigned j = i; j <= n; ++j)
		{
			const auto& f_jMi = f[j - i];
			auto& h_j = h[get_die(n,j)];
			for (unsigned k = 0; k < length; h_j[k] = (h_j[k] + static_cast<ull>(g_i[k]) * f_jMi[k]) % mod, ++k);
		}
	}
	for (unsigned i = 0; i <= n; ++i)
	{
		auto& h_i = h[i];
		const unsigned* const end_p = h_i + length;
		for (unsigned j = 1; j < length; j *= 2)
		{
			for (unsigned* p = h_i; p != end_p; p += j)
			{
				for (unsigned k = 0; k < j; ++k, ++p)
				{
					if (static_cast<int>(*(p + j) -= *p) < 0)
					{
						*(p + j) += mod;
					}
				}
			}
		}
	}
	for (unsigned i = 0; i < length; IO << h[get_die(n,__builtin_popcount(i))][i] << ' ', ++i);
	return 0;
}
