#include<bits/stdc++.h>
using namespace std;
struct BST {
  BST *l, *r, *p;
  int len, sum, val;
};
BST *root;
void initTree() {
  root->l = NULL;
  root->r = NULL;
  root->p = NULL;
  root->len = 0;
  root->sum = 0;
  root->val = 0;
}
void Update(BST* &x) {
  x->len = (x->l)->len + (x->r)->len + 1;
  x->sum = (x->l)->sum + (x->r)->sum + x->val;
}
void SetL(BST* &x, BST* &y) {
  x->l = y;
  y->p = x;
}
void SetR(BST* &x, BST* &y) {
  x->r = y;
  y->p = x;
}
BST *NodeAt(BST* &x, int i) {
  int ord;
  while (true) {
    ord = (x->l)->len + 1;
    if (i == ord) break;
    if (i < ord) {
      x = x->l; 
    }
    else {
      i -= ord;
      x = x->r;
    }
  }
  return x;
}
void UpTree(BST* &x) {
  BST *y, *z;
  y = x->p;
  z = y->p;
  if (x == y->l) {
    SetL(y, x->r);
    SetR(x, y);
  } else {
    SetR(y, x->l);
    SetL(x, y);
  }
  if (z->l == y) {
    SetL(z, x);
  } else {
    SetR(z, x);
  }
  Update(y); Update(x);
}
void Splay(BST* &x) {
  BST *y, *z;
  while (true) {
    y = x->p;
    if (y == NULL) break;
    z = y->p;
    if (z != NULL) {
      if (y == z->l && x == y->l) UpTree(y);
      else UpTree(x);
    }
    else UpTree(x);
  }
}
void Split(BST* &T, int i, BST* &T1, BST* &T2) {
  if (i == 0) {
    T1 = NULL;
    T2 = T;
  } else {
    T1 = NodeAt(T, i);
    Splay(T1);
    T2 = T1->r;
    T1->r = NULL;
    T2->p = NULL;
    Update(T1);
  }
}
BST *Join(BST* &T1, BST* &T2) {
  if (T1 == NULL) return T2;
  else {
    while (T1->r != NULL) T1 = T1->r;
    Splay(T1);
    SetR(T1, T2);
    Update(T1);
    return T1;
  }
}
void Insert(int i, int v) {
  BST *T1, *T2;
  if (i > root->len) {
    i = root->len + 1;
  }
  Split(root, i - 1, T1, T2);
  root->val = v;
  root->p = NULL;
  SetL(root, T1); SetR(root, T2);
  Update(root);
}
int Query(int i, int j) {
  BST *T1, *T2, *T3, *T4;
  Split(root, j, T2, T3);
  Split(T2, i - 1, T1, T2);
  int res = T2->sum;
  T4 = Join(T1, T2);
  root = Join(T4, T3);
  return res;
}
int main() {
  initTree();
  char c;
  int q;
  cin >> q;
  while (q--) {
    cin >> c;
    if (c == 'I') {
      int x, v;
      cin >> x >> v;
      Insert(x, v);
    }
    if (c == 'Q') {
      int i, j;
      cin >> i >> j;
      cout << Query(i, j) << '\n';
    }
  }
  return 0;
}
