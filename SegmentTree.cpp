const int MAXN = 1e3;
const int INF = 1e9 + 9;
int a[MAXN];

struct SegmentTree {
  int lazy;
  int val;
};

SegmentTree tree[MAXN * 4];

vector<int> merge(vector<int> c, vector<int> b) {
  int l = 0, r = 0;
  vector<int> res;
  while (l < (int)c.size() || r < (int)b.size()) {
    if (l >= (int)c.size()) {
      res.push_back(b[r++]);
    } else if (r >= (int)b.size()) {
      res.push_back(c[l++]);
    } else if (c[l] < b[r]) {
      res.push_back(c[l++]);
    } else {
      res.push_back(b[r++]);
    }
  }
  return vector<int>(begin(res), end(res));
}

void buildtree(int id, int l, int r) {
  if (l == r) { tree[id].val = a[l]; return; }
  int mid = (l + r) >> 1;
  buildtree(id << 1, l, mid); buildtree((id << 1) + 1, mid + 1, r);
  tree[id].val = max(tree[id << 1].val, tree[(id << 1) + 1].val);
}

void down(int id) {
  int cur = tree[id].lazy;
  tree[id << 1].val += cur; tree[id << 1].lazy += cur;
  tree[(id << 1) + 1].val += cur; tree[(id << 1) + 1].lazy += cur;
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
  upd((id << 1), l, mid, u, v, k); upd((id << 1) + 1, mid + 1, r, u, v, k);
  tree[id].val = max(tree[id << 1].val, tree[(id << 1) + 1].val); 
}

int get_query(int id, int l, int r, int u, int v) {
  if (v < l || r < u) return -INF;
  if (l <= u && v <= r) return tree[id].val;
  down(id);
  int mid = (l + r) >> 1;
  return max(get_query(id << 1, l, mid + 1, u, v), get_query((id << 1) + 1, mid + 1, r, u, v)); 
}
