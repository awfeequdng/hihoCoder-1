#include<iostream>
#include<cstdlib>
#include<cstring>
#define MAXN 105

using namespace std;

typedef struct node {
    node* left;
    node* right;
    node* up;
    node* down;
    int x,y;
}Node, *Dancing_Link;

int board[MAXN][MAXN];
Dancing_Link nodes[MAXN][MAXN];
Dancing_Link column_headers[MAXN];
int ans[MAXN];
// Dancing header
Dancing_Link head = NULL;
// board size
int n,m;

void build(){
    int i,j,k;
    // initialize header
    if(head == NULL) head = (Dancing_Link)malloc(sizeof(Node));
    head->left=head->right=head->up=head->down=head;
    head->x = head->y = 0;
    Dancing_Link pre = head;
    Dancing_Link p = NULL;
    // initialize column header
    for(i=1;i<=m;i++){
        p = (Dancing_Link)malloc(sizeof(Node));
        p->up = p->down = p;
        p->x = 0; p->y = i;
        // insert the column header
        p->right = pre->right;
        p->left = pre;
        pre->right->left = p;
        pre->right = p;
        pre = p;
        column_headers[i] = p;
    }
    // initialize the nodes
    memset(nodes, 0, sizeof(Dancing_Link));
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(board[i][j] == 1){
                nodes[i][j] = (Dancing_Link)malloc(sizeof(Node));
                nodes[i][j]->left=nodes[i][j]->right=nodes[i][j]->down=nodes[i][j]->up=nodes[i][j];
                nodes[i][j]->x = i;
                nodes[i][j]->y = j;
            }
        }
    }
    // insert the column nodes
    for(j=1;j<=m;j++){
        // find the jth column header
        pre = column_headers[j];
        for(i=1;i<=n;i++){
            if(board[i][j] == 1){
                p = nodes[i][j];
                p->down = pre->down;
                p->up = pre;
                pre->down->up = p;
                pre->down = p;
                pre = p;
            }
        }
    }
    // insert the row nodes
    for(i=1;i<=n;i++){
        pre = NULL;
        for(j=1;j<=m;j++){
            if(board[i][j] == 1){
                if(pre == NULL)
                    pre = nodes[i][j];
                else{
                    p = nodes[i][j];
                    p->right = pre->right;
                    p->left = pre;
                    pre->right->left = p;
                    pre->right = p;
                    pre = p;
                }
            }
        }
    }
}
void remove(int col){
    Dancing_Link p = column_headers[col];
    // delete the column header in the header row
    p->right->left = p->left;
    p->left->right = p->right;
    Dancing_Link p2 = p->down;
    while(p2 != p){
        Dancing_Link p3 = p2->right;
        // delete all nodes in the colth column
        while(p3 != p2){
            p3->down->up = p3->up;
            p3->up->down = p3->down;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}
void resume(int col){
    Dancing_Link p = column_headers[col];
    p->right->left = p;
    p->left->right = p;
    Dancing_Link p2 = p->down;
    while(p2 != p){
        Dancing_Link p3 = p2->right;
        while(p3 != p2){
            p3->down->up = p3;
            p3->up->down = p3;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}
bool dance(int depth){
    Dancing_Link p = head->right;
    // if the right of header is itself, the job is done
    if(p == head) return true;
    Dancing_Link p2 = p->down;
    // if the column contains none nodes, the column can't be overrided
    if(p2 == p) return false;

    remove(p->y);
    while(p2 != p){
        ans[depth] = p2->x;

        Dancing_Link p3 = p2->right;
        while(p3 != p2){
            remove(p3->y);
            p3 = p3->right;
        }

        // recurse
        if(dance(depth + 1))
            return true;

        p3 = p2->left;
        while(p3 != p2){
            resume(p3->y);
            p3 = p3->left;
        }

        p2 = p2->down;
    }
    resume(p->y);
    return false;
}
int main(){
    int t,i,j;
    scanf("%d", &t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                scanf("%d", &board[i][j]);
            }
        }
        build();
        if(dance(0))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
