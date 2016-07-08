#include<cstdio>
struct Node {
  int key;
  int val;

  Node *l, *r;
  Node *p;
  Node() { p = NULL; }
  Node(int k,int v, Node *pp) {
    key = k;
    val = v;
    p = pp;
    l = r = NULL;
  }
};
class Splay{
public:
  Node *root;
  Node *_hot;
  Splay(){
    root = _hot = NULL;
  }
  Splay(int k,int v) {
    root = new Node(k,v, NULL);
    _hot = root;
  }
  void zig(Node *cur) {
    if (cur == NULL) return;
    Node *v = cur->l;
    if (v == NULL) return;
    Node *g = cur->p;

    v->p = g;
    if (g != NULL) {
      if (cur == g->l) g->l = v;
      else g->r = v;
    }

    cur->l = v->r;
    if (cur->l != NULL) cur->l->p = cur;

    cur->p = v;
    v->r = cur;
    if (cur == root) root = v;
  }
  void zag(Node *cur) {
    if (cur == NULL) return;
    Node *v = cur->r;
    if (v == NULL) return;
    Node *g = cur->p;

    v->p = g;
    if (g != NULL) {
      if (cur == g->l) g->l = v;
      else g->r = v;
    }

    cur->r = v->l;
    if (cur->r != NULL) cur->r->p = cur;

    cur->p = v;
    v->l = cur;
    if (cur == root) root = v;
  }
  void splay(Node *x, Node *f) {
    if (x == NULL) return;
    while (x->p != f) {
      Node *p = x->p;
      if (p == NULL) return;
      if (p->p == f) {
        if (x == p->l) {

          zig(p);
        }
        else {
          zag(p);
        }
      }
      else {
        Node *g = p->p;
        if (g == NULL) return;
        if (g->l == p) {
          if (p->l == x) {
            zig(g); zig(p);
          }
          else {
            zag(p); zig(g);
          }
        }
        else {
          if (p->l == x) {
            zig(p); zag(g);
          }
          else {
            zag(g); zag(p);
          }
        }
      }
    }
  }
  Node* search(Node *cur, int k) {
    if (cur == NULL) return _hot;
    if (cur->key == k) {
      splay(cur, NULL);
      return cur;
    }
    _hot = cur;
    if (k < cur->key) return search(cur->l, k);
    else return search(cur->r, k);
  }

  Node* insert(Node *cur, int k,int v) {
    if (cur == NULL) {
      cur = new Node(k,v, _hot);
      if (k < _hot->key)
        _hot->l = cur;
      else
        _hot->r = cur;
      _hot = cur;
      splay(cur, NULL);
      return cur;
    }
    _hot = cur;
    if (k < cur->key)
      return insert(cur->l, k,v);
    else
      return insert(cur->r, k,v);
  }
  Node* prev(int k) {
    splay(search(root, k), NULL);
    Node *cur = root->l;
    if (cur == NULL) return NULL;
    while (cur->r != NULL) cur = cur->r;
    return cur;
  }
  Node* succ(int k) {
    splay(search(root, k), NULL);
    Node *cur = root->r;
    if (cur == NULL) return NULL;
    while (cur->l != NULL) cur = cur->l;
    return cur;
  }

  Node* splay2(int a,int b)
  {
    Node *pa = search(root, a);
    if (pa->key != a) pa = insert(pa, a,0);
    Node *pb = search(root, b);
    if (pb->key != b) pb = insert(pb, b,0);

    Node *p = prev(a);
    Node *s = succ(b);
    splay(p, NULL);
    splay(s, p);
    Node *q = s->l;
    _hot = s;
    return s;
  }
  void deleteInterval(int a,int b) {
    splay2(a,b);
    _hot->l = NULL;
  }
  int sum(Node *a)
  {
    if(a == NULL)
      return 0;
    return sum(a->l) + sum(a->r) + a->val;
  }
  int areaAdd(int a,int b)
  {
    splay2(a,b);
    return sum(_hot->l);
  }
  void addNum(Node *a,int c)
  {
    if(a != NULL)
      a->val += c;
    if(a->l)
      addNum(a->l,c);
    if(a->r)
      addNum(a->r,c);
  }
  void setAera(int a,int b,int c)
  {
    splay2(a,b);
    return addNum(_hot->l,c);
  }
};

const int MIN_K = 0;
const int MAX_K = 1000000005;
char s[5];
int main()
{
  Splay *mySplay = new Splay(MIN_K,0);
  mySplay->insert(mySplay->root, MAX_K,0);
  int key,val, n,a,b,c;
  scanf("%d", &n);
  while (n--) {
    scanf("%s", s);
    if (s[0] == 'I') {
      scanf("%d%d", &key,&val);
      mySplay->insert(mySplay->root,key,val);
    }
    else if (s[0] == 'Q')
    {
      scanf("%d%d", &a,&b);
      printf("%d\n",mySplay->areaAdd(a,b));
    }
    else if (s[0] == 'D')
    {
     scanf("%d%d", &a,&b);
     mySplay->deleteInterval(a,b);
    }
    else if (s[0] == 'M')
    {
      scanf("%d%d%d", &a,&b,&c);
      mySplay->setAera(a,b,c);
    }
  }
  return 0;
}
