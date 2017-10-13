// Homework 04
// Word Counting
// ---
// Counting the times of [word] exiting in file
// sorting & print
// ---
// Build : 2017 03 27
// Log : 2017 03 27 SF
// ---

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxL 1010
#define wordL 110
#define ON 1
#define OFF 0

typedef struct{
	char word[wordL];
	int count;
}wordCnt;
void ws(wordCnt*,int,int);
void swap(wordCnt *a,wordCnt *b)
{
	wordCnt tmp;
	memcpy(&tmp,a,sizeof(wordCnt));
	memcpy(a,b,sizeof(wordCnt));
	memcpy(b,&tmp,sizeof(wordCnt));
	return;
}
int cmp_num(const void*a,const void*b)
{
	return (*(wordCnt*)a).count<(*(wordCnt*)b).count?1:-1;
}
void my_sort(wordCnt* test,int len)
{
	qsort(test,len,sizeof(wordCnt),cmp_num);
	ws(test,0,len);
	return;
}
void ws(wordCnt*test,int front,int end)
{
	int check,i=1,j,k;
	if(front>=end)return;
	check=test[front].count;
	for(j=front;j<end;j++)
	{
		for(k=j+1;k<end;k++)
		{
			if(test[j].count==check&&test[k].count==check)
				if(strcmp(test[j].word,test[k].word)>0)swap(&test[j],&test[k]);
			i=k-j;
		}
	}
	ws(test,front+i,end);
	return;
}

int main()
{
	wordCnt wList[MaxL];
	char line[wordL];
	int nowC=0,i;
	int isExist=OFF;

	while(fgets(line,wordL,stdin))
	{
		for(i=0;i<nowC;i++)
		{
			if(strcmp(line,wList[i].word)==0)
			{
				wList[i].count++;
				isExist=ON;
			}
		}
		if(isExist==OFF)
		{
			strcpy(wList[nowC].word,line);
			wList[nowC].count=1;
			nowC++;
		}
		isExist=OFF;
	}
	my_sort(wList,nowC);
	for(i=0;i<nowC;i++)
	{
		printf("%d %s",wList[i].count,wList[i].word);
	}
	return 0;
}

