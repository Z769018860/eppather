#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

valueType mul(valueType a, valueType b, valueType p) {
    return static_cast<valueType>(static_cast<__int128_t>(a) * static_cast<__int128_t>(b) % static_cast<__int128_t>(p));
}

valueType pow(valueType a, valueType b, valueType p) {
    valueType result = 1;

    while (b > 0) {
        if (b & 1)
            result = mul(result, a, p);

        b >>= 1;
        a = mul(a, a, p);
    }

    return result;
}

bool MillerRabin(valueType n) {
    if (n < 3 || n % 2 == 0)
        return n == 2;

    valueType u = n - 1, t = 0;

    while (u % 2 == 0) {
        ++t;

        u /= 2;
    }

    static ValueVector const A = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (auto a : A) {
        a %= n;

        if (a == 0 || a == 1)
            continue;

        valueType v = pow(a, u, n);

        bool flag = v == 1;
        
        for (valueType s = 0; s < t && !flag; ++s) {
            if (v == n - 1)
                flag = true;

            v = mul(v, v, n);
        }

        if (!flag)
            return false;
    }

    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType x;

    while (std::cin >> x)   
        std::cout << (MillerRabin(x) ? 'Y' : 'N') << '\n';

    std::cout << std::flush;

    return 0;
}