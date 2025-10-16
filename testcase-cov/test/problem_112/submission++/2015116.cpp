#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

class TreeArray {
private:
    valueType N, nowTime;
    ValueVector Data, Time;

    static valueType LowBit(valueType n) {
        return n & (-n);
    }
public:
    TreeArray() = default;

    explicit TreeArray(valueType n) : N(n), nowTime(0), Data(N + 1, 0), Time(N + 1, 0) {}

public:
    void Insert(valueType x, valueType v) {
        while (x <= N) {
            if (Time[x] != nowTime) {
                Data[x] = 0;

                Time[x] = nowTime;
            }

            Data[x] += v;

            x += LowBit(x);
        }
    }

    valueType Query(valueType x) {
        if (x < 1)
            return 0;

        valueType result = 0;

        while (x >= 1) {
            if (Time[x] != nowTime) {
                Data[x] = 0;

                Time[x] = nowTime;
            }

            result += Data[x];

            x -= LowBit(x);
        }

        return result;
    }

    void Clear() {
        ++nowTime;
    }
};

struct Element {
    valueType a, b, c;
    valueType count, result;

    Element() = default;

    Element(valueType a, valueType b, valueType c,valueType count = 1) : a(a), b(b), c(c), count(count), result(0) {}

    friend bool operator==(Element const &X, Element const &Y) {
        return X.a == Y.a && X.b == Y.b && X.c == Y.c;
    }

    friend bool operator!=(Element const &X, Element const &Y) {
        return X.a != Y.a || X.b != Y.b || X.c != Y.c;
    }
};

bool CompareA(Element const &X, Element const &Y) {
    if (X.a != Y.a)
        return X.a < Y.a;
    
    if (X.b != Y.b)
        return X.b < Y.b;

    return X.c < Y.c;
}

bool CompareB(Element const &X, Element const &Y) {
    if (X.b != Y.b)
        return X.b < Y.b;

    return X.c < Y.c;
}

valueType N, K;
std::vector<Element> Item;
TreeArray tree;

void Solve(valueType l, valueType r) {
    if(l == r)
        return;

    valueType const mid = (l + r) >> 1;

    Solve(l, mid);
    Solve(mid + 1, r);

    std::sort(Item.begin() + l, Item.begin() + r + 1, CompareA);
    std::sort(Item.begin() + l, Item.begin() + mid + 1, CompareB);
    std::sort(Item.begin() + mid + 1, Item.begin() + r + 1, CompareB);

    tree.Clear();

    valueType LeftPointer = l - 1;

    for (valueType i = mid + 1; i <= r; ++i) {
        while (LeftPointer + 1 <= mid && Item[LeftPointer + 1].b <= Item[i].b) {
            ++LeftPointer;

            tree.Insert(Item[LeftPointer].c, Item[LeftPointer].count);
        }

        Item[i].result += tree.Query(Item[i].c);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> N >> K;

    tree = TreeArray(K);

    std::vector<Element> A(N);

    for (valueType i = 0; i < N; ++i) {
        std::cin >> A[i].a >> A[i].b >> A[i].c;

        A[i].count = 1;
    }

    std::sort(A.begin(), A.end(), CompareA);

    for (valueType i = 0; i < N; ++i) {
        if (Item.empty() || A[i] != Item.back())
            Item.push_back(A[i]);
        else
            ++Item.back().count;
    }

    Solve(0, Item.size() - 1);

    ValueVector Ans(N, 0);

    for (valueType i = 0; i < Item.size(); ++i)
        Ans[Item[i].result + Item[i].count - 1] += Item[i].count;

    for (valueType i = 0; i < N; ++i)
        std::cout << Ans[i] << '\n';
    
    std::cout << std::flush;

    return 0;
}