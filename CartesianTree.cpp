int N; cin >> N;
vector<int> a(N + 1), sta(N + 1);
vector<vector<int>> ct(N + 1, vector<int>(2, 0));
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
