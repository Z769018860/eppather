#include <cstdio>
#include <cctype>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;
#define MAXN 100005
inline char get_char(){
    static char buf[5000001], *p1 = buf, *p2 = buf + fread(buf, 1, 5000000, stdin);
    return p1 == p2 ? EOF : *p1 ++;
}
inline int read(){
    int num = 0;
    char c, sf = 1;
    while (isspace(c = get_char()));
    if(c == '-') sf = -1, c = get_char();
    while (num = num * 10 + c - 48, isdigit(c = get_char()));
    return num * sf;
}
int father[MAXN];
inline int Get_Father(int u){
    return father[u] == u ? u : father[u] = Get_Father(father[u]);
}
struct Node{
    int v, id;
    Node(int a, int b){
        v = a, id = b;
}

    bool operator < (Node tar) const {
        return v == tar.v ? id > tar.id : v > tar.v;
    }
};
typedef __gnu_pbds::priority_queue<Node, less<Node>, pairing_heap_tag> Heap;
Heap stl_heap[MAXN];
Heap::iterator itx, ity;
bool del[MAXN];
int main(){
    int n = read(), m = read();
    for(int i = 1; i <= n; i++){
        Node data(read(), i);
        father[i] = i;
        stl_heap[i].push(data);
    }
    for(int i = 1; i <= m; i++){
        int cons = read();
        if(cons & 1){
            int x = read(), y = read(), fx = Get_Father(x), fy = Get_Father(y);
            if(fx == fy || del[x] || del[y]) continue;
            stl_heap[fx].join(stl_heap[fy]);
            father[fy] = fx;
        } else {
            int x = read(), fx = Get_Father(x);
            if(del[x] || stl_heap[fx].empty()) puts("-1");
            else {
                Node data = stl_heap[fx].top();
                stl_heap[fx].pop();
                del[data.id] = true;
                printf("%d\n", data.v);
            }
        }
    }
    return 0;
}
