#include <stdio.h>

int fun(int n, int p[])
{
    int person[n];
    int i = 0;
    for(i = 0; i < n; ++i)
        person[i] = 1;
    int count = 0;
    int nums = 0;
    i = 0;
    while(1)
    {
        if(i == n)
            i = 0;
        if(person[i] == 0)
        {
            i++;
            continue;
        }
        else
        {
            nums++;
            if(nums == 3)
            {
                person[i] = 0;
                p[count++] = i+1;
                nums = 0;
            }
            i++;
        }
        if(count == n)
            break;
    }
    return i;
}

int main()
{
    int i, n;
    scanf("%d", &n);
    int p[n];
    for(i = 0; i < n; ++i)
        p[i] = 0;
    int lastPerson = fun(n, p);
    printf("%d\t", lastPerson);
    for(i = 0; i < n; ++i)
        printf("%d ", p[i]);
    printf("\n");
    return 0;
}
