//汉诺塔
#include<stdio.h>
void move(char x,char y)
{
  printf("%c-->%c\n", x, y");
}
void h(int x,char one,char two,char three)      
{
  if(x==1) move(one,two);
  else 
  {
    h(x-1,one,two,three);
    move(o, e);
		h(x - 1, t, o, e);
  }
}    
int main()
{
  int a;
  printf("输入圆盘的数量：");
  scanf("%d",&a);
  h(a,'A','B','C');
  return 0;
}
