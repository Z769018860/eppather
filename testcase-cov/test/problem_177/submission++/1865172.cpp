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

typedef __int128 bigint;

class perm {
	std::vector<int> v;
	inline perm(const std::vector<int> &v, bool check) : v(v) {
		if (!check) return;
		std::vector<u8> t(v.size());
		for (const int &i : v)
			if (0 <= i && i < v.size() && !t[i])
				t[i] = 1;
			else
				throw new std::runtime_error("Input is not a permutation.");
	}

public:
	inline perm() = default;
	inline perm(int n) : v(n) { std::iota(v.begin(), v.end(), 0); }
	inline perm(const std::vector<int> &v) : perm(v, true) {}
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
		for (int i = 0; i < size(); i++) ret[i] = rhs[v[i]];
		return ret;
	}
	inline perm &operator*=(const perm &rhs) {
		if (size() != rhs.size())
			throw new std::runtime_error("Operands have unequal lengths.");
		std::vector<int> ret(size());
		for (int i = 0; i < size(); i++) ret[i] = rhs[v[i]];
		return v = ret, *this;
	}
	inline perm operator~() const {
		std::vector<int> ret(size());
		for (int i = 0; i < size(); i++) ret[v[i]] = i;
		return ret;
	}
};

const int radix = 1e7;
struct B {
	std::vector<int> v;
	B() : v(1) {}
	inline B &operator*=(int x) {
		if (v.back() > radix / x) v.emplace_back(0);
		for (int i = 0; i < v.size(); i++) v[i] *= x;
		for (int i = 0; i < v.size() - 1; i++) {
			v[i + 1] += v[i] / radix;
			v[i] %= radix;
		}
		return *this;
	}
	inline void print() const {
		for (int i = v.size() - 1, f = 1; i >= 0; i--, f = 0)
			printf(f ? "%d" : "%07d", v[i]);
		puts("");
	}
};

class schreier_sims {
	int base;
	std::map<int, perm> orbit;
	std::vector<perm> trans, gen;

	template <typename... _Args>
	inline void emplace_perm(_Args &&...args) {
		trans.emplace_back(args...);
		auto &p = trans.back();

		orbit.emplace(p[base], p);
	}
	void add_orbit(const perm &g) {
		emplace_perm(g);
		for (const perm &h : gen) {
			if (!orbit.count(h[g[base]]))
				add_orbit(g * h);
			else
				subgroup->extend(g * h * ~orbit[h[g[base]]]);
		}
	}

public:
	schreier_sims *subgroup;

	schreier_sims() : base(0), subgroup(nullptr) {}
	~schreier_sims() { delete subgroup; }

	bool test(const perm &g) const {
		if (g.isId()) return true;
		int b = g[base];
		if (!orbit.count(b)) return false;
		return subgroup->test(g * ~orbit.at(b));
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

			perm h(g.size());
			do {
				emplace_perm(h);
				h *= g;
			} while (h[base] != base);

			(subgroup = new schreier_sims())->extend(h);
		} else {
			int orig_sz = trans.size();
			for (int i = 0; i < orig_sz; i++) {
				perm &p = trans[i];
				if (!orbit.count(g[p[base]]))
					add_orbit(p * g);
				else
					subgroup->extend(p * g * ~orbit[g[p[base]]]);
			}
		}
	}
	inline int size() { return trans.size(); }
};

schreier_sims s;
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	std::vector<int> v(n);
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < n; j++) scanf("%d", &v[j]), v[j]--;
		s.extend(v);
		
	}
	B b;
	b.v[0] = 1;
	for (schreier_sims *p = &s; p->subgroup; p = p->subgroup) b *= p->size();
	b.print();
}
