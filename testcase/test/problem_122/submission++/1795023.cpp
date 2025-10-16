
#define DROP
#ifdef ONLINE
#undef LOCAL
#endif
#ifndef LOCAL
#undef _GLIBCXX_DEBUG
#undef _DEBUG
#endif
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <fstream>

#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <type_traits>
#include <chrono>
#include <random>
#include <complex>
#include <bitset>
#include <set>
#include <list>
#include <array>

template <class T, int S>
struct MDVecDef {
  using Type = std::vector<typename MDVecDef<T, S - 1>::Type>;
  template <typename... Args>
  static Type Make(int n, Args... args) {
    return Type(n, MDVecDef<T, S - 1>::Make(args...));
  }
};
template <class T>
struct MDVecDef<T, 0> {
  using Type = T;
  static Type Make(T val = T()) { return val; }
};
template <class T, int S = 1>
using MDVec = typename MDVecDef<T, S>::Type;
#ifndef M_PI
#define M_PI 3.14159265358979323851280895940618620443274267017841L
#endif
#ifndef M_E
#define M_E 2.718281828459045235428168107993940338928950950503355L
#endif
#ifdef LOCAL
#define Assert(x) assert(x)
#define DebugRun(X) X
#define DebugPoint int _x_ = 0; _x_++;
#else
#define Debug(...) 42
#define DebugFmtln(...) 42
#define Assert(x) 42
#define DebugRun(X)
#define DebugPoint
#endif
#define Trace(x) DebugFmtln("Line %d: %s", __LINE__, #x)
template<class T>
inline T DebugRet(T x) {
    Debug(x);
    return x;
}
#define const_ref(T) const T &
#define mut_ref(T) T &
#define let auto
#define var auto
#define MEMSET0(X) std::memset(&X, 0, sizeof(X)) 
#define Size(T) int((T).size())
#define All(data) data.begin(), data.end()
#define MakeUnique(data) data.resize(std::unique(All(data)) - data.begin())
#define MakeUniqueAndSort(data) Sort(All(data)); MakeUnique(data) 
#define MakeAttribute(struct_name, Type, attr_name)               \
  struct struct_name {                                            \
    using attr_name ## _type = Type;                              \
    Type attr_name;                                               \
    mut_ref(Type) get_##attr_name() { return attr_name; }         \
    const_ref(Type) get_##attr_name() const { return attr_name; } \
  };
#define MakeTemplateAttribute(struct_name, attr_name)          \
  template <class T>                                           \
  struct struct_name {                                         \
    using attr_name##_type = T;                             \
    T attr_name;                                               \
    mut_ref(T) get_##attr_name() { return attr_name; }         \
    const_ref(T) get_##attr_name() const { return attr_name; } \
  };
#define ImplDefaultEq(name)                        \
  bool operator==(const name &a, const name &b) {  \
    return std::memcmp(&a, &b, sizeof(name)) == 0; \
  }                                                \
  bool operator!=(const name &a, const name &b) { return !(a == b); }
#define ImplDefaultComparision(name)                                \
  bool operator>(const name &rhs) const { return rhs < *this; }     \
  bool operator<=(const name &rhs) const { return !(*this > rhs); } \
  bool operator>=(const name &rhs) const { return !(*this < rhs); }
#define ImplArithmeticAssignOperation(name)                                 \
  name &operator+=(const name &rhs) { return *this = (*this) + rhs; } \
  name &operator-=(const name &rhs) { return *this = (*this) - rhs; } \
  name &operator*=(const name &rhs) { return *this = (*this) * rhs; } \
  name &operator/=(const name &rhs) { return *this = (*this) / rhs; }
#define IsType(Type, param, ret_type)                                        \
  template <typename OnlyWhenArg = param>                                    \
  enable_if_t<is_same_v<OnlyWhenArg, param> && is_same_v<OnlyWhenArg, Type>, \
              ret_type>
#define IsBool(param, ret_type)       \
  template <bool OnlyWhenArg = param> \
  enable_if_t<OnlyWhenArg == (param) && OnlyWhenArg, ret_type>
#define IsBoolStatic(param, ret_type) \
  template <bool OnlyWhenArg = param> \
  static enable_if_t<OnlyWhenArg == (param) && OnlyWhenArg, ret_type>
#define MakeAnnotation(name)         \
  template <class T>                 \
  struct is_##name {                 \
    static const bool value = false; \
  };                                 \
  template <class T>                 \
  inline constexpr bool is_##name##_v = is_##name<T>::value;
#define AssignAnnotation(cls, annotation) \
  template <>                             \
  struct is_##annotation<cls> {           \
    static const bool value = true;       \
  };
#define AssignAnnotationTemplate(cls, annotation, type) \
  template <type T>                                     \
  struct is_##annotation<cls<T>> {                      \
    static const bool value = true;                     \
  };
#define FunctionAlias(from, to)                       \
  template <typename... Args>                         \
  inline auto to(Args &&...args)                      \
      ->decltype(from(std::forward<Args>(args)...)) { \
    return from(std::forward<Args>(args)...);         \
  }
#define CastToScalar(field, type) \
  operator type() const { return type(field); }
#define CastToAllScalar(field) \
  CastToScalar(field, i8);     \
  CastToScalar(field, u8);     \
  CastToScalar(field, i16);    \
  CastToScalar(field, u16);    \
  CastToScalar(field, i32);    \
  CastToScalar(field, u32);    \
  CastToScalar(field, i64);    \
  CastToScalar(field, u64);    \
  CastToScalar(field, f32);    \
  CastToScalar(field, f64);    \
  CastToScalar(field, f80);
#define COMMA ,
#ifndef LOCAL
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
#else
std::mt19937 rng(0);
#endif
template <class T> T random_choice(T l, T r, std::mt19937 &gen = rng) {
  std::uniform_int_distribution<T> random(l, r);
  return random(gen);
}
namespace dalt {
#ifndef LOCAL
struct Timer {explicit Timer(const char* m) {}void stop() const {}};
#else
#endif
}
using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using usize = size_t;
using f32 = float;
using f64 = double;

using f80 = long double;
FunctionAlias(std::lower_bound, LowerBound);
FunctionAlias(std::upper_bound, UpperBound);
FunctionAlias(std::unique, Unique);
FunctionAlias(std::swap, Swap);
FunctionAlias(std::min, Min);
FunctionAlias(std::max, Max);
FunctionAlias(std::abs, Abs);
FunctionAlias(std::sin, Sin);
FunctionAlias(std::asin, Asin);
FunctionAlias(std::cos, Cos);
FunctionAlias(std::acos, Acos);
FunctionAlias(std::tan, Tan);
FunctionAlias(std::atan, Atan);
FunctionAlias(std::sort, Sort);
FunctionAlias(std::fill, Fill);
FunctionAlias(std::move, Move);
FunctionAlias(std::reverse, Reverse);
FunctionAlias(std::max_element, MaxElement);
FunctionAlias(std::min_element, MinElement);
FunctionAlias(std::make_tuple, MakeTuple);
FunctionAlias(std::make_pair, MakePair);
FunctionAlias(std::clamp, Clamp);
FunctionAlias(std::shuffle, Shuffle);
FunctionAlias(std::to_string, ToString);
FunctionAlias(std::tie, Tie);
template <typename _Signature>
using Function = std::function<_Signature>;
template <typename _Signature>
using Func = Function<_Signature>;
using Str = std::string;
using String = Str;
using StringStream = std::stringstream;
using IStream = std::istream;
using OStream = std::ostream;
using std::enable_if;
using std::enable_if_t;
using std::is_base_of;
using std::is_base_of_v;
using std::is_floating_point;
using std::is_floating_point_v;
using std::is_integral;
using std::is_integral_v;
using std::is_arithmetic;
using std::is_arithmetic_v;
using std::is_same;
using std::is_same_v;
auto &Stderr = std::cerr;
auto &Stdin = std::cin;
auto &Stdout = std::cout;
template <class T>
using Less = std::less<T>;
template <class T>
using Greater = std::greater<T>;
template <typename _Key, typename _Tp, typename _Compare = Less<_Key>>
using TreeMap = std::map<_Key, _Tp, _Compare>;
template <typename _Key, typename _Compare = Less<_Key>>
using TreeSet = std::set<_Key, _Compare>;
template <typename _Key, typename _Compare = std::less<_Key>,
          typename _Alloc = std::allocator<_Key>>
using MultiTreeSet = std::multiset<_Key, _Compare, _Alloc>;
template <class T>
using Deque = std::deque<T>;
template <class T>
using Queue = std::queue<T>;
template <class T>
using Vec = std::vector<T>;
template <class T>
using Reducer = Func<T(const T &, const T &)>;
template <class T>
using Comparator = Func<bool(const T &, const T &)>;
template <class T>
using Indexer = Func<T(i32)>;
template <class T>
using Indexer2 = Func<T(i32, i32)>;
template <class A, class B = A, class C = A>
using Adder = Func<C(const A &, const B &)>;
template <class I>
using Checker = Func<bool(const I &)>;
template <class A, class B>
using BiChecker = Func<bool(const A &, const B &)>;
template <class T>
using Consumer = Func<void(const T &)>;
template<class T>
using Supplier = Func<T()>;
template <class FIRST, class SECOND>
using BiConsumer = Func<void(const FIRST &, const SECOND &)>;
template <class F, class T = F>
using Mapper = Func<T(const F &)>;
template <class T>
using MinHeap = std::priority_queue<T, Vec<T>, Greater<T>>;
template <class T>
using MaxHeap = std::priority_queue<T, Vec<T>, Less<T>>;
template <class T, usize S>
using Array = std::array<T, S>;
template <typename... _Elements>
using Tuple = std::tuple<_Elements...>;
template <class T, class = enable_if_t<is_floating_point_v<T>>>
using Complex = std::complex<T>;
template <class A, class B>
using Pair = std::pair<A, B>;
namespace dalt {
template <class T>
IStream& operator>>(IStream& is, Vec<T>& val) {
  for (auto& v : val) {
    is >> v;
  }
  return is;
}
#define VEC_OP(op)                         \
  template <class T>                       \
  Vec<T>& operator op(Vec<T>& data, T x) { \
    for (auto& v : data) {                 \
      v op x;                              \
    }                                      \
    return data;                           \
  }
VEC_OP(+=)
VEC_OP(-=)
VEC_OP(*=)
VEC_OP(/=)
VEC_OP(%=)
VEC_OP(^=)
VEC_OP(&=)
VEC_OP(|=)
VEC_OP(==)
VEC_OP(!=)
template <class T>
int Compare(const Vec<T>& lhs, const Vec<T>& rhs) {
  for(int i = 0; i < Size(lhs) && i < Size(rhs); i++) {
    if(lhs[i] != rhs[i]) {
      return lhs[i] < rhs[i] ? -1 : 1;
    }
  }
  return Size(lhs) < Size(rhs) ? -1 : Size(lhs) > Size(rhs) ? 1 : 0;
}
template <class T>
bool operator<(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) < 0;
}
template <class T>
bool operator>(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) > 0;
}
template <class T>
bool operator<=(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) <= 0;
}
template <class T>
bool operator>=(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) >= 0;
}
}  

using namespace dalt;

namespace external {
namespace graph {
struct Xor128 {
  unsigned x, y, z, w;
  Xor128() : x(123456789), y(362436069), z(521288629), w(88675123) {}
  unsigned next() {
    unsigned t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
  }
  
  inline unsigned next(unsigned n) { return next() % n; }
};






template <typename Node>
struct BottomupTreap {
  Xor128 rng;
  typedef Node *Ref;
  static int size(Ref t) { return !t ? 0 : t->size; }
  unsigned nextRand() { return rng.next(); }
 private:
  bool choiceRandomly(Ref l, Ref r) { return l->priority < r->priority; }
 public:
  Ref join(Ref l, Ref r) {
    if (!l) return r;
    if (!r) return l;
    Ref t = NULL;
    unsigned long long dirs = 0;
    int h;
    for (h = 0;; ++h) {
      if (h >= sizeof(dirs) * 8 - 2) {
        
        
        t = join(l->right, r->left);
        dirs = dirs << 2 | 1;
        h++;
        break;
      }
      dirs <<= 1;
      if (choiceRandomly(l, r)) {
        Ref c = l->right;
        if (!c) {
          t = r;
          r = r->parent;
          break;
        }
        l = c;
      } else {
        dirs |= 1;
        Ref c = r->left;
        if (!c) {
          t = l;
          l = l->parent;
          break;
        }
        r = c;
      }
    }
    for (; h >= 0; --h) {
      if (!(dirs & 1)) {
        Ref p = l->parent;
        t = l->linkr(t);
        l = p;
      } else {
        Ref p = r->parent;
        t = r->linkl(t);
        r = p;
      }
      dirs >>= 1;
    }
    return t;
  }
  typedef std::pair<Ref, Ref> RefPair;
  
  RefPair split2(Ref t) {
    Ref p, l = t->left, r = t;
    Node::cut(l);
    t->linkl(NULL);
    while (p = t->parent) {
      t->parent = NULL;
      if (p->left == t)
        r = p->linkl(r);
      else
        l = p->linkr(l);
      t = p;
    }
    return RefPair(l, r);
  }
  
  RefPair split3(Ref t) {
    Ref p, l = t->left, r = t->right;
    Node::cut(l), Node::cut(r);
    t->linklr(NULL, NULL);
    while (p = t->parent) {
      t->parent = NULL;
      if (p->left == t)
        r = p->linkl(r);
      else
        l = p->linkr(l);
      t = p;
    }
    return RefPair(l, r);
  }
  Ref cons(Ref h, Ref t) {
    assert(size(h) == 1);
    if (!t) return h;
    Ref u = NULL;
    while (true) {
      if (choiceRandomly(h, t)) {
        Ref p = t->parent;
        u = h->linkr(t);
        t = p;
        break;
      }
      Ref l = t->left;
      if (!l) {
        u = h;
        break;
      }
      t = l;
    }
    while (t) {
      u = t->linkl(u);
      t = t->parent;
    }
    return u;
  }
};

class EulerTourTreeWithMarks {
  struct Node {
    typedef BottomupTreap<Node> BST;
    Node *left, *right, *parent;
    int size;
    unsigned priority;
    char marks, markUnions;  
    Node()
        : left(NULL),
          right(NULL),
          parent(NULL),
          size(1),
          priority(0),
          marks(0),
          markUnions(0) {}
    inline Node *update() {
      int size_t = 1, markUnions_t = marks;
      if (left) {
        size_t += left->size;
        markUnions_t |= left->markUnions;
      }
      if (right) {
        size_t += right->size;
        markUnions_t |= right->markUnions;
      }
      size = size_t, markUnions = markUnions_t;
      return this;
    }
    inline Node *linkl(Node *c) {
      if (left = c) c->parent = this;
      return update();
    }
    inline Node *linkr(Node *c) {
      if (right = c) c->parent = this;
      return update();
    }
    inline Node *linklr(Node *l, Node *r) {
      if (left = l) l->parent = this;
      if (right = r) r->parent = this;
      return update();
    }
    static Node *cut(Node *t) {
      if (t) t->parent = NULL;
      return t;
    }
    static const Node *findRoot(const Node *t) {
      while (t->parent) t = t->parent;
      return t;
    }
    static std::pair<Node *, int> getPosition(Node *t) {
      int k = BST::size(t->left);
      Node *p;
      while (p = t->parent) {
        if (p->right == t) k += BST::size(p->left) + 1;
        t = p;
      }
      return std::make_pair(t, k);
    }
    static const Node *findHead(const Node *t) {
      while (t->left) t = t->left;
      return t;
    }
    static void updatePath(Node *t) {
      while (t) {
        t->update();
        t = t->parent;
      }
    }
  };
  typedef Node::BST BST;
  BST bst;
  std::vector<Node> nodes;
  
  
  std::vector<int> firstArc;
  
  std::vector<bool> edgeMark, vertexMark;
  inline int getArcIndex(const Node *a) const { return a - &nodes[0]; }
  inline int arc1(int ei) const { return ei; }
  inline int arc2(int ei) const { return ei + (numVertices() - 1); }
 public:
  inline int numVertices() const { return firstArc.size(); }
  inline int numEdges() const { return numVertices() - 1; }
  inline bool getEdgeMark(int a) const {
    return a < numEdges() ? edgeMark[a] : false;
  }
  inline bool getVertexMark(int v) const { return vertexMark[v]; }
 private:
  void updateMarks(int a, int v) {
    Node *t = &nodes[a];
    t->marks = getEdgeMark(a) << 0 | getVertexMark(v) << 1;
    Node::updatePath(t);
  }
  
  void firstArcChanged(int v, int a, int b) {
    if (a != -1) updateMarks(a, v);
    if (b != -1) updateMarks(b, v);
  }
 public:
  class TreeRef {
    friend class EulerTourTreeWithMarks;
    const Node *ref;
   public:
    TreeRef() {}
    TreeRef(const Node *ref_) : ref(ref_) {}
    bool operator==(const TreeRef &that) const { return ref == that.ref; }
    bool operator!=(const TreeRef &that) const { return ref != that.ref; }
    bool isIsolatedVertex() const { return ref == NULL; }
  };
  void init(int N) {
    int M = N - 1;
    firstArc.assign(N, -1);
    nodes.assign(M * 2, Node());
    for (int i = 0; i < M * 2; i++) nodes[i].priority = bst.nextRand();
    edgeMark.assign(M, false);
    vertexMark.assign(N, false);
  }
  TreeRef getTreeRef(int v) const {
    int a = firstArc[v];
    return TreeRef(a == -1 ? NULL : Node::findRoot(&nodes[a]));
  }
  bool isConnected(int v, int w) const {
    if (v == w) return true;
    int a = firstArc[v], b = firstArc[w];
    if (a == -1 || b == -1) return false;
    return Node::findRoot(&nodes[a]) == Node::findRoot(&nodes[b]);
  }
  static int getSize(TreeRef t) {
    if (t.isIsolatedVertex())
      return 1;
    else
      return t.ref->size / 2 + 1;
  }
  void link(int ti, int v, int w) {
    int a1 = arc1(ti), a2 = arc2(ti);
    
    if (v > w) std::swap(a1, a2);
    int va = firstArc[v], wa = firstArc[w];
    Node *l, *m, *r;
    if (va != -1) {
      
      std::pair<Node *, Node *> p = bst.split2(&nodes[va]);
      m = bst.join(p.second, p.first);
    } else {
      
      m = NULL;
      firstArc[v] = a1;
      firstArcChanged(v, -1, a1);
    }
    if (wa != -1) {
      std::pair<Node *, Node *> p = bst.split2(&nodes[wa]);
      l = p.first, r = p.second;
    } else {
      
      l = r = NULL;
      firstArc[w] = a2;
      firstArcChanged(w, -1, a2);
    }
    
    m = bst.cons(&nodes[a2], m);
    
    r = bst.cons(&nodes[a1], r);
    bst.join(bst.join(l, m), r);
  }
  void cut(int ti, int v, int w) {
    
    if (v > w) std::swap(v, w);
    int a1 = arc1(ti), a2 = arc2(ti);
    std::pair<Node *, Node *> p = bst.split3(&nodes[a1]);
    int prsize = BST::size(p.second);
    std::pair<Node *, Node *> q = bst.split3(&nodes[a2]);
    Node *l, *m, *r;
    
    if (p.second == &nodes[a2] || BST::size(p.second) != prsize) {
      l = p.first, m = q.first, r = q.second;
    } else {
      
      std::swap(v, w);
      std::swap(a1, a2);
      l = q.first, m = q.second, r = p.second;
    }
    
    if (firstArc[v] == a1) {
      int b;
      if (r != NULL) {
        
        b = getArcIndex(Node::findHead(r));
      } else {
        
        b = !l ? -1 : getArcIndex(Node::findHead(l));
      }
      firstArc[v] = b;
      firstArcChanged(v, a1, b);
    }
    if (firstArc[w] == a2) {
      
      int b = !m ? -1 : getArcIndex(Node::findHead(m));
      firstArc[w] = b;
      firstArcChanged(w, a2, b);
    }
    bst.join(l, r);
  }
  void changeEdgeMark(int ti, bool b) {
    assert(ti < numEdges());
    edgeMark[ti] = b;
    Node *t = &nodes[ti];
    t->marks = (b << 0) | (t->marks & (1 << 1));
    Node::updatePath(t);
  }
  void changeVertexMark(int v, bool b) {
    vertexMark[v] = b;
    int a = firstArc[v];
    if (a != -1) {
      Node *t = &nodes[a];
      t->marks = (t->marks & (1 << 0)) | (b << 1);
      Node::updatePath(t);
    }
  }
  template <typename Callback>
  bool enumMarkedEdges(TreeRef tree, Callback callback) const {
    return enumMarks<0, Callback>(tree, callback);
  }
  
  template <typename Callback>
  bool enumMarkedVertices(TreeRef tree, Callback callback) const {
    return enumMarks<1, Callback>(tree, callback);
  }
 private:
  
  
  
  
  template <int Mark, typename Callback>
  bool enumMarks(TreeRef tree, Callback callback) const {
    if (tree.isIsolatedVertex()) return true;
    const Node *t = tree.ref;
    if (t->markUnions >> Mark & 1)
      return enumMarksRec<Mark, Callback>(t, callback);
    else
      return true;
  }
  
  template <int Mark, typename Callback>
  bool enumMarksRec(const Node *t, Callback callback) const {
    const Node *l = t->left, *r = t->right;
    if (l && (l->markUnions >> Mark & 1))
      if (!enumMarksRec<Mark, Callback>(l, callback)) return false;
    if (t->marks >> Mark & 1)
      if (!callback(getArcIndex(t))) return false;
    if (r && (r->markUnions >> Mark & 1))
      if (!enumMarksRec<Mark, Callback>(r, callback)) return false;
    return true;
  }
 public:
  
  void debugEnumEdges(std::vector<int> &out_v) const {
    int M = numEdges();
    for (int ti = 0; ti < M; ti++) {
      const Node *t = &nodes[ti];
      if (t->left || t->right || t->parent) out_v.push_back(ti);
    }
  }
};











class HolmDeLichtenbergThorup {
  typedef HolmDeLichtenbergThorup This;
  typedef EulerTourTreeWithMarks Forest;
  typedef Forest::TreeRef TreeRef;
  int numVertices_m;
  int numSamplings;
  
  std::vector<Forest> forests;
  std::vector<char> edgeLevel;
  std::vector<int> treeEdgeIndex;          
  std::vector<int> treeEdgeMap;            
  std::vector<int> treeEdgeIndexFreeList;  
  
  std::vector<int> arcHead;
  std::vector<std::vector<int>> firstIncidentArc;
  std::vector<int> nextIncidentArc, prevIncidentArc;
  
  std::vector<bool> edgeVisited;
  std::vector<int> visitedEdges;  
  int arc1(int ei) const { return ei; }
  int arc2(int ei) const { return numMaxEdges() + ei; }
  int arcEdge(int i) const {
    return i >= numMaxEdges() ? i - numMaxEdges() : i;
  }
  bool replace(int lv, int v, int w) {
    Forest &forest = forests[lv];
    TreeRef vRoot = forest.getTreeRef(v), wRoot = forest.getTreeRef(w);
    assert(vRoot.isIsolatedVertex() || wRoot.isIsolatedVertex() ||
           vRoot != wRoot);
    int vSize = forest.getSize(vRoot), wSize = forest.getSize(wRoot);
    int u;
    TreeRef uRoot;
    int uSize;
    if (vSize <= wSize)
      u = v, uRoot = vRoot, uSize = vSize;
    else
      u = w, uRoot = wRoot, uSize = wSize;
    
    int replacementEdge = -1;
    enumIncidentArcs(forest, uRoot, u, lv,
                     FindReplacementEdge(uRoot, &replacementEdge));
    
    
    
    if (replacementEdge != -1 && (int)visitedEdges.size() + 1 <= numSamplings) {
      
      deleteNontreeEdge(replacementEdge);
      addTreeEdge(replacementEdge);
      for (int i = 0; i < (int)visitedEdges.size(); i++)
        edgeVisited[visitedEdges[i]] = false;
      visitedEdges.clear();
      return true;
    }
    
    
    for (int i = 0; i < (int)visitedEdges.size(); i++) {
      int ei = visitedEdges[i];
      edgeVisited[ei] = false;
      deleteNontreeEdge(ei);
      ++edgeLevel[ei];
      insertNontreeEdge(ei);
    }
    visitedEdges.clear();
    
    forest.enumMarkedEdges(uRoot, EnumLevelTreeEdges(this));
    
    for (int i = 0; i < (int)visitedEdges.size(); i++) {
      int ti = visitedEdges[i];
      int ei = treeEdgeMap[ti];
      int v = arcHead[arc2(ei)], w = arcHead[arc1(ei)];
      int lv = edgeLevel[ei];
      edgeLevel[ei] = lv + 1;
      forests[lv].changeEdgeMark(ti, false);
      forests[lv + 1].changeEdgeMark(ti, true);
      forests[lv + 1].link(ti, v, w);
    }
    visitedEdges.clear();
    if (replacementEdge != -1) {
      
      deleteNontreeEdge(replacementEdge);
      addTreeEdge(replacementEdge);
      return true;
    } else if (lv > 0) {
      return replace(lv - 1, v, w);
    } else {
      return false;
    }
  }
  struct EnumLevelTreeEdges {
    This *thisp;
    EnumLevelTreeEdges(This *thisp_) : thisp(thisp_) {}
    inline bool operator()(int a) {
      thisp->enumLevelTreeEdges(a);
      return true;
    }
  };
  void enumLevelTreeEdges(int ti) { visitedEdges.push_back(ti); }
  
  template <typename Callback>
  bool enumIncidentArcs(Forest &forest, TreeRef t, int u, int lv,
                        Callback callback) {
    if (t.isIsolatedVertex())
      return enumIncidentArcsWithVertex<Callback>(lv, u, callback);
    else
      return forest.enumMarkedVertices(
          t, EnumIncidentArcs<Callback>(this, lv, callback));
  }
  template <typename Callback>
  struct EnumIncidentArcs {
    This *thisp;
    int lv;
    Callback callback;
    EnumIncidentArcs(This *thisp_, int lv_, Callback callback_)
        : thisp(thisp_), lv(lv_), callback(callback_) {}
    inline bool operator()(int tii) const {
      return thisp->enumIncidentArcsWithTreeArc(tii, lv, callback);
    }
  };
  template <typename Callback>
  bool enumIncidentArcsWithTreeArc(int tii, int lv, Callback callback) {
    bool dir = tii >= numVertices() - 1;
    int ti = dir ? tii - (numVertices() - 1) : tii;
    int ei = treeEdgeMap[ti];
    int v = arcHead[arc2(ei)], w = arcHead[arc1(ei)];
    
    int u = !(dir != (v > w)) ? v : w;
    return enumIncidentArcsWithVertex(lv, u, callback);
  }
  
  template <typename Callback>
  bool enumIncidentArcsWithVertex(int lv, int u, Callback callback) {
    int it = firstIncidentArc[lv][u];
    while (it != -1) {
      if (!callback(this, it)) return false;
      it = nextIncidentArc[it];
    }
    return true;
  }
  struct FindReplacementEdge {
    TreeRef uRoot;
    int *replacementEdge;
    FindReplacementEdge(TreeRef uRoot_, int *replacementEdge_)
        : uRoot(uRoot_), replacementEdge(replacementEdge_) {}
    inline bool operator()(This *thisp, int a) const {
      return thisp->findReplacementEdge(a, uRoot, replacementEdge);
    }
  };
  
  bool findReplacementEdge(int a, TreeRef uRoot, int *replacementEdge) {
    int ei = arcEdge(a);
    if (edgeVisited[ei]) return true;
    int lv = edgeLevel[ei];
    TreeRef hRoot = forests[lv].getTreeRef(arcHead[a]);
    if (hRoot.isIsolatedVertex() || hRoot != uRoot) {
      
      *replacementEdge = ei;
      return false;
    }
    
    edgeVisited[ei] = true;
    visitedEdges.push_back(ei);
    return true;
  }
  void addTreeEdge(int ei) {
    int v = arcHead[arc2(ei)], w = arcHead[arc1(ei)];
    int lv = edgeLevel[ei];
    int ti = treeEdgeIndexFreeList.back();
    treeEdgeIndexFreeList.pop_back();
    treeEdgeIndex[ei] = ti;
    treeEdgeMap[ti] = ei;
    forests[lv].changeEdgeMark(ti, true);
    for (int i = 0; i <= lv; i++) forests[i].link(ti, v, w);
  }
  void insertIncidentArc(int a, int v) {
    int ei = arcEdge(a);
    int lv = edgeLevel[ei];
    assert(treeEdgeIndex[ei] == -1);
    int next = firstIncidentArc[lv][v];
    firstIncidentArc[lv][v] = a;
    nextIncidentArc[a] = next;
    prevIncidentArc[a] = -1;
    if (next != -1) prevIncidentArc[next] = a;
    if (next == -1) forests[lv].changeVertexMark(v, true);
  }
  void deleteIncidentArc(int a, int v) {
    int ei = arcEdge(a);
    int lv = edgeLevel[ei];
    assert(treeEdgeIndex[ei] == -1);
    int next = nextIncidentArc[a], prev = prevIncidentArc[a];
    nextIncidentArc[a] = prevIncidentArc[a] = -2;
    if (next != -1) prevIncidentArc[next] = prev;
    if (prev != -1)
      nextIncidentArc[prev] = next;
    else
      firstIncidentArc[lv][v] = next;
    if (next == -1 && prev == -1) forests[lv].changeVertexMark(v, false);
  }
  void insertNontreeEdge(int ei) {
    int a1 = arc1(ei), a2 = arc2(ei);
    insertIncidentArc(a1, arcHead[a2]);
    insertIncidentArc(a2, arcHead[a1]);
  }
  void deleteNontreeEdge(int ei) {
    int a1 = arc1(ei), a2 = arc2(ei);
    deleteIncidentArc(a1, arcHead[a2]);
    deleteIncidentArc(a2, arcHead[a1]);
  }
 public:
  HolmDeLichtenbergThorup() : numVertices_m(0), numSamplings(0) {}
  int numVertices() const { return numVertices_m; }
  int numMaxEdges() const { return edgeLevel.size(); }
  void init(int N, int M) {
    numVertices_m = N;
    int levels = 1;
    while (1 << levels <= N / 2) levels++;
    
    numSamplings = (int)(levels * 1);
    forests.resize(levels);
    for (int lv = 0; lv < levels; lv++) forests[lv].init(N);
    edgeLevel.assign(M, -1);
    treeEdgeIndex.assign(M, -1);
    treeEdgeMap.assign(N - 1, -1);
    treeEdgeIndexFreeList.resize(N - 1);
    for (int ti = 0; ti < N - 1; ti++) treeEdgeIndexFreeList[ti] = ti;
    arcHead.assign(M * 2, -1);
    firstIncidentArc.resize(levels);
    for (int lv = 0; lv < levels; lv++) firstIncidentArc[lv].assign(N, -1);
    nextIncidentArc.assign(M * 2, -2);
    prevIncidentArc.assign(M * 2, -2);
    edgeVisited.assign(M, false);
  }
  bool insertEdge(int ei, int v, int w) {
    if (!(0 <= ei && ei < numMaxEdges() && 0 <= v && v < numVertices() &&
          0 <= w && w < numVertices())) {
      system("pause");
    }
    assert(0 <= ei && ei < numMaxEdges() && 0 <= v && v < numVertices() &&
           0 <= w && w < numVertices());
    assert(edgeLevel[ei] == -1);
    int a1 = arc1(ei), a2 = arc2(ei);
    arcHead[a1] = w, arcHead[a2] = v;
    bool treeEdge = !forests[0].isConnected(v, w);
    edgeLevel[ei] = 0;
    if (treeEdge) {
      addTreeEdge(ei);
    } else {
      treeEdgeIndex[ei] = -1;
      
      if (v != w) insertNontreeEdge(ei);
    }
    return treeEdge;
  }
  bool deleteEdge(int ei) {
    assert(0 <= ei && ei < numMaxEdges() && edgeLevel[ei] != -1);
    int a1 = arc1(ei), a2 = arc2(ei);
    int v = arcHead[a2], w = arcHead[a1];
    int lv = edgeLevel[ei];
    int ti = treeEdgeIndex[ei];
    bool splitted = false;
    if (ti != -1) {
      treeEdgeMap[ti] = -1;
      treeEdgeIndex[ei] = -1;
      treeEdgeIndexFreeList.push_back(ti);
      for (int i = 0; i <= lv; i++) forests[i].cut(ti, v, w);
      forests[lv].changeEdgeMark(ti, false);
      splitted = !replace(lv, v, w);
    } else {
      
      if (v != w) deleteNontreeEdge(ei);
    }
    arcHead[a1] = arcHead[a2] = -1;
    edgeLevel[ei] = -1;
    return splitted;
  }
  bool isConnected(int v, int w) const { return forests[0].isConnected(v, w); }
};
}
}
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M;
  in >> N >> M;
  int lastans = 0;
  external::graph::HolmDeLichtenbergThorup g;
  g.init(N + 1, M);
  var id = [&](int a, int b) {
    if(a > b) {
      Swap(a, b);
    }
    return a * 10000 + b;
  };
  TreeMap<int, int> map;
  for(int i = 0; i < M; i++) {
    int op, x, y;
    in >> op >> x >> y;
    x ^= lastans;
    y ^= lastans;
    if(op == 0) {
      g.insertEdge(i, x, y);
      map[id(x, y)] = i;
    } else if(op == 1) {
      g.deleteEdge(map[id(x, y)]);
    } else {
      if(g.isConnected(x, y)) {
        lastans = x;
        out << "Y";
      } else {
        lastans = y;
        out << "N";
      }
      out << '\n';
    }
  }
}
void SolveMulti(IStream &in, OStream &out) {
  
  int num_of_input = 1;
  
  for (int i = 0; i < num_of_input; i++) {
    
	SolveOne(i + 1, in, out);
  }
}
int main() {
  std::ios_base::sync_with_stdio(false);
  Stdin.tie(0);
  Stdout << std::setiosflags(std::ios::fixed);
  Stdout << std::setprecision(15);
#ifdef STRESS
  stress::Stress();
#else
  SolveMulti(Stdin, Stdout);
#endif
  return 0;
}