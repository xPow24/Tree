const int MAXN = 2 * 1e5 + 1;
int n, bit[MAXN];
void update(int x) {
  while (x) {
    bit[x]++;
    x -= x & -x;
  }
}
int get(int x) {
  int res = 0;
  while (x <= n) {
    res += bit[x];
    x += x & -x;
  }
  return res;
}
