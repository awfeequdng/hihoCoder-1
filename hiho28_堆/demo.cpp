#include <iostream>
#define N 100010
using namespace std;

int num[N];
int rear = 1;

void HeapFixup(int i)
{
    int j, temp;
    temp = num[i];
    j = (i - 1) / 2;
    while(j > 0 && i != 0)
    {
        if(num[j] >= temp)
            break;
        num[i] = num[j];
        i = j;
        j = (i - 1) / 2;
    }
    num[i] = temp;
}

void HeapAdd(int n)
{
    num[rear] = n;
    HeapFixup(rear);
    rear++;
}

void HeapFixdown(int i)
{
    int j, temp;
    temp = num[i];
    j = 2 * i + 1;
    while(j < rear && j+1 < rear)
    {
        if(j+1 < rear && num[j+1] < num[j])
            j++;
        if(num[j] <= temp)
            break;
        num[i] = num[j];
        i = j;
        j = i * 2 + 1;
    }
    num[i] = temp;
}

void HeapDelete()
{
    rear--;
    swap(num[1], num[rear]);
    HeapFixdown(1);
}

int main()
{
    int n;
    char oper;
    int weight;
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> oper;
        if(oper == 'A')
        {
            cin >> weight;
            HeapAdd(weight);
        }
        else
        {
            cout << num[1] << endl;
            HeapDelete();
        }
    }
    return 0;
}
