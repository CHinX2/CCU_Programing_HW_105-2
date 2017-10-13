// Homework #7
// Hashing
//---
// insert,delete,find(>0 only)
//---
// Build : 2017 05 20
// Log : 2017 05 20 - SF Finish!
//---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (1<<25)-1

typedef struct h{
	char key[84];
	int val;
	struct h *next;
}hNode;

hNode* hFind(hNode*,char*);
unsigned long hash33(char*);
hNode* hInsert(hNode*,char*);
int hDelete(hNode*,char*);

int main()
{
	hNode** hTab=malloc(sizeof(hNode*)*MAX);
	char key[84]={'\0'};
	char state[15]={'\0'};

	while(scanf("%s\t%s",state,key)==2)
	{
		unsigned long site=hash33(key);
		if(strcmp(state,"find")==0)
		{
			printf("find\t%s\n",key);
			hNode* t=(hNode*)malloc(sizeof(hNode));
			t=hFind(hTab[site],key);
			if(t==NULL)
			{
				printf("----------\n");
				printf("Not\tfound!\n");
				printf("----------\n");
			}
			else if(t->val>0)
			{
				printf("----------\n");
				printf("%s\t%d\n",t->key,t->val);
				printf("----------\n");
			}
		}
		else if(strcmp(state,"insert")==0)
		{
			hTab[site]=hInsert(hTab[site],key);
		}
		else if(strcmp(state,"delete")==0)
		{
			hDelete(hTab[site],key);
		}
	}
	return 0;
}

hNode* hFind(hNode* nHead,char* key)
{
	hNode* tmp=(hNode*)malloc(sizeof(hNode));
	tmp=nHead;
	if(nHead==NULL)return NULL;
	if(strcmp(tmp->key,key)==0)return tmp;
	else{
		return hFind(tmp->next,key);
	}
}

unsigned long hash33(char* key)
{
	unsigned long hashv=0;
	unsigned long len=strlen(key);
	unsigned long i;
	for(i=0;i<len-1;i++)
	{
		hashv=(hashv<<5)+hashv+key[i];
		while(hashv>=MAX)hashv-=MAX;
	}
	while(hashv>=MAX)hashv-=MAX;
	return hashv;
}

hNode* hInsert(hNode* nHead,char* key)
{
	hNode* tmp=(hNode*)malloc(sizeof(hNode));
	if(nHead==NULL)
	{
		strcpy(tmp->key,key);
		tmp->val=1;
		tmp->next=NULL;
		return tmp;
	}
	tmp=nHead;
	while(tmp!=NULL)
	{
		if(strcmp(tmp->key,key)==0)
		{
			tmp->val++;
			return nHead;
		}
		tmp=tmp->next;
	}
	strcpy(tmp->key,key);
	tmp->val=1;
	tmp->next=nHead;
	return tmp;
}

int hDelete(hNode* nHead,char* key)
{
	if(nHead==NULL)return 0;
	hNode* tmp=(hNode*)malloc(sizeof(hNode));
	tmp=nHead;
	while(tmp!=NULL)
	{
		if(strcmp(tmp->key,key)==0)
		{
			if(tmp->val>0)tmp->val--;
			return 1;
		}
		tmp=tmp->next;
	}
	return 0;
}

