\\输入一个字符，再输入一个以回车结束的字符串(少于80 个字符)，在字符串中查找该字符｡如果找到，则输出该字符在字符串中所对应的最大下标(下标从0 开始)；否则输出"Not Found"
#include<stdio.h>
#include<string.h>
int main()
{
	char a[80], b;
	int i=0,x=0;
	printf("Input a character:");
	scanf("%c", &b);
	printf("Input a string:");
	scanf("%s", a);\\a为字符数组的首地址名
	for (i = 0; a[i] != '\0'; i++)
	if (a[i] == b) x = i;
	if (x > 0) printf("index=%d\n", x);
	else printf("Not Found");
	return 0;
}
