#include <stdio.h>
#include <string.h>
#include <vector>
#include <numeric>

using perm = std::vector<int>;

inline perm id(int n)
{
    perm ans(n);
    std::iota(ans.begin(), ans.end(), 0);
    return ans;
}

inline perm operator*(const perm& p, const perm& q)
{
    int n = p.size(); perm ans(n);
    for (int i = 0; i < n; i++)
        ans[i] = p[q[i]];
    return ans;
}

inline perm operator-(const perm& p)
{
    int n = p.size(); perm ans(n);
    for (int i = 0; i < n; i++)
        ans[p[i]] = i;
    return ans;
}

inline perm trunc(const perm& p)
{
    return perm(p.begin(), p.end() - 1);
}

inline perm output(perm p)
{
    printf("{");
    for (auto&& i : p) printf("%d, ", i);
    printf("}");
}

const int N = 55;

struct group
{
    int n, orbsz;
    std::vector<perm> trs, gen;
    group* sub;

    inline group() {}
    inline void init(int n)
    {
        this -> n = n; orbsz = 1;
        trs.resize(n);
        trs.back() = id(n);
    }

    inline bool test(perm p) const
    {
        if (n == 1) return true;
        int pn = p.back();
        if (trs[pn].empty()) return false;
        return sub -> test(trunc(-trs[pn] * p));
    }

    inline void insert_gen(const perm& p)
    {
        if (n == 1) return;
        if (test(p)) return;
        gen.push_back(p);
        auto dfs = [&](auto self, const perm& p) -> void 
        {
            int pn = p.back();
            if (trs[pn].size())
                sub -> insert_gen(trunc(-trs[pn] * p));
            else
            {
                orbsz++;
                trs[pn] = p;
                for (auto&& g : gen)
                    self(self, g * p);
            }
        };
        for (auto&& tr : trs)
            if (tr.size())
                dfs(dfs, p * tr);
    }
}
chain[N];

const int radix = 10000, digs = 17;

struct kmn
{
    int a[digs];

    inline kmn() { memset(a, 0, sizeof a); }

    inline void operator*=(int x)
    {
        for (int i = 0; i < digs; i++) a[i] *= x;
        for (int i = 0; i < digs - 1; i++)
            a[i + 1] += a[i] / radix, a[i] %= radix;
    }

    inline void output() const
    {
        bool start = false;
        for (int i = digs - 1; i >= 0; i--)
            if (start)
                printf("%04d", a[i]);
            else if (a[i])
                printf("%d", a[i]), start = true;
        putchar('\n');
    }
};

int main()
{
    int n, m; scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
    {
        chain[i].init(i);
        if (i > 1) chain[i].sub = &chain[i - 1];
    }

    while (m--)
    {
        perm gen;
        for (int i = 0; i < n; i++)
        {
            int x; scanf("%d", &x); gen.push_back(x - 1);
        }
        chain[n].insert_gen(gen);
    }

    kmn ans; ans.a[0] = 1;

    for (int i = 1; i <= n; i++)
        ans *= chain[i].orbsz;
    ans.output();
}
