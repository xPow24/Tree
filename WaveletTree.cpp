#include <bits/stdc++.h>
using namespace std;
const int N = 3e5, M = N;
vector<int> g[N];
int a[N];
const int MAX = 1e6;
struct wavelet_tree{
  #define vi vector<int>
  #define pb push_back
  int lo, hi;
  wavelet_tree *l, *r;
  vi b;
  wavelet_tree(int *from, int *to, int x, int y) {
    lo = x, hi = y;
    if (lo == hi or from >= to) return;
    int mid = (lo + hi)/2;
    auto f = [mid](int x){
      return x <= mid;
    };
    b.reserve(to - from + 1);
    b.pb(0);
    for (auto it = from; it != to; it++)
      b.pb(b.back() + f(*it));
    auto pivot = stable_partition(from, to, f);
    l = new wavelet_tree(from, pivot, lo, mid);
    r = new wavelet_tree(pivot, to, mid + 1, hi);
  }
  int kth(int l, int r, int k) {
    if (l > r) return 0;
    if (lo == hi) return lo;
    int inleft = b[r] - b[l - 1];
    int lb = b[l - 1];
    int rb = b[r];
    if (k <= inleft) return this->l->kth(lb + 1, rb , k);
    return this->r->kth(l - lb, r - rb, k - inleft);
  }
  ~wavelet_tree() {
     delete l;
     delete r;
  }	
};
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  int q, n, k, l, r;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  wavelet_tree T(a + 1, a + n + 1, 1, MAX);
  cin >> q;
  while (q--) {
    cin >> l >> r >> k;
    cout << T.kth(l, r, k) << endl;
  }
  return 0;
} 

