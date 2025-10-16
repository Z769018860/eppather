#include <cstdio>
#include <cassert>
using namespace std;
int n, m, l, d, v;
bool dest() {
    printf("reach_dest\n");
    fflush(NULL);
    scanf("%d", &v);
    return v;
}
void move() {
    printf("move_left\n");
    fflush(NULL);
    scanf("%d", &v);
    assert(v == 1);
}
int main() {
    scanf("%d%d%d%d", &n, &m, &l, &d);

    while (!dest())
        move();

    return 0;
}