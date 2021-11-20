\\一物体从height米的高度自由落下，触地后反弹到原高度的一半，再落下，再反弹，如此反复｡该物体在第n次落地时，在空中经过的路程是多少米？第n次反弹的高度是多少？
#include<stdio.h>
int main()
{
	int n,i;
	float height, distance=0;\\height为物体离地高度，distance为物体在height落下后反弹n次时运动的总路程
	printf("Input height: ");
	scanf("%f", &height);\\输入物体离地高度
	printf("Input n: ");
	scanf("%d", &n);\\n为落地几次
	for (i = 1; i <= n; i++)
	{	distance += height;\\物体原有高度
		height =0.5* height ;\\假设物体反弹一次后的高度为原高度的一半
		distance += height;\\物体反弹一次后到达最高点时运动的路程
	}
	distance -= height;\\n次落地时（不算最后一次反弹后上升的距离）物体所经过的路程，若去掉则为最后一次次反弹时物体上升到最高点时所经过的路程
	printf("distance=%0.1f\nheight=%0.1f", distance, height);\\保留一位小数
	return 0;
}
