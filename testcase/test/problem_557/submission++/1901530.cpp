#include<bits/stdc++.h>
using namespace std;
#define MAXN 400005
int n, m, a[MAXN], tot;
struct FHQ{
    int dat[MAXN], L[MAXN], R[MAXN], siz[MAXN], tot;
    int ls[MAXN], rs[MAXN];
    int rt[MAXN], x, y, z;
    queue<int> q;

    int new_node(int l, int r){
        int now;
        if(!q.empty()) now = q.front(), q.pop();
        else now = ++tot;
        dat[now] = rand(), L[now] = l, R[now] = r, siz[now] = r-l+1;
        return now;
    }

    void push_up(int p){
        siz[p] = siz[ls[p]] + siz[rs[p]] + R[p] - L[p] + 1;
    }

    int merge(int x, int y){
        if(!x || !y) return x + y;
        if(dat[x] < dat[y]){
            rs[x] = merge(rs[x], y);
            push_up(x);
            return x;
        }else{
            ls[y] = merge(x, ls[y]);
            push_up(y);
            return y;
        }
    }

    void split(int now, int k, int& x, int& y){
        if(!now) {x = y = 0; return;}
        if(L[now] <= k){
            x = now;
            split(rs[x], k, rs[x], y);
        }else{
            y = now;
            split(ls[y], k, x, ls[y]);
        }
        push_up(now);
    }

    void insert(int idx, int l, int r){
        split(rt[idx], l, x, y);
        rt[idx] = merge(x, merge(new_node(l, r), y));
    }

    void del(int idx, int l){
        split(rt[idx], l-1, x, y);
        split(y, l, y, z);
        q.push(y);
        rt[idx] = merge(x, z);
    }

    int query(int idx, int l, int r, int k){
        split(rt[idx], l-1, x, y);
        int now = y;
        if(siz[now] < k) return rt[idx] = merge(x, y), 0;
        while(true){
            if(k > siz[now] - siz[rs[now]]) k -= siz[now] - siz[rs[now]], now = rs[now];
            else if(k > siz[ls[now]]){
                k -= siz[ls[now]];
                int ret = (L[now] + k - 1 > r) ? 0 : (L[now] + k - 1);
                rt[idx] = merge(x, y);
                return ret;
            }else now = ls[now];
        }
    }
} tr;
#define IT map<pair<int, int>, int>::iterator
map<int, int> mp;
map<pair<int, int>, int> s;
void ins(int l, int r, int idx){
    s.insert({make_pair(l, r), idx});
    tr.insert(idx, l, r);
}
void del(int l, int r, int idx){
    s.erase(s.find(make_pair(l, r)));
    tr.del(idx, l);
}
struct Node{
    int l, r, x;
    Node(){}
    Node(int _l, int _r, int _x){l = _l, r = _r, x = _x;}
};
int main(){
    srand(time(0));
    cin>>n>>m;
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    int cnt = 1, last = a[1];
    for(int i=2;i<=n;i++){
        if(a[i] == last) cnt++;
        else {
            int& idx = mp[last];
            if(!idx) idx = ++tot;
            ins(i-cnt, i-1, idx), cnt = 1, last = a[i];
        }
    } 
    {int& idx = mp[last];
    if(!idx) idx = ++tot;
    ins(n-cnt+1, n, idx);}
    int l, r, k, x;
    char op[5];
    int lastans = 0;
    for(int i=1;i<=m;i++){
        scanf("%s%d%d", op, &l, &r);
        l ^= lastans, r ^= lastans;
        if(op[0] == 'M'){
            scanf("%d", &x);
            x ^= lastans;
            int& idx = mp[x];
            if(!idx) idx = ++tot;
            vector<Node> v;
            IT it = s.lower_bound(make_pair(l, 0));
            if(it->first.first != l) --it;
            while(it != s.end() && it->first.first <= r) v.push_back(Node(it->first.first, it->first.second, it->second)), ++it;
            for(auto p : v){
                del(p.l, p.r, p.x);
                if(p.l < l) ins(p.l, l-1, p.x);
                if(p.r > r) ins(r+1, p.r, p.x);
            }
            ins(l, r, idx);
        }else{
            scanf("%d%d", &k, &x);
            k ^= lastans, x ^= lastans;
            if(!mp.count(x)) {lastans = 0, puts("0"); continue;}
            int idx = mp[x];
            IT it = s.lower_bound(make_pair(l, 0));
            if(it->first.first != l){
                --it;
                int L = it->first.first, R = it->first.second;
                if(it->second == idx) del(L, R, idx), ins(L, l-1, idx), ins(l, R, idx);
            }
            printf("%d\n", lastans = tr.query(idx, l, r, k));
        }
    }
    return 0;
}