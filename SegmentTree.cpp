#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000, INF = 1000000009;
int tree[MAXN*4], a[MAXN];

void buildtree(int id, int l, int r) {
  if (l == r) { tree[id].val = a[l]; return; }
  int mid = (l + r) >> 1;
  buildtree(id * 2, l, mid); buildtree(id * 2 + 1, mid + 1, r);
  tree[id].val = max(tree[id * 2].val, tree[id * 2 + 1].val);
}

void down(int id) {
  int cur = tree[id].lazy;
  tree[id * 2].val += cur; tree[id * 2].lazy += cur;
  tree[id * 2 + 1].val += cur; tree[id * 2 + 1].lazy += cur;
  tree[id].lazy = 0;
}

void upd(int id, int l, int r, int u, int v, int k) {
  if (v < l || r < u) return;
  if (u <= l && r <= v) {
    tree[id].lazy += k;
    tree[id].val += k;
    return;
  }
  down(id);
  int mid = (l + r) >> 1;
  upd(id * 2, l, mid, u, v, k); upd(id * 2 + 1, mid + 1, r, u, v, k);
  tree[id].val = max(tree[id * 2].val, tree[id * 2 + 1].val); 
}

int get_query(int id, int l, int r, int u, int v) {
  if (v < l || r < u) return -INF;
  if (l <= u && v <= r) return tree[id].val;
  down(id);
  int mid = (l + r) >> 1;
  return max(get_query(id * 2, l, mid + 1, u, v), get_query(id * 2 + 1, mid + 1, r, u, v)); 
}
