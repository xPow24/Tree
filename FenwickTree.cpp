#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2*1e5 + 1;
int n, bit[MAXN];
void update(int x) {
  while (x) {
    bit[x]++;
    x -= x & -x;
  }
}
long long get(int x) {
  long long res = 0;
  while (x <= n) {
    res += bit[x];
    x += x & -x;
  }
  return res;
}
int main() {
  int tc;
  cin >> tc;
  while (tc--) {
    long long ans = 0;
    int x;
    cin >> n;
    memset(bit, 0, sizeof(bit));
    for (int i = 0; i < n; ++i) {
      cin >> x;
      ans += get(x); 
      update(x);
    }
    cout << ans << '\n';
  }
}
