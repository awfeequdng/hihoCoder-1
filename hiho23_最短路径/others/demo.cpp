#include <stdio.h>
#include <string.h>
#include <algorithm>
 
#define N 1005
 
unsigned w[N][N];
 
int main()
{
    memset(w, -1, sizeof(w));
    int n, m, u, v;
    scanf("%d%d%d%d", &n, &m, &u, &v);
    int from, to;
    unsigned weight;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%u", &from, &to, &weight);
        weight = std::min(weight, w[from][to]);
        w[from][to] = w[to][from] = weight;
    }
    int min_idx;
    unsigned min;
    while (true) {
        min_idx = 1;
        min = w[u][1];
        for (int i = 2; i <= n; i++) {
            if (min > w[u][i]) {
                min = w[u][i];
                min_idx = i;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (w[min_idx][i] != (unsigned)-1) {
               w[u][i] = std::min(w[u][i], w[u][min_idx] + w[min_idx][i]);
            }
        }
        if (min_idx == v) {
            break;
        } else {
            w[u][min_idx] = -1;
        }
    }
    printf("%u\n", w[u][v]);
    return 0;
}