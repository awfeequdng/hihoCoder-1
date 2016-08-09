#include <stdio.h>

#define N 100005
#define MODE_ADD 0
#define MODE_SET 1

typedef struct _seg_tree_ {
    int left, right;
    int add;
    int setv;
    int val;
    _seg_tree_ *lson = NULL, *rson = NULL;
    _seg_tree_(int left_idx, int right_idx, int value)
        : left(left_idx), right(right_idx), add(0), setv(-1), val(value) {}
} seg_tree, *pseg_tree;

pseg_tree construct_seg_tree(int left, int right) {
    if (left == right) {
        int val;
        scanf("%d", &val);
        return new seg_tree(left, right, val);
    }
    int mid = left + (right - left) / 2;
    pseg_tree lson = construct_seg_tree(left, mid);
    pseg_tree rson = construct_seg_tree(mid + 1, right);
    pseg_tree ans = new seg_tree(left, right, lson->val + rson->val);
    ans->lson = lson;
    ans->rson = rson;
    return ans;
}
void lazy_down(pseg_tree proot) {
    if (proot->setv != -1) {
        if (proot->lson != NULL) {
            proot->lson->setv = proot->setv;
            proot->lson->add = 0;
            proot->lson->val = proot->setv * (proot->lson->right - proot->lson->left + 1);
            proot->rson->setv = proot->setv;
            proot->rson->add = 0;
            proot->rson->val = proot->setv * (proot->rson->right - proot->rson->left + 1);
        }
        proot->setv = -1;
    }
    if (proot->add != 0) {
        if (proot->lson != NULL) {
            proot->lson->add += proot->add;
            proot->rson->add += proot->add;
            proot->lson->val += proot->add * (proot->lson->right - proot->lson->left + 1);
            proot->rson->val += proot->add * (proot->rson->right - proot->rson->left + 1);
        }
        proot->add = 0;
    }
}
void modify_seg_tree(pseg_tree proot, int left, int right, int val, int type) {
    if (left == proot->left && right == proot->right) {
        if (type == MODE_ADD) {
            proot->add += val;
            proot->val += val * (right - left + 1);
        } else {
            proot->setv = val;
            proot->val = val * (right - left + 1);
            proot->add = 0;
        }
        return;
    }
    int mid = proot->left + (proot->right - proot->left) / 2;
    lazy_down(proot);
    if (left > mid) {
        modify_seg_tree(proot->rson, left, right, val, type);
    }
    else if (right <= mid) {
        modify_seg_tree(proot->lson, left, right, val, type);
    }
    else {
        modify_seg_tree(proot->rson, mid + 1, right, val, type);
        modify_seg_tree(proot->lson, left, mid, val, type);
    }
    proot->val = proot->lson->val + proot->rson->val;
}
int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    pseg_tree proot = construct_seg_tree(0, n);
    int type, left, right, val;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d%d", &type, &left, &right, &val);
        modify_seg_tree(proot, left, right, val, type);
        printf("%d\n", proot->val);
    }
    return 0;
}
