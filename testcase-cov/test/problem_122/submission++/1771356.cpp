#include <iostream>
#include <unordered_set>
#include <stack>
#include <unordered_map>

using namespace std;

#define MAXN 5011
#define MAX_LEVEL 15

struct LCT {
    int c[MAXN][2], fa[MAXN], sta[MAXN];
    bool r[MAXN];
    
    int subtree_size[MAXN], subtree_size2[MAXN];
    struct Tag {
        
        unordered_set<int> edges;
        int tag;
        unordered_set<int> tagged_non_preferred_children;
    } tag_tree[MAXN], tag_non_tree[MAXN];

    void update_tag(Tag tags[], int x) {
        if (!tags[x].edges.empty()) {
            tags[x].tag = x;
        } else if (tags[ls(x)].tag) {
            tags[x].tag = tags[ls(x)].tag;
        } else if (tags[rs(x)].tag) {
            tags[x].tag = tags[rs(x)].tag;
        } else if (!tags[x].tagged_non_preferred_children.empty()) {
            tags[x].tag = tags[*tags[x].tagged_non_preferred_children.begin()].tag;
        } else {
            tags[x].tag = 0;
        }
    }
    void new_non_preferred_child(int x) {
        if (fa[x] == 0)
            return;
        subtree_size2[fa[x]] += subtree_size[x];
        if (tag_tree[x].tag)
            tag_tree[fa[x]].tagged_non_preferred_children.insert(x);
        if (tag_non_tree[x].tag)
            tag_non_tree[fa[x]].tagged_non_preferred_children.insert(x);
    }
    void delete_non_preferred_child(int x) {
        if (fa[x] == 0)
            return;
        subtree_size2[fa[x]] -= subtree_size[x];
        if (tag_tree[x].tag)
            tag_tree[fa[x]].tagged_non_preferred_children.erase(x);
        if (tag_non_tree[x].tag)
            tag_non_tree[fa[x]].tagged_non_preferred_children.erase(x);
    }

    inline int& ls(int rt) {
        return c[rt][0];
    }
    inline int& rs(int rt) {
        return c[rt][1];
    }
    inline bool not_splay_rt(int x) {
        return ls(fa[x]) == x || rs(fa[x]) == x;
    }
    inline int side(int x) {
        return x == rs(fa[x]);
    }
    void Init(int n) {
        
        
        for (int i = 1; i <= n; ++i) {
            subtree_size[i] = 1;
        }
    }
    inline void pushr(int x) {
        swap(ls(x), rs(x));
        r[x] ^= 1;
    }
    inline void pushdown(int x) {
        if (r[x]) {
            if (ls(x))
                pushr(ls(x));
            if (rs(x))
                pushr(rs(x));
            r[x] = false;
        }
    }
    inline void __pushup(int x) {
        update_tag(tag_tree, x);
        update_tag(tag_non_tree, x);
        subtree_size[x] = subtree_size[ls(x)] + subtree_size[rs(x)] + 1 + subtree_size2[x];
    }
    
    inline void __pushup_splay_rt(int x) {
        __pushup(x);
        new_non_preferred_child(x);
        
    }
    
    void __rotate_up(int x) {
        int y = fa[x], z = fa[y], side_x = side(x), w = c[x][side_x ^ 1];
        fa[x] = z;
        if (not_splay_rt(y))
            c[z][side(y)] = x;
        if (w)
            fa[w] = y;
        c[y][side_x] = w;
        fa[y] = x;
        c[x][side_x ^ 1] = y;
        __pushup(y);
    }
    
    
    void __splay(int x) {
        int y = x, top = 0;
        while(1) {
            sta[++top] = y;
            if (!not_splay_rt(y))
                break;
            y = fa[y];
        }
        int to = fa[y];
        delete_non_preferred_child(y);
        while (top)
            pushdown(sta[top--]);
        while (fa[x] != to) {
            int y = fa[x];
            if (fa[y] != to)
                __rotate_up(side(x) == side(y) ? y : x);
            __rotate_up(x);
        }
    }
    void splay(int x) {
        __splay(x);
        __pushup_splay_rt(x);
    }
    void access(int x) {
        int ori_x = x;
        for (int w = 0; x; w = x, x = fa[x]) {
            __splay(x);
            delete_non_preferred_child(w);
            new_non_preferred_child(rs(x));
            rs(x) = w;
            __pushup_splay_rt(x);
        }
        __splay(ori_x);
        __pushup(ori_x);
    }
    int find_root(int x) {
        access(x);
        for (; ls(x); x = ls(x))
            pushdown(x);
        __splay(x);
        __pushup(x);
        return x;
    }
    inline void make_root(int x) {
        access(x);
        pushr(x);
    }
    void __link(int x, int y) {
        
        access(y);
        pushdown(x);
        fa[y] = x;
        ls(x) = y;
        __pushup(x); 
    }
    inline void link_new(int x, int y) {
        make_root(x);
        __link(x, y);
    }
    inline void link(int x, int y) {
        make_root(x);
        if (find_root(y) == x)
            return;
        __link(x, y);
    }
    inline void split(int x, int y) {
        make_root(x);
        access(y);
    }
    void cut_existing(int x, int y) {
        split(x, y);
        fa[x] = ls(y) = 0;
        __pushup(y); 
    }
    void cut(int x, int y) {
        split(x, y);
        if (ls(y) != x || rs(x) != 0)
            return;	
        fa[x] = ls(y) = 0;
        __pushup(y); 
    }
    std::unordered_set<int> take_out_edges(Tag type[], int x) {
        access(x);
        auto tmp = std::unordered_set<int>();
        swap(tmp, type[x].edges);
        update_tag(type, x);
        return std::move(tmp);
    }
    void add_directed_edge(Tag type[], int x, int y) {
        if (type[x].edges.empty()) {
            access(x);
            type[x].edges.insert(y);
            update_tag(type, x);
        } else {
            type[x].edges.insert(y);
        }
    }
    void delete_directed_edge(Tag type[], int x, int y) {
        if (type[x].edges.size() == 1) {
            access(x);
            type[x].edges.erase(y);
            update_tag(type, x);
        } else {
            type[x].edges.erase(y);
        }
    }
    void new_tree_edge(int x, int y) {
        link_new(x, y);
        add_directed_edge(tag_tree, x, y);
        add_directed_edge(tag_tree, y, x);
    }
};

struct DynamicConnectivity {
    struct LCT F[MAX_LEVEL];
    unordered_map<int, unordered_map<int, int> > level;
    void Init(int n) {
        for (int i = 0; (1 << i) <= n; ++i)
            F[i].Init(n);
    }
    
    void link_new(int x, int y) {
        level[x][y] = 0;
        level[y][x] = 0;
        if (F[0].find_root(x) == F[0].find_root(y)) {
            F[0].add_directed_edge(F[0].tag_non_tree, y, x);
            F[0].add_directed_edge(F[0].tag_non_tree, x, y);
        } else {
            F[0].new_tree_edge(x, y);
        }
    }
    bool reconnect(int x, int y, int l) {
        F[l].access(x);
        F[l].access(y);
        if (F[l].subtree_size[x] > F[l].subtree_size[y])
            swap(x, y);
        while (1) {
            F[l].access(x);
            int u = F[l].tag_tree[x].tag;
            if (u == 0)
                break;
            auto tmp = F[l].take_out_edges(F[l].tag_tree, u);
            for (int v : tmp) {
                F[l].delete_directed_edge(F[l].tag_tree, v, u);
                F[l+1].new_tree_edge(u, v);
                ++level[u][v];
                ++level[v][u];
            }
        }

        y = F[l].find_root(y);
        while (1) {
            F[l].access(x);
            int u = F[l].tag_non_tree[x].tag;
            if (u == 0)
                break;
            auto tmp = F[l].take_out_edges(F[l].tag_non_tree, u);
            do {
                auto it = tmp.begin();
                int v = *it;
                tmp.erase(it);
                F[l].delete_directed_edge(F[l].tag_non_tree, v, u);
                if (F[l].find_root(v) == y) {
                    if (!tmp.empty()) {
                        F[l].access(u);
                        swap(tmp, F[l].tag_non_tree[u].edges);
                        F[l].update_tag(F[l].tag_non_tree, u);
                    }
                    for (int i = 0; i < l; ++i)
                        F[i].link_new(u, v);
                    F[l].new_tree_edge(u, v);
                    return true;
                } else {
                    F[l+1].add_directed_edge(F[l+1].tag_non_tree, u, v);
                    F[l+1].add_directed_edge(F[l+1].tag_non_tree, v, u);
                    ++level[u][v];
                    ++level[v][u];
                }
            } while (!tmp.empty());
        };
        return false;
    }
    void cut_existing(int x, int y) {
        auto it1 = level[x].find(y);
        int l = it1->second;
        level[x].erase(it1);
        level[y].erase(x);

        auto& s = F[l].tag_non_tree[x].edges;
        if (s.find(y) != s.end()) {
            F[l].delete_directed_edge(F[l].tag_non_tree, x, y);
            F[l].delete_directed_edge(F[l].tag_non_tree, y, x);
            return;
        }
        F[l].delete_directed_edge(F[l].tag_tree, x, y);
        F[l].delete_directed_edge(F[l].tag_tree, y, x);
        for (int i = 0; i <= l; ++i)
            F[i].cut_existing(x, y);
        while (true) {
            if (reconnect(x, y, l))
                break;
            if (l == 0)
                break;
            --l;
        }
    }
    bool is_connected(int x, int y) {
        return F[0].find_root(x) == F[0].find_root(y);
    }
};

int main() {
    int n, m;
    static DynamicConnectivity dc;

    scanf("%d%d", &n, &m);
    dc.Init(n);
    int last = 0;
    while (m--) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        x ^= last;
        y ^= last;
        switch (op) {
            case 0:
                dc.link_new(x, y);
                break;
            case 1:
                dc.cut_existing(x, y);
                break;
            case 2:
                if (dc.is_connected(x, y)) {
                    puts("Y");
                    last = x;
                } else {
                    puts("N");
                    last = y;
                }
                break;
        }
    }

    return 0;
}
