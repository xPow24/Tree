#include <bits/stdc++.h> 
using namespace std;
const int N = 3e5;
int a[N];
const int MAX = 1e6;

struct WVTree {
  int lo, hi;
  WVTree *l, *r;
  vector<int> b;
  WVTree(int *from, int *to, int x, int y) {
    lo = x, hi = y;
    if (lo == hi || from >= to) return;
    int mid = (lo + hi)/2;
    auto f = [mid](int tt) {
      return tt <= mid;
    };
    b.reserve(to - from + 1);
    b.push_back(0);
    for (auto it = from; it != to; it++) {
      b.push_back(b.back() + f(*it));
    }
    auto pivot = stable_partition(from, to, f);
    l = new WVTree(from, pivot, lo, mid);
    r = new WVTree(pivot, to, mid + 1, hi);
  }
  int kth(int u, int v, int k) {
    if (u > v) return 0;
    if (lo == hi) return lo;
    int inleft = b[v] - b[u - 1];
    int lb = b[u - 1], rb = b[v];
    if (k <= inleft) return this->l->kth(lb + 1, rb, k);
    return this->r->kth(u - lb, v - rb, k - inleft);
  }
  int LTE(int u, int v, int k) {
    if (u > v || k < lo) return 0;
    if (hi <= k) return v - u + 1;
    int lb = b[u - 1], rb = b[v];
    return this->l->LTE(lb + 1, rb, k) + this->r->LTE(u - lb, v - rb, k);
  }
  int count(int u, int v, int k) {
    if (u > v || k < lo || k > hi) return 0;
    if (lo == hi) return v - u + 1;
    int lb = b[u - 1], rb = b[v], mid = (lo + hi)/2;
    if (k <= mid) return this->l->count(lb + 1, rb, k);
    else return this->r->count(u - lb, v - rb, k);
  }	
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  int q, n, k, l, r, maxn = 0;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    maxn = max(maxn, a[i]);
  }
  WVTree T(a + 1, a + n + 1, 1, maxn);
  cin >> q;
  while (q--) {
    int type;
    cin >> type >> l >> r >> k;
    if (type == 0) {
      //return kth smallest value in [l, r]
      cout << T.kth(l, r, k) << '\n';
    }
    if (type == 1) {
      //return number of values that are less than or equal to K in [l, r]
      cout << T.LTE(l, r, k) << '\n';
    }
    if (type == 2) {
      //count number of occurences of K in [l, r]
      cout << T.count(l, r, k) << '\n';
    }
  }
  return 0;
} 
