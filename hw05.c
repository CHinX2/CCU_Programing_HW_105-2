// Homework 05
// Word Counting - Linked List & qsort using
// ---
// Counting the times of [word] in file
// sorting & print
// first '-' means "delete"(value-1)
// first '+' means "add"(value+i)
// ---
// Build : 2017 04 10
// Log : 2017 04 10 SF from HW4
//                  del/upd : ws,cmp_all,my_sort_print
//                  add : lfind,addNode,delNode
//       2017 04 11 bug fixed - qsort error : segmentation fault
//                  file input
//       2017 04 13 input form fixed
// ---

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxL 1010
#define wordL 110
#define ON 1
#define OFF 0
int HEAD=OFF;//whether the targert is the first one in list or not
int nowC=0;//num of word in list now

typedef struct l_node{
	char word[wordL];
	int count;
	struct l_node *next;
}wordCnt;

//find in list
wordCnt* lfind(char* word,wordCnt* test)
{
	wordCnt *now=test,*last=test;
	while(now!=NULL)
	{
		if(strcmp(now->word,word)==0)
		{
			if(now==test)//now is at the first one in list
			{
				HEAD=ON;
				return now;
			}
			else return last;
		}
		last=now;
		now=now->next;
	}
	return NULL;
}

//add new node
wordCnt* addNode(wordCnt* test,char* word)
{
	wordCnt *tmp=(wordCnt*)malloc(sizeof(wordCnt)+1);
	strcpy(tmp->word,word);
	tmp->count=1;
	tmp->next=test;
	return tmp;
}

//delete node
wordCnt* delNode(wordCnt* test,wordCnt* last)
{
	wordCnt *tmp=last->next;
	if(HEAD==ON)//test->word=target
	{
		HEAD=OFF;
		if(test->count > 0)
		{
			test->count--;
			return test;
		}
		else{
			free(test);
			nowC--;
			return tmp;
		}
	}
	if(tmp->count > 0)
	{
		tmp->count--;
		return test;
	}
	last->next=tmp->next;
	nowC--;
	free(tmp);
	return test;
}

//sorting & print
int cmp_all(const void*a,const void*b)
{
	wordCnt *ta=*(wordCnt**)a;
	wordCnt *tb=*(wordCnt**)b;
	if(ta->count == tb->count)
		return strcmp(ta->word,tb->word);
	return ta->count < tb->count?1:-1;
}
void my_sort_print(wordCnt* test)
{
	//build an array to stored linked list pointer and sort the array
	wordCnt **sortArr=malloc(sizeof(wordCnt)*(nowC));
	wordCnt *ptr=test;
	int i=0;

	while(ptr!=NULL)
	{
		sortArr[i]=ptr;
		ptr=ptr->next;
		i++;
	}
	qsort(sortArr,nowC,sizeof(wordCnt*),cmp_all);
	//data type is struct pointer,not struct

	for(i=0;i<nowC;i++)
	{
		printf("%s:\t%d\n",sortArr[i]->word,sortArr[i]->count);
	}
	return;
}

//main
int main(int argc,char *argv[])
{
	FILE *fp;
	wordCnt *hList,*last,*now;
	char line[wordL]={'\0'},*ptr;
	int isExist=OFF,isDelete=OFF;
	fp=fopen(argv[argc-1],"r");

	while(fgets(line,wordL,fp))
	{
		ptr=line;
		*(ptr+strlen(line)-1)='\0';//del '\n'

		//if the first char is '-',state = delete
		if(*ptr=='-')isDelete=ON;
		if(isDelete==ON)ptr=line+1;

		//search word in list and return previous word pointer
		if((last=lfind(ptr,hList))!=NULL)
		{
			if(isDelete==ON)hList=delNode(hList,last);
			else
			{
				if(strcmp(last->word,ptr)==0)now=last;
				else now=last->next;
				now->count++;
			}
			isExist=ON;
			HEAD=OFF;
		}
		if(isExist==OFF&&isDelete==OFF)
		{
			hList=addNode(hList,ptr);
			nowC++;
		}
		isExist=OFF;
		isDelete=OFF;
	}
	if(hList==NULL)printf("Terms not exists!\n");
	else my_sort_print(hList);
	return 0;
}

