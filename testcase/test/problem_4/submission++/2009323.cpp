#include <cstdio>
using namespace std;

constexpr char str[] = R"(#include <cstdio>
using namespace std;

constexpr char str[] = R"(%s)%c;

int main()
{
    printf(str, str, 34);
    return 0;
})";

int main()
{
    printf(str, str, 34);
    return 0;
}