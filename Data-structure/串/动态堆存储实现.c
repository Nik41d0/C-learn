#include<stdio.h>
#include<stdlib.h>
#define MAXLEN 100


typedef struct
{
	char *ch;
	int length;
}HString;


void StrAssign(HString *s,char a[])
{
	int i=0;
	while(a[i]!='\0')
		i++;
	s->length=i;
	s->ch=(char *)malloc(s->length*sizeof(char));
	for(i=0;i<s->length;i++)
		s->ch[i]=a[i];
}


void StrPrint(HString s)
{
	int i;
	for(i=0;i<s.length;i++)
		printf("%c",s.ch[i]);
	printf("\n");
}


void freeHString(HString s)
{
	if(s.ch!=NULL)
		free(s.ch);
}


int SubStr(HString *sub,HString s,int pos,int len)
{
	int i;
	if(pos<1||pos>s.length||len<0||len>s.length-pos+1)
		return 0;
	sub->length=len;
	sub->ch=(char *)malloc(sub->length*sizeof(char));
	for(i=0;i<len;i++)
		sub->ch[i]=s.ch[pos+1];
	return 1;
}


int Strcom(HString s1,HString s2)
{
	int i=0;
	while(s1.ch[i]==s2.ch[i]&&i<=s1.length-1&&i<=s2.length-1)
		i++;
	if(i<=s1.length-1&&i<=s2.length-1)
		return s1.ch[i]-s2.ch[i];
	else if(i>s1.length-1&&s2.length-1)
		return 0;
	else if(i>s1.length-1)
		return -1;
	else
		return 1;
}


int StrLenth(HString a)
{
	return a.length;
}

int Index(HString S,HString T,int pos)
{
	int i=pos,j=1;
	while(i<=S.length&&j<=T.length)
	{
		if(S.ch[i-1]==T.ch[j-1])
		{
			++i;
			++j;
		}
		else
		{
			i=i-j+2;
			j=1;
		}
	}
	if(j>T.length)
		return i-T.length;
	else
		return 0;
}


int Concat(HString *T,HString S1,HString S2)
{
	int i;
	T->ch=(char *)malloc((S1.length+S2.length)*sizeof(char));
	if(!T->ch) return 0;
	for(i=0;i<=S1.length-1;i++)
		T->ch[i]=S1.ch[i];
	for(i=0;i<=S2.length-1;i++)
		T->ch[S1.length+i]=S2.ch[i];
	T->length=S1.length+S2.length;
	return 1;
}


int main()
{
	int t;
	HString a,sub,T;
	StrAssign(&a,"1234512367890");
	StrAssign(&sub,"123");
	t=Index(a,sub,2);
	printf("%d\n",t);
	Concat(&T,a,sub);
	StrPrint(T);
	freeHString(a);
	freeHString(sub);
	freeHString(T);
	return 0;
}
