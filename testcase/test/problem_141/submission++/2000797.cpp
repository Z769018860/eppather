#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using Int = long long;

template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <class T> ostream &operator<<(ostream &os, const vector<T> &as) { const int sz = as.size(); os << "["; for (int i = 0; i < sz; ++i) { if (i >= 256) { os << ", ..."; break; } if (i > 0) { os << ", "; } os << as[i]; } return os << "]"; }
template <class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }
template <class T> bool chmin(T &t, const T &f) { if (t > f) { t = f; return true; } return false; }
template <class T> bool chmax(T &t, const T &f) { if (t < f) { t = f; return true; } return false; }
#define COLOR(s) ("\x1b[" s "m")



template <class T, int SIZE, T OFFSET> struct Depam {
  struct Node {
    
    
    
    int len, pos, fail;
    int nxt[SIZE], quick[SIZE];
  };

  
  
  
  
  int nodesLen, pre, suf;
  vector<Node> nodes;
  
  int nL, nR, l, r;
  vector<T> tsBuffer;
  T *ts;
  
  int historyLen;
  vector<pair<int, int>> history;

  Depam(int nL_, int nR_) : nL(nL_), nR(nR_) {
    nodesLen = 2;
    pre = suf = 0;
    nodes.resize(2 + nL + nR);
    nodes[0].len =  0; nodes[0].pos = 0; nodes[0].fail = 1;
    nodes[1].len = -1; nodes[1].pos = 0; nodes[1].fail = 1;
    memset(nodes[0].nxt, 0, sizeof(nodes[0].nxt));
    memset(nodes[1].nxt, 0, sizeof(nodes[1].nxt));
    for (int a = 0; a < SIZE; ++a) nodes[0].quick[a] = 1;
    for (int a = 0; a < SIZE; ++a) nodes[1].quick[a] = 1;
    l = r = 0;
    tsBuffer.assign(1 + nL + nR + 1, OFFSET - 1);
    ts = tsBuffer.data() + (1 + nL);
    historyLen = 0;
    history.resize(nL + nR);
  }
  const Node &operator[](int u) const {
    return nodes[u];
  }

  void pushFront(T t) {
    assert(-nL < l);
    const int a = t - OFFSET;
    history[historyLen++] = make_pair(~pre, -1);
    ts[--l] = t;
    if (ts[l + 1 + nodes[pre].len] != t) pre = nodes[pre].quick[a];
    Node &f = nodes[pre];
    if (!f.nxt[a]) {
      history[historyLen - 1].second = pre;
      Node &g = nodes[nodesLen];
      g.len = f.len + 2; g.pos = l; g.fail = nodes[f.quick[a]].nxt[a];
      memset(g.nxt, 0, sizeof(g.nxt));
      memcpy(g.quick, nodes[g.fail].quick, sizeof(g.quick));
      g.quick[ts[l + nodes[g.fail].len] - OFFSET] = g.fail;
      f.nxt[a] = nodesLen++;  
    }
    if (nodes[pre = f.nxt[a]].len == r - l) suf = pre;
  }
  void pushBack(T t) {
    assert(r < nR);
    const int a = t - OFFSET;
    history[historyLen++] = make_pair(suf, -1);
    ts[r++] = t;
    if (ts[r - 2 - nodes[suf].len] != t) suf = nodes[suf].quick[a];
    Node &f = nodes[suf];
    if (!f.nxt[a]) {
      history[historyLen - 1].second = suf;
      Node &g = nodes[nodesLen];
      g.len = f.len + 2; g.pos = r - g.len; g.fail = nodes[f.quick[a]].nxt[a];
      memset(g.nxt, 0, sizeof(g.nxt));
      memcpy(g.quick, nodes[g.fail].quick, sizeof(g.quick));
      g.quick[ts[r - 1 - nodes[g.fail].len] - OFFSET] = g.fail;
      f.nxt[a] = nodesLen++;  
    }
    if (nodes[suf = f.nxt[a]].len == r - l) pre = suf;
  }
  void undo() {
    const pair<int, int> h = history[--historyLen];
    if (h.first < 0) {
      
      if (nodes[pre].len == r - l) suf = nodes[suf].fail;
      pre = ~h.first;
      if (~h.second) {
        --nodesLen;
        nodes[h.second].nxt[ts[l] - OFFSET] = 0;
      }
      ts[l++] = OFFSET - 1;
    } else {
      
      if (nodes[suf].len == r - l) pre = nodes[pre].fail;
      suf = h.first;
      if (~h.second) {
        --nodesLen;
        nodes[h.second].nxt[ts[r - 1] - OFFSET] = 0;
      }
      ts[--r] = OFFSET - 1;
    }
  }

  void dfsPrint(ostream &os, int u, const string &branch, int type) const {
    const Node &f = nodes[u];
    os << branch << ((type == 0) ? "" : (type == 1) ? "|-- " : "`-- ");
    if (f.len <= 0) {
      os << "(" << f.len << ")";
    } else {
      for (int i = f.pos; i < f.pos + f.len; ++i) os << ts[i];
    }
    os << " " << u << " " << f.fail;
    
    os << "\n";
    int a0 = -1;
    for (int a = 0; a < SIZE; ++a) if (f.nxt[a]) a0 = a;
    for (int a = 0; a < SIZE; ++a) if (f.nxt[a]) {
      dfsPrint(os, f.nxt[a],
               branch + ((type == 0) ? "" : (type == 1) ? "|   " : "    "),
               (a == a0) ? 2 : 1);
    }
  }
  friend ostream &operator<<(ostream &os, const Depam &depam) {
    depam.dfsPrint(os, 0, "  ", 0);
    depam.dfsPrint(os, 1, "", 0);
    return os;
  }
};





char buf[400'010];

string S;
int Q;
vector<int> O;
vector<string> T;

int main() {
  for (; ~scanf("%s", buf); ) {
    S = buf;
    scanf("%d", &Q);
    O.resize(Q);
    T.assign(Q, "");
    for (int q = 0; q < Q; ++q) {
      scanf("%d", &O[q]);
      if (O[q] == 1 || O[q] == 2) {
        scanf("%s", buf);
        T[q] = buf;
      }
    }
    
    int nL = 0, nR = S.size();
    for (int q = 0; q < Q; ++q) {
      if (O[q] == 1) nR += (int)T[q].size();
      if (O[q] == 2) nL += (int)T[q].size();
    }
    Depam<char, 26, 'a'> depam(nL, nR);
    vector<int> dep(2 + nL + nR, 0);
    Int ans = 0;
    for (const char s : S) {
      depam.pushBack(s);
      ans += dep[depam.suf] = dep[depam[depam.suf].fail] + 1;
    }
    for (int q = 0; q < Q; ++q) {
      if (O[q] == 1) {
        for (const char t : T[q]) {
          depam.pushBack(t);
          ans += dep[depam.suf] = dep[depam[depam.suf].fail] + 1;
        }
      } else if (O[q] == 2) {
        for (const char t : T[q]) {
          depam.pushFront(t);
          ans += dep[depam.pre] = dep[depam[depam.pre].fail] + 1;
        }
      } else if (O[q] == 3) {
        printf("%lld\n", ans);
      }
    }
  }
  return 0;
}
