#include <iostream>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;
struct TrieNode{
	TrieNode *child, *bro, *fa, *next;
	char val;
	bool isEnd;
	TrieNode(char val) : child(NULL), bro(NULL), fa(NULL), next(NULL), val(val), isEnd(0) {}
}*root=new TrieNode('^');

void createTrie(char *str){
	int len = strlen(str);
	TrieNode *p=root;
	for(int i=0;i<len;i++){
		TrieNode* pa = p->child;
		while(pa!=NULL && pa->val!=str[i])
			pa = pa->bro;
		if(pa==NULL){
			TrieNode *q = new TrieNode(str[i]);
			q->fa = p;
			q->bro = p->child;
			p->child = q;
			p = q;
		}else{
			p = pa;
		}
		if(i==len-1)
			p->isEnd = true;
		
	}
}
TrieNode* in(TrieNode* t,char a){
	TrieNode* tmp = t->child;
	for(;tmp!=NULL && tmp->val != a;tmp = tmp->bro);
	return tmp;
}
void bfs(){
	queue<TrieNode *> myqueue;
	myqueue.push(root);
	while(!myqueue.empty()){
		TrieNode *t = myqueue.front();
		myqueue.pop();
		for(TrieNode* tmp = t->child;tmp;tmp=tmp->bro)
			myqueue.push(tmp);
		if(t == root)
			t->next = NULL;
		else if (t->fa == root)
			t->next = root;
		else{
			TrieNode *np = t->fa->next,*nt=NULL;
			while(np != NULL && (nt=in(np,t->val)) == NULL)
				np = np->next;
			if(np == NULL)
				t->next = NULL;
			else
				t->next = nt;
		}
	}
} 
int main(){
	int N;
	cin>>N;
	for(int w=0;w<N;w++){
		char d[100001];
		cin>>d;
		createTrie(d);
	}
	bfs();
	char m[1000001];
	cin>>m;
	TrieNode *p = root,*tmp = NULL;
	bool hasWord = false;
	for(int i = 0; i<strlen(m); i++){
		while(p!=NULL && (tmp=in(p,m[i])) == NULL)
			p = p->next;
		if(p == NULL)
			p = root;
		else if( tmp->isEnd == true){
			hasWord = true;
			break;
		}
		else
			p = tmp;
	}
	if(hasWord)
		cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
}
 