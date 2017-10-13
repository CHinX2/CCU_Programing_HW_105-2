// Homework #7
// Hashing
//---
// insert,delete,find(>0 only)
//---
// Build : 2017 05 20
// Log : 2017 05 20 - SF Finish!
//		 2017 05 21 - lib build Finish!
//					  All Done
//---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash77.h"

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

