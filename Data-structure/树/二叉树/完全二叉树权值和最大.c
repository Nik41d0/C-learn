#include <stdio.h>
#define MAXn 100000


int main()
{
    int n, a[MAXn + 1],i,j;
    printf("请输入节点总数:");
    scanf("%d", &n);
    printf("请输入各个节点数:");
    for (i = 1; i <= n; i++)
        scanf("%d", a + i);
    long long m = -MAXn;    
    int ans = 1;
    for (i = 1; (1 << (i - 1)) <= n; ++i)
    {
        long long t = 0;
        for (j = 1 << (i - 1); j < (1 << i) && j <= n; j++)
            t += a[j];
        if (m < t)
	{
            m = t;
            ans = i;
        }
    }
    printf("权值和最大的层数为:%d\n", ans);
    return 0;
}
