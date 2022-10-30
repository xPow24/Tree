#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000, INF = 1000000009;
int tree[MAXN*4], a[MAXN];

void buildtree(int id, int l, int r) {
  if (l == r) {tree[id] = a[l]; return;}
  int mid = (l + r)/2;
  buildtree(id*2, l, mid); buildtree(id*2 + 1, mid + 1, r);
  tree[id] = max(tree[id*2], tree[id*2 + 1]);
}
int get_query(int id, int l, int r, int u, int v) {
  if (v < l || r < u) return -INF;
  if (l <= u && v <= r) return tree[id];
  int mid = (l + r)/2;
  return max(get_query(id*2, l, mid + 1, u, v), get_query(id*2 + 1, mid + 1, r, u, v)); 
}
int main()
{
  int n, queries; cin >> n >> queries;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  buildtree(1, 1, n);
  while (queries--) {
    int u, v;
    cin >> u >> v;
    cout << get_query(1, 1, n, u, v) << '\n';
  }
}
