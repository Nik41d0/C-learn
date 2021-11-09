#include <stdio.h>
void delchar(char *s,char c)
{
    char *p,*q;
    p=s;
    while(*p!='\0')
    {
        if(*p==c)
        {
            q=p;
            while(*q!='\0')
            {
                *q=*(q+1);
                q++;
            }
        }
        if(*p!= c)
            p++;
    }
}
 
 
int main(void)
{
    char s[100];
    char c;
    printf("Input a string:");
    gets(s);
    printf("Input a char:");
    scanf("%c",&c);
    delchar(s,c);
    printf("After deleted,the string is:%s",s);
    return 0;
}
