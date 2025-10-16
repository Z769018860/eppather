#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define flt double
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

mt19937 rnd(2342);

struct SGT {
    int n;
    vector<int> t;

    void build(int _n) {
        n = 1;
        while (n < _n) {
            n *= 2;
        }
        t.assign(n + n, 0);
    }

    void add(int i, int x) {
        i += n;
        for (; i > 0; i /= 2) {
            t[i] += x;
        }
    }

    int get(int l, int r) {
        l += n;
        r += n;
        int rs = 0;
        while (l < r) {
            if (l & 1) {
                rs += t[l];
                l += 1;
            }
            if (r & 1) {
                r -= 1;
                rs += t[r];
            }
            l /= 2;
            r /= 2;
        }
        return rs;
    }
};

template <class T>
void print(const vector<T> &a, T k = 0) {
    for (int i = 0; i < (int)a.size(); i += 1) {
        cout << a[i] + k << " ";
    }
    cout << "\n";
}

vector<int> flex_slow(const vector<int> &a, const vector<int> &b) {
    int n = (int)a.size();
    vector<vector<int>> x(n + 1, vector<int>(n + 1)), y(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i += 1) {
        x[i][a[i] + 1] = 1;
        y[i][b[i] + 1] = 1;
    }
    for (int i = 0; i <= n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            x[i][j] += x[i][j - 1];
            y[i][j] += y[i][j - 1];
        }
    }
    for (int i = n - 1; i >= 0; i -= 1) {
        for (int j = 0; j <= n; j += 1) {
            x[i][j] += x[i + 1][j];
            y[i][j] += y[i + 1][j];
        }
    }
    vector<vector<int>> z(n + 1, vector<int>(n + 1, n * 2 + 10));
    for (int i = 0; i <= n; i += 1) {
        for (int j = 0; j <= n; j += 1) {
            for (int k = 0; k <= n; k += 1) {
                z[i][k] = min(z[i][k], x[i][j] + y[j][k]);
            }
        }
    }
    for (int i = 0; i <= n; i += 1) {
        
    }
    vector<int> c(n);
    for (int i = 0; i < n; i += 1) {
        for (int j = 1; j <= n; j += 1) {
            if (z[i][j] + z[i + 1][j - 1] - z[i + 1][j] - z[i][j - 1] == 1) {
                c[i] = j - 1;
            }
        }
    }
    return c;
}

vector<int> flex(const vector<int> &a, const vector<int> &b) {
    int n = a.size();
    if (n == 1) {
        return {0};
    }
    if (n == 0) {
        return {};
    }
    vector<int> ra(n), rb(n);
    for (int i = 0; i < n; i += 1) {
        ra[a[i]] = i;
        rb[b[i]] = i;
    }
    int s = n / 2;
    int t = n - s;
    vector<int> xlo(s), ylo(s), xhi(t), yhi(t);
    vector<int> alo(s), blo(s), ahi(t), bhi(t);
    int j1 = 0;
    int j2 = 0;
    for (int i = 0; i < n; i += 1) {
        if (a[i] < s) {
            xlo[j1] = i;
            alo[j1] = a[i];
            j1 += 1;
        } else {
            xhi[j2] = i;
            ahi[j2] = a[i] - s;
            j2 += 1;
        }
    }
    j1 = 0;
    j2 = 0;
    for (int i = 0; i < n; i += 1) {
        if (rb[i] < s) {
            ylo[j1] = i;
            blo[rb[i]] = j1;
            j1 += 1;
        } else {
            yhi[j2] = i;
            bhi[rb[i] - s] = j2;
            j2 += 1;
        }
    }
    auto _clo = flex(alo, blo);
    auto _chi = flex(ahi, bhi);
    vector<int> clo(n, -1), rclo(n, -1), chi(n, -1), rchi(n, -1);
    for (int i = 0; i < s; i += 1) {
        clo[xlo[i]] = ylo[_clo[i]];
        rclo[ylo[_clo[i]]] = xlo[i];
    }
    for (int i = 0; i < t; i += 1) {
        chi[xhi[i]] = yhi[_chi[i]];
        rchi[yhi[_chi[i]]] = xhi[i];
    }
    vector<int> c(n, -1);
    vector<int> line(n + 1, n);
    auto go_left = [&](int &i, int &k, int &mlo, int &mhi) {
        if (rclo[k - 1] != -1) {
            if (rclo[k - 1] >= i) {
                mlo -= 1;
            }
        } else {
            mlo -= 1;
            if (rchi[k - 1] >= i) {
                mhi -= 1;
            }
        }
        k -= 1;
    };
    auto go_down = [&](int &i, int &k, int &mlo, int &mhi) {
        if (clo[i] != -1) {
            mhi -= 1;
            if (clo[i] < k) {
                mlo -= 1;
            }
        } else {
            if (chi[i] < k) {
                mhi -= 1;
            }
        }
        i += 1;
    };
    auto go_right = [&](int &i, int &k, int &mlo, int &mhi) {
        if (rclo[k] != -1) {
            if (rclo[k] >= i) {
                mlo += 1;
            }
        } else {
            mhi += 1;
            if (rchi[k] >= i) {
                mlo += 1;
            }
        }
        k += 1;
    };
    auto go_up = [&](int &i, int &k, int &mlo, int &mhi) {
        if (clo[i - 1] != -1) {
            mhi += 1;
            if (clo[i - 1] < k) {
                mlo += 1;
            }
        } else {
            if (chi[i - 1] < k) {
                mhi += 1;
            }
        }
        i -= 1;
    };
    auto check = [&](int i, int k, int mlo, int mhi) {
        int rs = min(mlo, mhi);
        go_down(i, k, mlo, mhi);
        rs -= min(mlo, mhi);
        go_left(i, k, mlo, mhi);
        rs += min(mlo, mhi);
        go_up(i, k, mlo, mhi);
        rs -= min(mlo, mhi);
        if (rs) {
            c[i] = k;
        }
    };
    int i = 0;
    int k = n;
    int mlo = n;
    int mhi = n;
    for (;;) {
        while (k > 0 && mlo > mhi) {
            if (i >= 0) {
                int i1 = i, k1 = k, mlo1 = mlo, mhi1 = mhi;
                go_up(i1, k1, mlo1, mhi1);
                check(i1, k1, mlo1, mhi1);
            }
            go_left(i, k, mlo, mhi);
        }
        line[i] = k;
        if (i == n) {
            break;
        }
        if (k < n) {
            int i1 = i, k1 = k, mlo1 = mlo, mhi1 = mhi;
            go_right(i1, k1, mlo1, mhi1);
            check(i1, k1, mlo1, mhi1);
        }
        go_down(i, k, mlo, mhi);
    }
    for (int i = 0; i < n; i += 1) {
        if (clo[i] != -1) {
            int k = clo[i] + 1;
            if (line[i + 1] >= k) {
                c[i] = k - 1;
            }
        } else {
            int k = chi[i] + 1;
            if (line[i] < k - 1) {
                c[i] = k - 1;
            }
        }
    }
    return c;
}

void stress_flex(int maxn = 10) {
    int c = 0;
    while (1) {
        cout << ++c << "\n";
        int n = rnd() % maxn + 1;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i += 1) {
            a[i] = i;
            b[i] = i;
        }
        shuffle(all(a), rnd);
        shuffle(all(b), rnd);
        auto right_rs = flex_slow(a, b);
        auto my_rs = flex(a, b);
        if (right_rs != my_rs) {
            print(a);
            print(b);
            cout << "Right result:"
                 << "\n";
            print(right_rs);
            cout << "My result:"
                 << "\n";
            print(my_rs);
            break;
        }
    }
}

vector<int> get_super_permutation_rec(const vector<int> &a) {
    int n = (int)a.size();
    if (n == 0) {
        return {};
    }
    if (n == 1) {
        return {0, 1};
    }
    int s = n / 2;
    int t = n - s;
    vector<int> alo(s), ahi(t);
    vector<int> indxlo(s), indxhi(t);
    int j1 = 0;
    int j2 = 0;
    for (int i = 0; i < n; i += 1) {
        if (a[i] < s) {
            alo[j1] = a[i];
            indxlo[j1] = i;
            j1 += 1;
        } else {
            ahi[j2] = a[i] - s;
            indxhi[j2] = i;
            j2 += 1;
        }
    }
    auto _plo = get_super_permutation_rec(alo);
    auto _phi = get_super_permutation_rec(ahi);
    int s2 = s + s;
    int t2 = t + t;
    int n2 = n + n;
    vector<int> xlo(s2), ylo(s2), xhi(t2), yhi(t2);
    for (int i = 0; i < s2; i += 1) {
        if (i < s) {
            xlo[i] = i + t;
        } else {
            xlo[i] = indxlo[i - s] + n;
        }
        if (i < s) {
            ylo[i] = indxlo[i] + t;
        } else {
            ylo[i] = n + i;
        }
    }
    for (int i = 0; i < t2; i += 1) {
        if (i < t) {
            xhi[i] = i;
        } else {
            xhi[i] = indxhi[i - t] + t;
        }
        if (i < t) {
            yhi[i] = indxhi[i];
        } else {
            yhi[i] = n + (i - t);
        }
    }
    vector<int> plo(n2);
    vector<int> phi(n2);
    for (int i = 0; i < n2; i += 1) {
        if (i < t) {
            plo[i] = i;
        } else if (i < n) {
            plo[i] = i + n + t;
        } else {
            plo[i] = i - s;
        }
        if (i < t) {
            phi[i] = i + n;
        } else if (i < n + t) {
            phi[i] = i - t;
        } else {
            phi[i] = i;
        }
    }
    for (int i = 0; i < s2; i += 1) {
        plo[xlo[i]] = ylo[_plo[i]];
    }
    for (int i = 0; i < t2; i += 1) {
        phi[xhi[i]] = yhi[_phi[i]];
    }
    return flex(plo, phi);
}

vector<int> get_super_permutation(const vector<int> &a) {
    
        vector<int> p = get_super_permutation_rec(a);
    return p;
}

int32_t main() {
    
    if (0) {
        ios::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
    }
    if (0) {
        vector<int> a = {1, 0, 2};
        vector<int> b = {0, 2, 1};
        print(flex(a, b));
    }
    if (0) {
        vector<int> a = {1, 0};
        vector<int> p = get_super_permutation(a);
        print(p);
    }

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i += 1) {
        cin >> a[i];
        --a[i];
    }
    for (int i = 0; i < n; i += 1) {
        cin >> b[i];
        --b[i];
    }
    print(flex(a, b), 1);
    }