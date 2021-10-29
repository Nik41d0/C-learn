#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int n,i;
	float height, distance=0;
	printf("Input height: ");
	scanf("%f", &height);
	printf("Input n: ");
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{	distance += height;
		height =0.5* height ;
		distance += height;
	}
	distance -= height;
	printf("distance=%0.1f\nheight=%0.1f", distance, height);
	return 0;
}