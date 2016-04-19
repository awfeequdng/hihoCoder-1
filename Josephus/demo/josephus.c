#include <stdio.h>
#include <stdlib.h>
//定义循环链表结构
typedef struct node
{
    int data;
    struct node *next;
}cLinkList;

//定义循环链表创建函数
void cListCreat(cLinkList *L, int n)
{
    int i = 0;
    cLinkList *head, *p;
    head = L;
    p = L;
    L->data = i;
    for(i = 1; i < n; ++i)
    {
        p = (cLinkList *)malloc(sizeof(cLinkList));
        p->data = i;
        L->next = p;
        L = p;
    }
    L->next = head;
    L = head;
}

int main()
{
    int num, i, n, k;
    cLinkList *L;
    scanf("%d", &num);
    while(num--)
    {
        scanf("%d%d", &n, &k);
        L = (cLinkList *)malloc(sizeof(cLinkList));
        cListCreat(L, n);
        cLinkList *p, *temp;
        p = L;
        while(n > 1)
        {
            for(i = 2; i < k; ++i)
            {
                p = p->next;
            }
            temp = p->next;
            p->next = temp->next;
            p = p->next;
            free(temp);
            n--;
        }
        printf("%d\n", p->data);
        free(p);
    }
    return 0;
}
