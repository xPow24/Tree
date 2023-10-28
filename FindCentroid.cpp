const int maxn = 1e5 + 1;

int N, M, ans;

int child[maxn + 5];

vector<int> g[maxn + 1];

void init() {
  cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
}

void dfs(int u, int p) {
  child[u] = 1;
  for (int v : g[u]) {
    if (v == p) continue; 
    dfs(v, u);
    child[u] += child[v];
  }
}

int find_centroid(int v, int p, int sz) {
  for (int u : g[v]) {
    if (u == p) continue;
    if (child[u] > sz / 2) 
      return find_centroid(u, v, sz);
  }
  return v;
}
