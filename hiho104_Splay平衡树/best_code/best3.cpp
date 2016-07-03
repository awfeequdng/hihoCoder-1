#define _CRT_SECURE_NO_WARNINGS
//#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<string>
#include<queue>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
#include<limits.h>
#include<set>
using namespace std;

const int maxn = 100001;


// splay
struct Node{
	Node *ch[2];
	int r;		// 优先级，数值越大，优先级越高
	int v;		// 值
	int s,addv,mx;		// 需要维护的值
	// mx是当前结点为根的子树中结点最大值，addv是对当前结点为根的子树所有区间操作。
	bool operator < (const Node& rhs) const{
		return  r < rhs.r;
	}
	int cmp( int x ) const { // isLessThan
		if( x == v ) return -1;
		return x < v ? 0 : 1;
	}
	int cmpS( int x ) const{
		int ss = 1;
		if( ch[0] != NULL )
			ss += ch[0]->s;
		if( x == ss ) return -1;
		return x < ss ? 0 : 1;
	}
	void maintain(){
		/*s = 1;
		mx = v;
		if( ch[0] != NULL ){
			s += ch[0]->s;
			mx = max( mx, ch[0]->mx );
		}
		if( ch[1] != NULL ){
			s += ch[1]->s;
			mx = max( mx, ch[1]->mx );
		}
		mx += addv;*/
	}
	void pushdown(){
		/*if( ch[0] != NULL ){
			ch[0]->addv += addv;
			ch[0]->maintain();
		}
		if( ch[1] != NULL ){
			ch[1]->addv += addv;
			ch[1]->maintain();
		}
		if( ch[0] == NULL && ch[1] == NULL )
			v = v + addv;
		addv = 0;*/
	}
};

void rotate( Node* &o, int d ){ // d为0表示左旋:右旋提升左儿子，左旋提升右儿子
	Node* k = o->ch[d^1];
	o->pushdown(); k->pushdown();
	o->ch[d^1] = k->ch[d]; k->ch[d] = o;
	o->maintain(); k->maintain(); // 必须先维护o，再维护k
	o = k; // 要改变o，因为原来指向地址o的结点（其父节点）现在要指向地址k。
}
void insert( Node* &o, int x ){
	if( o == NULL ){ o = new Node(); o->ch[0] = o->ch[1] = NULL; o->v = x ; o->r = rand(); }
	else{
		int d = o->cmp(x);
		insert( o->ch[d], x ); if( o->ch[d] > o ) rotate(o, d^1);
	}
}
void remove( Node* &o, int x ){ // 相当于erase
	int d = o->cmp(x);
	if( d==-1 ){ // 找到x
		if( o->ch[0] == NULL ) o = o->ch[1];
		else if( o->ch[1] == NULL ) o = o->ch[0];
		else{
			int d2 = ( o->ch[0] > o->ch[1]? 1:0 );
			rotate(o, d2 ); remove( o->ch[d2], x );
		}
	}
	else
		remove( o->ch[d], x);
}

int find( Node* o, int x ){
	while( o!= NULL ){
		int d = o->cmp(x);
		if( d==-1 ) return 1;
		else o = o->ch[d];
	}
	return 0;	// 不存在
}
int findK( Node* o, int k ){ // 找不超过k的最大值,要确保有合法解
	if( o == NULL ) return INT_MIN;
	if( o->v == k ) return k;
	else if( o->v > k ) return findK( o->ch[0], k );
	else return max( o->v, findK( o->ch[1], k ) );
}
int kth( Node* o, int k ){ // 第k大的值
	if( o == NULL || k <= 0  || k > o->s ) return 0;
	int s = (o->ch[1] == NULL? 0: o->ch[1]->s );
	if( k == s+1 ) return o->v;
	else if( k <= s ) return kth( o->ch[1], k );
	else return kth( o->ch[0], k-s-1);
}
void splayK( Node* &o, int k ){ // 将v==k的结点伸展到根位置，若有多个，操作其中一个
	int d = o->cmp(k);
	if( d != -1 ){
		Node*p = o->ch[d];
		int d2 = p->cmp(k);
		if( d2 != -1 ){
			splayK( p->ch[d2], k );
			if( d==d2 ) rotate(o, d^1);
			else rotate(o->ch[d], d );
		}
		rotate( o, d^1 );
	}
	// 与单旋的区别是，对于链状，这里以3层节点为一组，先旋o，再旋o的儿子，而不是先旋o的儿子，再旋o
}
void deleteInterval( Node* &r, int a, int b){
	// 删除值在 a,b之间的数， 确保a,b最多出现一次
	if( !find(r, a) ) insert(r, a);
	if( !find(r, b) ) insert(r, b);
	if( a==b ) remove(r, a );
	else{
		splayK(r, a);
		splayK(r->ch[1], b );
		r->ch[1]->ch[0] = NULL;
		remove(r, a);
		remove(r, b);
	}
}
// 可分裂合并序列
Node* build( int *A, int L, int R ){ // 将数组A中范围从L到R的序列建成BST，（隐含的key是其下标）。
	if( L > R )
		return NULL;
	Node* o = new Node();
	int M = L + (R-L)/2;
	o->v = A[M], o->addv = 0;
	o->ch[0] = build( A, L, M-1 );
	o->ch[1] = build( A, M+1, R);
	o->maintain();
	return o;
}
void splay( Node* &o, int k ){  // 将序列顺数第k个位置的数伸展到根位置。
	int d = o->cmpS(k);
	// 如果 d == -1 ，则不需做任何操作。
	if( d == 1) k-= (o->ch[0]==NULL?0:o->ch[0]->s)+1;
	if( d!=-1 ){
		Node* p = o->ch[d];
		int d2 = p->cmpS(k);
		int k2 = (d2==0? k : k- ( p->ch[0]==NULL? 0:p->ch[0]->s   )-1);
		if( d2 != -1 ){
			splay( p->ch[d2], k2 );
			if( d==d2 ) rotate(o, d^1 ); 
			else rotate(o->ch[d], d );
		}
		rotate(o, d^1 );
	}
}
Node* merge(Node* left, Node* right){
	splay( left, left->s); // 将左序列最后一个元素伸展到根
	left->pushdown();
	left->ch[1] = right; // 可见左序列必须不能为NULL，右序列可以
	left->maintain();
	return left;
}
void split( Node* o, int k , Node* &left, Node* &right){ // 序列o分裂成2段，左段包含k（>=1)个元素。
	splay(o, k );
	o->pushdown();
	left = o;
	right = o->ch[1];
	o->ch[1] = NULL;
	left->maintain();
}
void printNode( Node* &o ){
	if( o == NULL ) return;
	printNode( o->ch[0] );
	printf("%d ",o->v);
	printNode( o->ch[1] );
}

struct comp{
	bool operator () ( pair<int,int> p1, pair<int,int> p2 ){
		return p1.second < p2.second ;
	}
};


int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
	int n;
	scanf("%d",&n);
	char ss[2];
	int a, b;
	Node* r = NULL;
	for( int i(0); i < n ; i++ ){
		scanf("%s%d", &ss, &a);
		switch (ss[0])
		{
		case 'I': 
			insert(r, a);
			break;
		case 'Q':
			printf("%d\n",findK(r, a));
			break;
		case 'D':
			scanf("%d",&b);
			deleteInterval(r, a, b );
		}
	}
    return 0;
}