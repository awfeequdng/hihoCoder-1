#include <iostream>
#include <algorithm>
#include <set>


using namespace std;

int n, m;
const int MAX = 1000000;

struct node{
  int id;
  int value;
  node *parent;
  set<node *> children;
};

void print(int rid, int **array){

  cout << "id=" << rid << "\t";
  for(int i=0; i<n-m+1; ++i){
    cout << array[rid][i] << "\t";
  }
  cout << endl;
}

void f(node *root, int **array){
  int rid = root->id;

  if(root->children.empty()){
    array[rid][1] = root->value;
    return;
  }

  for (set<node *>::iterator it = root->children.begin();
    it != root->children.end(); ++it) {
    f(*it, array);
  }

  for (set<node *>::iterator it = root->children.begin();
    it != root->children.end(); ++it) {
    int cid = (*it)->id;
    int *temp = new int[n-m+1]();
    for(int i=1; i<=n-m; i++){
      if(temp[i] == 0){
        temp[i] = array[rid][i];
      }
      for(int j=1; (j<=i) && (array[cid][j] != MAX); j++){
        temp[i] = min(temp[i], array[rid][i-j] + array[cid][j]); 
      }
      if(temp[i] == MAX){
        break;
      }
    }
    for(int i=1; i<=n-m; i++){
      if(temp[i] != 0){
        array[rid][i] = temp[i];
      }
    }
    delete[] temp;
  }
  
  for(int i=1; i<=n-m; i++){
    if(array[rid][i] == MAX){
      array[rid][i] = array[rid][i-1] + root->value;
      break;
    }
  }
  // print(rid, array);
}

int main(){
    
#ifndef ONLINE_JUDGE
    freopen ("input.txt" , "r" , stdin);
#endif
    cin >> n >> m;

    bool *candidate = new bool[n]();
    bool *removed = new bool[n]();
    node *nodes = new node[n];
    int total = 0;
    for(int i=0; i<n; ++i){
      cin >> nodes[i].value; 
      total += nodes[i].value;
      nodes[i].id = i;
    }    

    for(int i=0; i<n-1; ++i){
      int a, b;
      cin >> a >> b;
      --a;
      --b;
      if(a>b){
        swap(a, b);
      }

      nodes[a].children.insert(&nodes[b]);
      nodes[b].parent = &nodes[a];
    }
  
    int **array = new int*[n];   
    for(int i=0; i<n; i++){
      array[i] = new int[n-m+1]();
      array[i][0] = 0;
      for(int j=1; j<n-m+1; ++j){
        array[i][j] = MAX;
      }
    }
 
    f(&nodes[0], array);
    cout << (total - array[0][n-m]) << endl;
    
    return 0;
    
}