#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000;
int tree[MAXN*4], a[MAXN];

void buildtree(int id, int l, int r) {
  if (l == r) {tree[id] = a[l]; return;}
  int mid = (l + r)/2;
  buildtree(id*2, l, mid); buildtree(id*2 + 1, mid + 1, r);
  tree[id] = max(tree[id*2], tree[id*2 + 1]);
}

int main()
{
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  buildtree(1, 1, n);
}
