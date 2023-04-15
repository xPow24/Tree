#include<bits/stdc++.h>
#define vi vector<int>
#define vl vector<long long>
#define ll long long
#define all(x) x.begin(), x.end()
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORREV(i, a, b) for (int i = a; i >= b; --i)
using namespace std;
const int MAXN = 1e5;
int sz[MAXN + 1];
vector<int> g[MAXN + 1];

void DFS(int u, int f) {
  sz[u] = 1;
  for (int v : g[u]) {
    if (v == f) continue;
    DFS(v, u);
    sz[u] += sz[v];
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int N, M; cin >> N >> M;
  FOR(i, 1, N) cin >> a[i];
  FOR(i, 1, N - 1) {
	  int u, v; cin >> u >> v;
	  g[u].push_back(v);
	  g[v].push_back(u);
  }
  DFS(1, 0);
  // cout << sz[x] == biggest subtree that it's root is x
}
