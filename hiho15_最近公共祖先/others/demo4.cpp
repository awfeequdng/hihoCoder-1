#include<iostream>
#include<string>
using namespace std;

struct treeNode{
	int name;
	treeNode * next;
	treeNode * tail;
	treeNode(int a){
		name = a;
		next = tail = NULL;
	}
};
struct queryNode{
	int tar;
	int order;
	queryNode * next;
	queryNode * tail;
	queryNode(int a=-1,int b=0){
		tar = a;
		order = b;
		next = tail = NULL;
	}
};

struct nameNode{
	char ch;
	nameNode * next[26];
	int name;
	nameNode(char c=0){
		ch = c;
		for(int i=0;i<26;i++) next[i] = NULL;
		name = -1;
	}
};


string people[100001];
nameNode * nameRoot = new nameNode;
int arr[100001];
int status[100001];
int answer[100001];
int size=0;
queryNode ** query;
treeNode ** tree;

int find_root(int a){
	if(arr[a]==-1) return a;
	else return arr[a] = find_root(arr[a]);
}

int find_name_pos(string &name){
	nameNode * tmp = nameRoot;
	for(int i=0;i<name.length();i++){
		int pos;
		if(name[i]>='A' && name[i]<='Z') pos = name[i]-'A';
		else pos = name[i]-'a';
		if(tmp->next[pos]==NULL){
			tmp->next[pos] = new nameNode(name[i]);
		}
		tmp = tmp->next[pos];
	}
	if(tmp->name==-1){
		tmp->name = size;
		people[size] = name;
		size++;
	}
	return tmp->name;
}

void find_ancester(int rootName){
	status[rootName] = 1;
	queryNode * tmp = query[rootName]->next;
	while(tmp!=NULL){
		if(status[tmp->tar]==1){
			answer[tmp->order]=tmp->tar;
		}
		if(status[tmp->tar]==2){
			answer[tmp->order]=find_root(tmp->tar);
		}
		tmp = tmp->next;
	}
	treeNode * tmp1 = tree[rootName]->next;
	while(tmp1!=NULL){
		find_ancester(tmp1->name);
		arr[tmp1->name] = rootName;
		tmp1 = tmp1->next;
	}
	status[rootName] = 2;
}



int main(){
	int N;
	cin>>N;
	string father,son;
	for(int i=0;i<=N;i++) arr[i] = -1;
	tree = new treeNode* [N+1];
	for(int i=0;i<=N;i++){
		tree[i] = new treeNode(i);
		tree[i]->tail = tree[i];
	}
	for(int i=0;i<N;i++){
		cin>>father>>son;
		int fa = find_name_pos(father);
		int so = find_name_pos(son);
		tree[fa]->tail->next = new treeNode(so);
		tree[fa]->tail = tree[fa]->tail->next;
	}
	query = new queryNode*[N+1];
	for(int i=0;i<=N;i++){
		query[i] = new queryNode;
		query[i]->tail = query[i];
		status[i] = 0;
		answer[i] = -1;
		arr[i]=-1;
	}
	int M;
	cin>>M;
	string person1,person2;
	for(int i=0;i<M;i++){
		cin>>person1>>person2;
		int per1 = find_name_pos(person1);
		int per2 = find_name_pos(person2);
		query[per1]->tail->next = new queryNode(per2,i);
		query[per1]->tail = query[per1]->tail->next;
		query[per2]->tail->next = new queryNode(per1,i);
		query[per2]->tail = query[per2]->tail->next;
	}
	find_ancester(0);
	for(int i=0;i<M;i++){
		cout<<people[answer[i]]<<endl;
	}
	return 0;
}