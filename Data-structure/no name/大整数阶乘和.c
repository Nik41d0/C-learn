#include<stdio.h>
int main()
{
	int i, j, n, t, ws = 1, jw;
	int a[3000],h[100000];
	a[0] = 1;
	printf("请输入n的值:");
	scanf("%d", &n);
	int hl=0,hjw;
	for (i = 1; i <= n; i++)
	{
		for (j = 1, jw = 0; j <= ws; j++)
		{
			t = a[j-1] * i + jw;
			a[j-1] = t % 10;
			jw = t / 10;
		}
		while (jw)
		{
			++ws;
			a[ws - 1] = jw % 10;
			jw /= 10;
		}
		hjw=0;
		hl = ws > hl ? ws : hl;
		for (j = 0; j <= hl; j++)
		{
			h[j] = h[j] + a[j] + hjw;
			hjw = h[j] / 10;
			h[j] = h[j] % 10;
		}
		if (hjw != 0)
			h[++hl] = jw;
	}
	for (i=hl-1;i>=0;i--)
		printf("%d", h[i]);
	printf("\n");
	return 0;
}
