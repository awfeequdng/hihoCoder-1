#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

struct node {
    int spring[26];
    int next;
    bool is_end_of_word;
    void init() {
        memset(spring, 0, sizeof(spring));
        next = 0;
        is_end_of_word = false;
    }
}T[1000001];

void insert(char* word) {
    static int end = 1;
    int now = 0, p;
    for (p = 0; word[p] != '\0'; ++p) {
        if (T[now].spring[word[p] - 'a'] == 0) {
            T[end].init();
            T[now].spring[word[p] - 'a'] = end;
            ++end;
        }
        now = T[now].spring[word[p] - 'a'];
    }
    T[now].is_end_of_word = true;
}

void get_next() {  /*uses breath-first search*/
    queue<int> *q = new queue<int>;
    int i, now;
    for (i = 0; i < 26; ++i)
        if (T[0].spring[i] != 0)
            q->push(T[0].spring[i]);
    while (!q->empty()) {
        now = q->front();
        for (i = 0; i < 26; ++i)
            if (T[now].spring[i] != 0) {
                q->push(T[now].spring[i]);
                /*if one node is the end of a word,
                 *all node in the subtree should be labeled,
                 *like "abc" and "abcd"*/
                if (T[now].is_end_of_word == true)
                    T[T[now].spring[i]].is_end_of_word = true;
                /*calculate next, similar with KMP*/
                T[T[now].spring[i]].next = T[now].next;
                while (T[T[now].spring[i]].next != 0
                && T[T[T[now].spring[i]].next].spring[i] == 0)
                    T[T[now].spring[i]].next = T[T[T[now].spring[i]].next].next;
                T[T[now].spring[i]].next = T[T[T[now].spring[i]].next].spring[i];
                /*if one node's next is the end of a word,
                 *the node should be labeled, too*/
                if (T[T[T[now].spring[i]].next].is_end_of_word == true)
                    T[T[now].spring[i]].is_end_of_word = true;
            }
        q->pop();
    }
    delete q;
}

bool query(char* str) {
    int p, now = 0;
    for (p = 0; str[p] != '\0'; ++p) {
        while (now != 0 && T[now].spring[str[p] - 'a'] == 0)
            now = T[now].next;
        now = T[now].spring[str[p] - 'a'];
        if (T[now].is_end_of_word == true)
            return true;
    }
    return false;
}

int main() {
    int n;
    char s[1000001];
    T[0].init();
    scanf("%d", &n);
    while (n--) {
        scanf("%s", s);
        insert(s);
    }
    get_next();
    scanf("%s", s);
    printf("%s\n", query(s) ? "YES" : "NO");
    return 0;
}
