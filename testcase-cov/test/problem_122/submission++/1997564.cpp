#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <optional>
#include <utility>

namespace dynamic_graph {

using Edge = std::pair<int, int>;

}

template <>
struct std::hash<dynamic_graph::Edge> {
    size_t operator()(const dynamic_graph::Edge& e) const {
        return (static_cast<size_t>(e.first) << 20) | e.second;
    }
};

namespace dynamic_graph {

class DynamicGraph {
    struct Node {
        Node* ch[2];
        Node* up;

        int you, vee;  
        int size;

        
        

        bool hereEdgesBool, subEdgesBool;
        bool hereNodesWithEdgesBool, subNodesWithEdgesBool;

        void Update() {
            if (this != nil) {
                size = 1 + ch[0]->size + ch[1]->size;
                subEdgesBool = hereEdgesBool || ch[0]->subEdgesBool || ch[1]->subEdgesBool;
                subNodesWithEdgesBool = hereNodesWithEdgesBool || ch[0]->subNodesWithEdgesBool ||
                                        ch[1]->subNodesWithEdgesBool;
            }
        }

        static inline int WhichChild(Node* p, Node* v) {
            return p->ch[0] == v ? 0 : 1;
        }

        static inline void SetAsChild(Node* p, Node* v, int dir) {
            p->ch[dir] = v;
            v->up = p;
        }

        static inline void SetAsChildUpdate(Node* p, Node* v, int dir) {
            SetAsChild(p, v, dir);
            p->Update();
        }

        Node* Unlink(int dir) {
            Node* ret = ch[dir];
            ret->up = ch[dir] = nil;
            Update();
            return ret;
        }

        void Rotate() {
            Node* p = up;
            Node* pp = p->up;

            int dir = WhichChild(p, this);

            SetAsChild(p, ch[dir ^ 1], dir);
            
            
            SetAsChild(this, p, dir ^ 1);
            
            

            p->Update();

            SetAsChild(pp, this, WhichChild(pp, p));
            
            
        }

        Node* Splay() {
            if (this == nil) {
                return nil;
            }
            Node* old_root = this;
            while (up != nil) {
                Node* p = up;
                Node* pp = p->up;
                if (pp != nil) {
                    old_root = pp;
                    (WhichChild(pp, p) == WhichChild(p, this) ? p : this)->Rotate();
                } else {
                    old_root = p;
                }
                Rotate();
            }
            Update();
            return old_root;
        }

        
        
        
        
        
        
        
        
        
        
        
        
        
        

        Node()
            : you{-1},
              vee{-1},
              size{0},
              hereEdgesBool{false},
              subEdgesBool{false},
              hereNodesWithEdgesBool{false},
              subNodesWithEdgesBool{false} {
            ch[0] = ch[1] = up = this;
        }

        Node(int you, int vee)
            : you{you},
              vee{vee},
              size{1},
              hereEdgesBool{false},
              subEdgesBool{false},
              hereNodesWithEdgesBool{false},
              subNodesWithEdgesBool{false} {
            ch[0] = ch[1] = up = nil;
        }
    };

    using NonTreeType = std::unordered_map<Edge, std::pair<int, std::list<int>::const_iterator>>;

    struct SpanTree {
        int level;

        std::unordered_map<Edge, Node*> tree_edges_map;
        std::vector<Node*> nodes;

        std::vector<std::list<int>> graph;
        NonTreeType& non_tree;

        SpanTree(int level, int size, NonTreeType& non_tree)
            : level(level), graph(size), non_tree(non_tree) {
            nodes.reserve(size);
            for (int i = 0; i < size; ++i) {
                nodes.push_back(new Node(i, i));
            }
        }

        ~SpanTree() {
            
            for (Node* loop : nodes) {
                delete loop;
            }
            for (auto it : tree_edges_map) {
                delete it.second;
            }
        }

        bool SameComponent(int you, int vee) {
            Node* node_u = nodes[you];
            node_u->Splay();

            
            

            return nodes[vee]->Splay() == node_u;
        }

        void AddNonSpan(int you, int vee) {
            AddNonSpanAux(you, vee);
            AddNonSpanAux(vee, you);
        }

        void AddNonSpanAux(int from, int to) {
            bool was_empty = graph[from].empty();
            graph[from].push_back(to);
            auto it = graph[from].cend();
            --it;

            non_tree[Edge{from, to}] = std::make_pair(level, it);

            if (was_empty) {
                Node* v = nodes[from];
                v->Splay();
                v->hereNodesWithEdgesBool = v->subNodesWithEdgesBool = true;
            }
        }

        void RemoveNonSpan(int from, const std::list<int>::const_iterator& it) {
            graph[from].erase(it);
            if (graph[from].empty()) {
                Node* v = nodes[from];
                v->Splay();
                v->hereNodesWithEdgesBool = false;
                v->Update();
            }
        }

        Node* Reroot(Node* v) {
            v->Splay();
            if (v->ch[0] == nil) {
                return v;
            }

            Node* lft = v->Unlink(0);
            while (lft->ch[0] != nil) {
                lft = lft->ch[0];
            }
            lft->Splay();
            Node::SetAsChildUpdate(lft, v, 0);
            return lft;
        }

        void AddSpan(int you, int vee, bool exact_level) {
            Node* node_u = nodes[you];
            Node* node_v = nodes[vee];

            Node* part_c = Reroot(node_v);

            node_u->Splay();
            Node* part_b = node_u->Unlink(1);

            
            
            
            
            
            
            

            Node* v_to_u = new Node(vee, you);
            Node::SetAsChild(v_to_u, part_c, 0);
            Node::SetAsChild(v_to_u, part_b, 1);
            if (exact_level) {
                v_to_u->hereEdgesBool = true;
            }
            v_to_u->Update();

            Node* u_to_v = new Node(you, vee);
            Node::SetAsChild(u_to_v, node_u, 0);
            Node::SetAsChild(u_to_v, v_to_u, 1);
            if (exact_level) {
                u_to_v->hereEdgesBool = true;
            }
            u_to_v->Update();

            tree_edges_map.insert_or_assign(Edge{you, vee}, u_to_v);
            tree_edges_map.insert_or_assign(Edge{vee, you}, v_to_u);
        }

        void RemoveSpan(int you, int vee) {
            auto u_to_v_it = tree_edges_map.find(Edge{you, vee});
            Reroot(u_to_v_it->second);

            u_to_v_it->second->Splay();
            u_to_v_it->second->Unlink(1);

            delete u_to_v_it->second;
            tree_edges_map.erase(u_to_v_it);

            auto v_to_u_it = tree_edges_map.find(Edge{vee, you});
            v_to_u_it->second->Splay();
            v_to_u_it->second->Unlink(0);
            v_to_u_it->second->Unlink(1);

            delete v_to_u_it->second;
            tree_edges_map.erase(v_to_u_it);
        }

        Node* MoveSpansUp(int you, int vee, SpanTree* next_span) {
            nodes[you]->Splay();
            nodes[vee]->Splay();

            
            
            
            
            
            
            

            Node* cur = nodes[you]->size < nodes[vee]->size ? nodes[you] : nodes[vee];

            
            while (cur->subEdgesBool) {
                while (!cur->hereEdgesBool) {
                    if (cur->ch[0]->subEdgesBool) {
                        cur = cur->ch[0];
                    } else {
                        cur = cur->ch[1];
                    }
                }

                cur->Splay();
                cur->hereEdgesBool = false;
                cur->Update();

                int one = cur->you;
                int two = cur->vee;

                
                if (one < two) {
                    next_span->AddSpan(one, two, true);
                }
            }

            return cur;
        }
    };

    bool RemoveNonSpanWithMaps(int you, int vee) {
        auto non_tree_it = non_tree_.find(Edge{you, vee});
        if (non_tree_it != non_tree_.end()) {
            
            SpanTree& span_tree = spans_[non_tree_it->second.first];
            span_tree.RemoveNonSpan(you, non_tree_it->second.second);
            non_tree_.erase(non_tree_it);

            non_tree_it = non_tree_.find(Edge{vee, you});
            
            span_tree.RemoveNonSpan(vee, non_tree_it->second.second);
            non_tree_.erase(non_tree_it);
            return true;
        }
        return false;
    }

    static Node* nil;

    int components_number_;

    NonTreeType non_tree_;
    std::vector<SpanTree> spans_;

public:
    explicit DynamicGraph(int vertex_count) : components_number_(vertex_count) {
        int log = 0;
        for (int size = vertex_count; size > 0; size /= 2) {
            ++log;
        }
        spans_.reserve(log);
        for (int i = 0; i < log; ++i) {
            spans_.emplace_back(i, vertex_count, non_tree_);
        }
        
    };

    void AddEdge(int you, int vee) {
        if (spans_[0].SameComponent(you, vee)) {
            spans_[0].AddNonSpan(you, vee);
        } else {
            spans_[0].AddSpan(you, vee, true);
            --components_number_;
        }
    };

    void RemoveEdge(int you, int vee) {
        if (RemoveNonSpanWithMaps(you, vee)) {
            return;
        }

        int start_level = spans_.size() - 1;
        for (; start_level >= 0; --start_level) {
            if (spans_[start_level].tree_edges_map.find(Edge{you, vee}) !=
                spans_[start_level].tree_edges_map.end()) {
                break;
            }
        }

        if (start_level < 0) {
            throw std::runtime_error("no edge found");
        }

        std::optional<Edge> replacement;
        for (int level = start_level; level >= 0; --level) {
            spans_[level].RemoveSpan(you, vee);
            bool look_for_replacement = !replacement.has_value();
            if (look_for_replacement) {
                Node* root = spans_[level].MoveSpansUp(
                    you, vee,
                    level + 1 != static_cast<int>(spans_.size()) ? &spans_[level + 1] : nullptr);

                while (root->subNodesWithEdgesBool) {
                    while (!root->hereNodesWithEdgesBool) {
                        if (root->ch[0]->subNodesWithEdgesBool) {
                            root = root->ch[0];
                        } else {
                            root = root->ch[1];
                        }
                    }

                    int node = root->you;
                    int other_side = spans_[level].graph[node].front();

                    
                    RemoveNonSpanWithMaps(node, spans_[level].graph[node].front());

                    if (!spans_[level].SameComponent(node, other_side)) {
                        replacement = Edge{node, other_side};
                        break;
                    } else {
                        spans_[level + 1].AddNonSpan(node, other_side);
                        root->Splay();
                    }
                }
            }

            if (replacement) {
                spans_[level].AddSpan(replacement->first, replacement->second,
                                      look_for_replacement);
            }
        }

        if (!replacement) {
            ++components_number_;
        }
    };

    int GetComponentsNumber() const {
        return components_number_;
    }

    bool IsConnected(int you, int vee) {
        return spans_[0].SameComponent(you, vee);
    }
};

DynamicGraph::Node* DynamicGraph::nil = new DynamicGraph::Node();
}  

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int n, m;

    std::cin >> n >> m;
    dynamic_graph::DynamicGraph g{n};
    int last_ans = 0;

    while (m-- > 0) {
        int t, x, y;
        std::cin >> t >> x >> y;
        x ^= last_ans;
        y ^= last_ans;
        if (t == 0) {
            g.AddEdge(x - 1, y - 1);
        } else if (t == 1) {
            g.RemoveEdge(x - 1, y - 1);
        } else if (t == 2) {
            bool ans = g.IsConnected(x - 1, y - 1);
            if (ans) {
                last_ans = x;
                std::cout << "Y\n";
            } else {
                last_ans = y;
                std::cout << "N\n";
            }
        }
    }

    return 0;
}