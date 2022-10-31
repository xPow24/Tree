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
    lo = x; hi = y;
    if (from > to || lo == hi) return;
    b.reserve(to - from + 1);
    b.push_back(0);
    int mid = (lo + hi)/2;
    auto check = [mid](int tt) {
      return tt <= mid; 
    };
    for (auto it = from; it != to; ++it) {
      if (*it <= mid) {
        cc = max(cc, *it);
        b.push_back(b.back() + 1);
      }
      else {
        zz = min(zz, *it);
        b.push_back(b.back());
      }
    }
    int mid2 = max(mid + 1, zz);
    mid = min(mid, cc);
    auto pivot = stable_partition(from, to, check);
    l = new WVTree(from, pivot, lo, mid);
    r = new WVTree(pivot, to, mid2, hi);
  }
  int kth(int u, int v, int k) {
    if (u > v) return 0;
    if (lo == hi) return lo;
    int lb = b[u - 1], rb = b[v];
    int cur = rb - lb;
    if (k <= cur) return this->l->kth(lb + 1, rb, k);
    else return this->r->kth(u - lb, v - rb, k - cur);
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
  int q, n, k, l, r, maxn = 0, minn = 1e9;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    maxn = max(maxn, a[i]);
    minn = min(minn, a[i]);
  }
  WVTree T(a + 1, a + n + 1, minn, maxn);
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
