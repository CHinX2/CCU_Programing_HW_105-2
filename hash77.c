#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (1<<25)-1 //size of hash table

typedef struct h{
	char key[84];
	int val;
	struct h *next;
}hNode;

hNode* hFind(hNode*,char*);
unsigned long hash33(char*);
hNode* hInsert(hNode*,char*);
int hDelete(hNode*,char*);

//finding match node and return it address
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

//hashing key into a number by 33(1<<5+1)
unsigned long hash33(char* key)
{
	unsigned long hashv=0;
	unsigned long len=strlen(key);
	unsigned long i;
	for(i=0;i<len-1;i++)
	{
		hashv=(hashv<<5)+hashv+key[i];
		while(hashv>=MAX)hashv-=MAX;
		//when num>=MAX,sub it til num<MAX
	}
	while(hashv>=MAX)hashv-=MAX;
	return hashv;
}

// insert new node when the key do not exist in the matching list
// if it exists,val+1
//return the first one address of list
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

//if the key exists,val-1 when it > 0
//can check delet or not by return value : yes-1/no-0
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
