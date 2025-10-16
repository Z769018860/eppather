#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <vector>

typedef unsigned char u8;
typedef unsigned long long u64;

class perm {
	std::vector<int> v;

public:
	inline perm() = default;
	inline perm(int n) : v(n) { std::iota(v.begin(), v.end(), 0); }
	inline perm(const std::vector<int> &v, bool check = true) : v(v) {
		if (!check) return;
		std::vector<u8> t(v.size());
		for (const int &i : v)
			if (0 <= i && i < v.size() && !t[i])
				t[i] = 1;
			else
				throw new std::runtime_error("Input is not a permutation.");
	}
	inline perm(const perm &p) : v(p.v) {}

	inline int operator[](int i) const { return v[i]; }
	inline int size() const { return v.size(); }

	void print() const {
		for (int i : v) printf("%d ", i);
		puts("");
	}
	bool isId() const {
		for (int i = 0; i < size(); i++)
			if (v[i] != i) return false;
		return true;
	}
	inline perm operator*(const perm &rhs) const {
		if (size() != rhs.size())
			throw new std::runtime_error("Operands have unequal lengths.");
		std::vector<int> ret(size());
		for (size_t i = 0; i < size(); i++) ret[i] = rhs[v[i]];
		return perm(ret, false);
	}
	inline perm &operator*=(const perm &rhs) {
		if (size() != rhs.size())
			throw new std::runtime_error("Operands have unequal lengths.");
		std::vector<int> ret(size());
		for (size_t i = 0; i < size(); i++) ret[i] = rhs[v[i]];
		return v = ret, *this;
	}
	inline perm operator~() const {
		std::vector<int> ret(size());
		for (size_t i = 0; i < size(); i++) ret[v[i]] = i;
		return perm(ret, false);
	}
};

const int radix = 1e7;
struct bigint {
	std::vector<int> v;
	bigint() : v(1) {}
	inline bigint &operator*=(int x) {
		if (v.back() > radix / x) v.emplace_back(0);
		for (size_t i = 0; i < v.size(); i++) v[i] *= x;
		for (size_t i = 0; i < v.size() - 1; i++) {
			v[i + 1] += v[i] / radix;
			v[i] %= radix;
		}
		return *this;
	}
	inline void print() const {
		for (int i = (int)v.size() - 1, f = 1; i >= 0; i--, f = 0)
			printf(f ? "%d" : "%07d", v[i]);
		puts("");
	}
};

class schreier_sims {
	int n, base;
	std::vector<int> orbit;
	std::vector<perm> trans, gen;

	template <typename... _Args>
	inline void emplace_perm(_Args &&...args) {
		trans.emplace_back(args...);
		auto &p = trans.back();

		orbit[p[base]] = trans.size() - 1;
	}
	void extend_orbit(const perm &g) {
		emplace_perm(g);
		for (const perm &h : gen) {
			if (orbit[h[g[base]]] == -1)
				extend_orbit(g * h);
			else
				subgroup->extend(g * h * ~trans[orbit.at(h[g[base]])]);
		}
	}

public:
	schreier_sims *subgroup;

	schreier_sims(int n) : n(n), base(0), subgroup(nullptr), orbit(n) {
		std::fill(orbit.begin(), orbit.end(), -1);
	}
	~schreier_sims() { delete subgroup; }

	bool test(const perm &g) const {
		if (g.isId()) return true;
		int b = g[base];
		if (orbit[b] == -1) return false;
		return subgroup->test(g * ~trans[orbit.at(b)]);
	}
	void extend(const perm &g) {
		if (test(g)) return;

		gen.emplace_back(g);
		if (!subgroup) {
			for (int i = 0; i < g.size(); i++)
				if (g[i] != i) {
					base = i;
					break;
				}

			emplace_perm(g.size());
			subgroup = new schreier_sims(n);
		}

		int orig_sz = trans.size();
		for (int i = 0; i < orig_sz; i++) {
			perm &p = trans[i];
			if (orbit[g[p[base]]] == -1)
				extend_orbit(p * g);
			else
				subgroup->extend(p * g * ~trans[orbit.at(g[p[base]])]);
		}
	}
	inline int size() { return trans.size(); }
};

int n, m;
int main() {
	scanf("%d%d", &n, &m);
	schreier_sims s(n);
	std::vector<int> v(n);
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < n; j++) scanf("%d", &v[j]), v[j]--;
		s.extend(v);
	}
	bigint b;
	b.v[0] = 1;
	for (schreier_sims *p = &s; p->subgroup; p = p->subgroup) b *= p->size();
	b.print();
}
