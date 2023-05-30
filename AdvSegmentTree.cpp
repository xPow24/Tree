// Chi dung voi truong hop N = 2 ^ K va bai toan khong lien quan den hai dau mut (l, r)
// Cac ham o trong day duoc tinh theo range [l, r) hay [l, r - 1]


const int MAXN = 3000;
int n, h, t[(MAXN << 1) | 1], d[MAXN];

void build_segtree() {
  for (int i = n - 1; i > 0; --i) t[i] = t[i << 1] + t[(i << 1) | 1];
}

void calc(int p, int k) {
  if (d[p]) t[p] = d[p] * k;
  else t[p] = t[p << 1] + t[(p << 1) | 1];
}

void apply(int p, int val, int k) {
  t[p] = val * k;
  if (p < n) d[p] = val;
}

void build(int p) {
  int k = 2;
  for (p += n; p > 1; k <<= 1) {
    p >>= 1; calc(p, k);
  }
} 

void push(int l, int r) {
  int s = h, k = 1 << (h - 1);
  for (l += n, r += n - 1; s > 0; k >>= 1, --s) {
    for (int i = l >> s; i <= r >> s; ++i) {
      if (d[i]) {
        apply(i << 1, d[i], k);
        apply((i << 1) | 1, d[i], k);
        d[i] = 0;
      }
    }
  }
}

void modify(int l, int r, int val) {
  if (!val) return;
  int left_end = l, right_end = r, k = 1;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
    if (l & 1) apply(l++, val, k);
    if (r & 1) apply(--r, val, k);
  }
  build(left_end);
  build(right_end - 1);
}

int query(int l, int r) {
  push(l, l + 1);
  push(r - 1, r);
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res += t[l++];
    if (r & 1) res += t[--r];
  }
  return res;
}
