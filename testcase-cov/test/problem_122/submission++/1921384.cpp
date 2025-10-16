#include <bits/stdc++.h>
#define fastio std::cin.tie(0) -> sync_with_stdio(0) 
#if defined(BACKLIGHT) && !defined(NASSERT)
#define ASSERT(x)                                                          \
  ((x) || (fprintf(stderr, "assertion failed (" __FILE__ ":%d): \"%s\"\n", \
                   __LINE__, #x),                                          \
           assert(false), false))
#else
#define ASSERT(x) ;
#endif

#define unordered 0

struct EulerTour{
	static std::mt19937 rng_;
	struct Node{
		size_t size, num_vertex, num_edge, priority;
		Node *left, *right, *parent;
		size_t from, to;
        Node* tag[2];
        #if unordered
        std::unordered_set<int> edges[2];
        #else
        std::set<int> edges[2];
        #endif
		Node()=delete;
		Node(int from, int to):size(1), num_vertex(from==to?1:0), num_edge(from==to?0:1), 
                               priority(rng_()), left(nullptr),
							   right(nullptr), parent(nullptr), from(from), to(to)
							   {
								   
								   
                                   tag[0] = nullptr;
                                   tag[1] = nullptr;
							   }
		
		void Maintain(){
			size = 1;
			num_vertex = (from == to);
			num_edge = !(from == to);
			if(left){
				size += left->size;
				left->parent = this;
				num_vertex += left->num_vertex;
				num_edge += left->num_edge;
			}
			if(right){
				size += right->size;
				right->parent = this;
				num_vertex += right->num_vertex;
				num_edge += right->num_edge;
			}
            for(int i = 0; i <= 1; ++i){
                if(!edges[i].empty()){
                    assert(from == to);
                    tag[i] = this;
                }else if(left && left->tag[i]){
                    tag[i] = left->tag[i];
                }else if(right && right->tag[i]){
                    tag[i] = right->tag[i];
                }else{
                    tag[i] = nullptr;
                }
            }
		}
	};
	
	static size_t GetSize(Node* p){
		return p ? p->size : 0;
	}

    static size_t GetVerticesNum(Node* p){
        return p ? p -> num_vertex : 0;
    }
	
	static Node* Root(Node* p){
		if(!p) return nullptr;
		while(p->parent != nullptr) {
			p = p->parent;
		}
		return p;
	}
	
	Node* AllocateNode(int u, int v){
		return new (std::nothrow) Node(u, v);
	}
	
	void Free(Node** p){
		if(p && *p){
			delete *p;
			*p = nullptr;
		}
	}
	
	struct Treap{
		
		static Node* Merge(Node* a, Node* b){
			if(!a) return b;
			if(!b) return a;
			if(a->priority < b->priority){
				a->right = Merge(a->right, b);
				a->Maintain();
				return a;
			}else{
				b->left = Merge(a, b->left);
				b->Maintain();
				return b;
			}
			return nullptr;
		}
		
		static int GetPosition(Node* p){
			if(!p) return -1;
			int pos = GetSize(p->left)+1;
			while(p){
				if(p->parent && p == p->parent->right){
					pos += GetSize(p->parent->left)+1;
				}
				p = p->parent;
			}
			return pos;
		}
		
		
		static std::pair<Node*, Node*> SplitUp2(Node* p){
			if(!p) return {nullptr, nullptr};
			Node* a = nullptr, *b = nullptr;
			b = p->right;
			if(b) b->parent = nullptr;
			p->right = nullptr;
			
			bool is_p_left_child_of_parent = false;
			bool from_left_child = false;
			while(p){
				Node* parent = p->parent;
				if(parent){
					is_p_left_child_of_parent = (parent->left == p);
					if (is_p_left_child_of_parent) {
						parent->left = nullptr;
					}else{
						parent->right = nullptr;
					}
					p->parent = nullptr;
				}
				
				if(!from_left_child){
					a = Merge(p, a);
				}else{
					b = Merge(b, p);
				}
				from_left_child = is_p_left_child_of_parent;
				p -> Maintain();
				p = parent;
			}
			return {a, b};
		}
		
		static std::tuple<Node*, Node*, Node*> SplitUp3(Node* p){
			if(!p) return {nullptr, nullptr, nullptr};
			Node* a = p->left;
			if(a) a->parent = nullptr;
			p->left = nullptr;
			Node* b = p->right;
			if(b) b->parent = nullptr;
			p->right = nullptr;
			Node* c = p;
			bool is_p_left_child_of_parent = false;
			bool from_left_child = false;
			Node* parent = p->parent;
			if(parent){
				is_p_left_child_of_parent = (parent->left == p);
				if(is_p_left_child_of_parent) { 
					parent->left = nullptr; 
				}else {
					parent->right = nullptr;
				}
				p -> parent = nullptr;
			}
			from_left_child = is_p_left_child_of_parent;
			p->Maintain();
			p = parent;
			
			while(p){
				Node* parent = p->parent;
				if(parent){
					is_p_left_child_of_parent = (parent->left == p);
					if(is_p_left_child_of_parent) {
						parent->left = nullptr;
					}else {
						parent->right = nullptr;
					}
					p->parent = nullptr;
				}
				
				if(!from_left_child) {
					a = Merge(p, a);
				}else{
					b = Merge(b, p);
				}
				from_left_child = is_p_left_child_of_parent;
				p->Maintain();
				p = parent;
			}
			
			return {a, c, b};
		}
	};
	
	int n;
	std::vector<Node*> vertices;
    #if unordered
    std::vector<std::unordered_map<int, Node*>> tree_edges;
    #else
	std::vector<std::map<int, Node*>> tree_edges;
    #endif
	
	EulerTour(int n){
		ASSERT(n > 0);
		Allocate(n);
	}
	
	EulerTour(){}
	~EulerTour(){ clear(); }
	
	void clear(){
		for(int i = 0; i < (int)tree_edges.size(); ++i){
			for(auto [_, e]: tree_edges[i]){
				Free(&e);
			}
		}
		
		for(int i = 0; i < (int)vertices.size(); ++i){
			Free(&vertices[i]);
		}
		tree_edges.clear();
		vertices.clear();
	}
	
	void Allocate(){
		for (int i = 0; i <= n; ++i) vertices[i] = AllocateNode(i, i);
	}
	
	void Allocate(int n){
		clear();
		this->n = n;
		vertices.resize(n+1);
		tree_edges.resize(n+1);
		Allocate();
	}
	
	int Insert(int u, int v){
		if(tree_edges[u].count(v)) return 1;
		if(tree_edges[v].count(u)) return 2;
		Node* vertex_u = vertices[u];
		Node* vertex_v = vertices[v];
		Node* edge_uv = AllocateNode(u, v);
		Node* edge_vu = AllocateNode(v, u);
		tree_edges[u][v] = edge_uv;
		tree_edges[v][u] = edge_vu;
		auto [L11, L12] = Treap::SplitUp2(vertex_u);
		auto [L21, L22] = Treap::SplitUp2(vertex_v);
		Node* result = nullptr;
		result = Treap::Merge(result, L12);
		result = Treap::Merge(result, L11);
		result = Treap::Merge(result, edge_uv);
		result = Treap::Merge(result, L22);
		result = Treap::Merge(result, L21);
		result = Treap::Merge(result, edge_vu);
		return 0;
	}
	
	int Delete(int u, int v){
		if(!tree_edges[u].count(v)) return 1;
		if(!tree_edges[v].count(u)) return 2;
		Node* edge_uv = tree_edges[u][v];
		Node* edge_vu = tree_edges[v][u];
		tree_edges[u].erase(v);
		tree_edges[v].erase(u);
		
		int position_uv = Treap::GetPosition(edge_uv);
		int position_vu = Treap::GetPosition(edge_vu);
		if (position_uv > position_vu) {
		    std::swap(edge_uv, edge_vu);
		    std::swap(position_uv, position_vu);
		}
		auto [L1, uv, _] = Treap::SplitUp3(edge_uv);
		auto [L2, vu, L3] = Treap::SplitUp3(edge_vu);
		L1 = Treap::Merge(L1, L3);
		Free(&edge_uv);
		Free(&edge_vu);
		return 0;
	}
	
	bool Connected(int u, int v){
		if(!vertices[u] || !vertices[v]){
			return false;
		}
		return Root(vertices[u]) == Root(vertices[v]);
	}

    Node* Root(int u){
        if(u < 1 || u > n) return nullptr;
        return Root(vertices[u]);
    }
	
	std::string str(bool verbose=false) const {
		std::stringstream ss;
		ss << "DynamicForest [\n";
		std::function<void(Node*)> dfs = [&](Node* p) {
			if (!p) return;
			dfs(p->left);
			ss << "(" << p->from << "," << p->to;
			if(verbose) ss << "," << p << "[p]," << p->parent << "[parent]," << p->left << "[left]," << p->right << "[right]";
			ss << "), ";
			dfs(p->right);
		};
		
		for (int i = 0; i < n; ++i) {
			if (vertices[i]->parent == nullptr) {
				ss << "  Component [ root:(" << i << "," << i << ")\n";
				dfs(vertices[i]);
				ss << "]\n";
			}
		}
		for (int i = 0; i < n; ++i) {
			for (auto [_, j] : tree_edges[i]) {
				if (j->parent == nullptr) {
				  ss << "  Component [ root:(" << j->from << "," << j->to << ")\n";
				  dfs(j);
				  ss << "]\n";
				}
			}
		}
		ss << "]\n\n";
		return ss.str();
	}

    void update_tag(int tagid, Node* p){
        while(p){
            if(!p->edges[tagid].empty()){
                assert(p->from == p->to);
                p->tag[tagid] = p;
            }else if(p->left && p->left->tag[tagid]){
                p->tag[tagid] = p->left->tag[tagid];
            }else if(p->right && p->right->tag[tagid]){
                p->tag[tagid] = p->right->tag[tagid];
            }else{
                p->tag[tagid] = nullptr;
            }
            
            assert(p != p->parent);
            p = p -> parent;
        }
    }

    void delete_directed_edge(int tagid, int x, int y){
        if(x < 1 || x > n) return;
        Node* p = vertices[x];
        p->edges[tagid].erase(y);
        if(p->edges[tagid].empty()){
            update_tag(tagid, p);
        }
    }

    void add_directed_edge(int tagid, int x, int y){
        if(x < 1 || x > n) return;
        Node* p = vertices[x];
        p->edges[tagid].insert(y);
        if(p->edges[tagid].size() == 1){
            update_tag(tagid, p);
        }
    }

    #if unordered
    void take_out_edges(int tagid, int x, std::unordered_set<int>& edges){
    #else
    void take_out_edges(int tagid, int x, std::set<int>& edges){
    #endif
        if(x < 1 || x > n) return;
        Node* p = vertices[x];
        if(p){
            std::swap(edges, p->edges[tagid]);
            update_tag(tagid, p);
            assert(!edges.empty());
        }
    }

    void new_tree_edge(int u, int v){
        add_directed_edge(0, u, v);
        add_directed_edge(0, v, u);
        Insert(u, v);
    }
};

struct DynamicConnectivity {
    static constexpr int TREE = 0, NONTREE = 1;
    int c; 
    std::vector<EulerTour> F;
    #if unordered
    std::unordered_map<int, std::unordered_map<int, int>> level;
    std::vector<std::unordered_set<int>> adj;
    #else
    std::map<int, std::map<int, int>> level;
    std::vector<std::set<int>> adj;
    #endif
    void Init(const int n) {
        c = n;
        for (int i = 0; (1 << i) <= 2*n; ++i)
            F.push_back(EulerTour());
        for (auto &f : F)
            f.Allocate(n);
        adj.resize(n + 2);
    }

    void link(const int x, const int y, const int GUARANTEE_LEGAL=0){
        if(!GUARANTEE_LEGAL){
            if (adj[x].count(y) || adj[y].count(x))
            return;
            adj[x].insert(y);
            adj[y].insert(x);
        }
        level[x][y] = 0;
        level[y][x] = 0;
        if(F[0].Connected(x, y)){
            F[0].add_directed_edge(NONTREE, x, y);
            F[0].add_directed_edge(NONTREE, y, x);
        }else{
            F[0].new_tree_edge(x, y);
        }
    }

    bool reconnect(int x, int y, int l) {
        EulerTour::Node* xroot = F[l].Root(x);
        EulerTour::Node* yroot = F[l].Root(y);
        size_t szx = F[l].GetVerticesNum(xroot);
        size_t szy = F[l].GetVerticesNum(yroot);
        if(szx > szy) {
            std::swap(szx, szy);
            std::swap(xroot, yroot);
            std::swap(x, y);
        }
        while(xroot->tag[TREE]){
            int u = xroot->tag[TREE]->from; 
            #if unordered
            std::unordered_set<int> tmp;
            #else 
            std::set<int> tmp;
            #endif
            F[l].take_out_edges(TREE, u, tmp);
            
            for(int v: tmp){
                
                F[l].delete_directed_edge(TREE, v, u);
                F[l + 1].new_tree_edge(u, v);
                ++level[u][v];
                ++level[v][u];
            }
        }

        while(xroot->tag[NONTREE]){
            int u = xroot->tag[NONTREE]->from; 
            #if unordered
            std::unordered_set<int> tmp;
            #else 
            std::set<int> tmp;
            #endif
            F[l].take_out_edges(NONTREE, u, tmp);
            while(!tmp.empty()){
                int v = *tmp.begin();
                tmp.erase(tmp.begin());
                F[l].delete_directed_edge(NONTREE, v, u);
                if(F[l].Root(v) == yroot){
                    if(!tmp.empty()){
                        std::swap(tmp, F[l].vertices[u] -> edges[NONTREE]);
                        F[l].update_tag(NONTREE, F[l].vertices[u]);
                    }
                    for(int i = 0; i < l; ++i){
                        F[i].Insert(u, v);
                    }
                    assert(!F[l].Connected(u, v));
                    F[l].new_tree_edge(u, v);
                    return true;
                }else {
                    F[l + 1].add_directed_edge(NONTREE, u, v);
                    F[l + 1].add_directed_edge(NONTREE, v, u);
                    ++level[u][v];
                    ++level[v][u];
                }
            }
        }

        return false;
    }

    void cut(int x, int y, int GUARANTEE_LEGAL=0) {
        auto it1 = level[x].find(y);
        if(!GUARANTEE_LEGAL){
            if (!adj[x].count(y) || !adj[y].count(x) || it1 == level[x].end())
                return;

            adj[x].erase(y);
            adj[y].erase(x);
        }
        int l = it1->second;
        level[x].erase(it1);
        level[y].erase(x);

        auto &s = F[l].vertices[x]->edges[NONTREE]; 
        if (s.find(y) != s.end()) {
            F[l].delete_directed_edge(NONTREE, x, y);
            F[l].delete_directed_edge(NONTREE, y, x);
            return;
        }

        F[l].delete_directed_edge(TREE, x, y);
        F[l].delete_directed_edge(TREE, y, x);

        for (int i = 0; i <= l; ++i)
            F[i].Delete(x, y);

        bool reconnect_successful = false;
        while(l >= 0){
            if (reconnect(x, y, l)) {
                reconnect_successful = 1;
                break;
            }
            --l;
        }

        if (!reconnect_successful)
            c++;
    }

    bool is_connected(int x, int y) {
        return F[0].Connected(x, y);
    }

    int comp() {
        return c;
    }
};

std::mt19937 EulerTour::rng_(
    std::chrono::steady_clock::now().time_since_epoch().count());

#define DEBUG 0
#define SINGLE 0
#define cstr(x) (luangao(x).c_str())

void debug(const char* p){
    #if DEBUG
    freopen(p, "r", stdin); 
    #else
    fastio;
    #endif      
}

int main(void){
    debug("test1.txt");
	int n, m;
    static DynamicConnectivity dc;

    scanf("%d%d", &n, &m);
    dc.Init(n);
    int last = 0;
    int id = 1;
    while (m--) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        x ^= last;
        y ^= last;

        switch (op) {
        case 0:
            dc.link(x, y, true);
            break;

        case 1:
            dc.cut(x, y, true);
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
        ++id;
    }

    return 0;
}