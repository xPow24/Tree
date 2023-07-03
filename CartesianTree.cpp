const int MAXN = 1e5;
int N, a[MAXN], sta[MAXN];
int ct[MAXN][2];

// ct[u][0] left child node of u
// ct[u][1] right child node of u

void build() {
  int top = 0, K = 0;
  for (int i = 1; i <= N; ++i) {
    cin >> a[i];
    while (top && a[sta[top]] < a[i]) {
      ct[i][0] = sta[top];
      top--;
    }
    if (top) ct[sta[top]][1] = i;
    sta[++top] = i;
  }
}
