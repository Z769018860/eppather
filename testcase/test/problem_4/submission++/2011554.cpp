#include <cstdio>
using namespace std;

const char s[] = R"(#include <cstdio>
using namespace std;

const char s[] = R"(%s)%c;

int main() {
    printf(s, s, char(34));
    return 0;
}
)";

int main() {
    printf(s, s, char(34));
    return 0;
}
