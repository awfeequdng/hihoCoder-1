#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

struct Node {
    int x, y, v;
    Node *up, *down, *left, *right;
} node[240000]; // 729行,324列的01精确覆盖问题

struct HeadCnt {
    int y, cnt;
    bool operator < (const HeadCnt& x) const {
        return x.cnt < cnt;
    }
} headCnt[325];

int Index;
int ans[100];
int ansIndex;
int mash[10][10];

void removeCol(int col) {
    Node *p = &node[col];
    p->right->left = p->left;
    p->left->right = p->right;
    Node *p2 = p->down;
    while (p != p2) {
        Node *p3 = p2->right;
        while (p2 != p3) {
            headCnt[p3->y].cnt--;
            p3->down->up = p3->up;
            p3->up->down = p3->down;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}
void recoverCol(int col) {
    Node *p = &node[col];
    p->right->left = p;
    p->left->right = p;
    Node *p2 = p->down;
    while (p != p2) {
        Node *p3 = p2->right;
        while (p2 != p3) {
            headCnt[p3->y].cnt++;
            p3->down->up = p3;
            p3->up->down = p3;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}

int minHeadCnt() {
    int Min = 0x7fffffff, index = 1;
    Node *p = node->right;
    while (p != node) {
        if (Min > headCnt[p->y].cnt) {
            Min = headCnt[p->y].cnt;
            index = p->y;
        }
        p = p->right;
    }
    return index;
}

bool dfs(int colDepth) {
    if (node[0].right == &node[0]) {
        return true;
    }
    int in = minHeadCnt();
    Node *p = &node[in];
    
    if (p == p->down) {
        return false;
    }
    removeCol(p->y);
    Node *p2 = p->down;
    while (p != p2) {
        ans[ansIndex] = p2->v;
        ansIndex++;
        
        Node *p3 = p2->right;
        while (p2 != p3) {
            removeCol(p3->y);
            p3 = p3->right;
        }
        if(dfs(colDepth + 1)) {
            return true;
        }
        
        ansIndex--;
        p3 = p2->right;
        while (p2 != p3) {
            recoverCol(p3->y);
            p3 = p3->right;
        }
        p2 = p2->down;
    }
    recoverCol(p->y);
    return false;
}

void addNode (int i, int j, int value) {
    headCnt[j].cnt++;
    Node *lastP = node[j].up;
    
    lastP->down->up = &node[Index + 1];
    node[Index + 1].down = lastP->down;
    lastP->down = &node[Index + 1];
    node[Index + 1].up = lastP;
    
    if (node[Index].x != i) {
        node[Index + 1].left = node[Index + 1].right = &node[Index + 1];
    } else {
        node[Index].right->left = &node[Index+1];
        node[Index + 1].right = node[Index].right;
        node[Index].right = &node[Index+1];
        node[Index + 1].left = &node[Index];
    }
    Index++;
    node[Index].x = i, node[Index].y = j, node[Index].v = value;
}

void setPlane (int x, int y, int v) {
    int i = ((x - 1) * 9 + (y - 1)) * 9 + v;
    int value = x * 100 + y * 10 + v;
    addNode(i, (x - 1) * 9 + v, value);
    addNode(i, 81 + (y - 1) * 9 + v, value);
    int index9 = (x - 1) / 3 * 3 + (y - 1) / 3;
    addNode(i, 162 + index9 * 9 + v, value);
    addNode(i, 243 + (x - 1) * 9 + y, value);
}

int main () {
    int T, tmp;
    scanf("%d", &T);
    while (T--) {
        Index = 0, ansIndex = 0;
        node[0].x = 0, node[0].y = 0;
        node[0].up = node[0].down = node[0].left = node[0].right = &node[0];
        
        for (int j = 1; j <= 324; j++) {
            node[Index].right->left = &node[Index+1];
            node[Index].right = &node[Index+1];
            Index++;
            node[Index].left = &node[Index - 1];
            node[Index].right = &node[0];
            node[Index].x = 0, node[Index].y = j;
            node[Index].up = node[Index].down = &node[Index];
            headCnt[j].y = j, headCnt[j].cnt = 0;
        }
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                scanf("%d", &tmp);
                mash[i][j] = tmp;
                if (tmp != 0) {
                    setPlane(i, j, tmp);
                } else {
                    for (int cnt = 1; cnt <= 9; cnt++) {
                        setPlane(i, j, cnt);
                    }
                }
            }
        }
        
        if(dfs(0)){
            for (int i = 0; i < ansIndex; i++) {
                mash[ans[i] / 100][(ans[i] % 100) / 10] = ans[i] % 10;
            }
            for (int i = 1; i <= 9; i++) {
                for (int j = 1 ; j <= 9; j++) {
                    printf("%d", mash[i][j]);
                    if (j != 9) {
                        printf(" ");
                    }
                }
                puts("");
            }
        } else {
            puts("No");
        }
    }
    return 0;
}