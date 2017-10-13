// Homeword #6
// Term Count(BST)
// ---
// insert,delete,find,inorder traversal(about key & val>0)
// count(about val : big-to-small & val>0)
// ---
// Build : 2017 05 01
// Log : 2017 05 01 - 6-1 OK
//                    6-2 Seperate
//       2017 05 02 - 6-2 bst.h build test
//                        change main function
// ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst66.h"

int main()
{
	bst *root=NULL;
	int now=0;
	char key[1004]={'\0'};
	char type[15]={'\0'};

	while(scanf("%s",type)==1)
	{
		if(strcmp(type,"inorder")==0)
		{
			printf("inorder\n");
			line();
			bInorder(root);
			line();
		}
		else if(strcmp(type,"count")==0)
		{
			printf("count\n");
			line();
			bCnt(root,now);
			line();
		}
		else
		{
			scanf("%s",key);
			if(strcmp(type,"insert")==0)
			{
				root=bIns(root,key,&now);
			}
			else if(strcmp(type,"delete")==0)
			{
				bDel(root,key);
			}
			else if(strcmp(type,"find")==0)
			{
				bst *p=bFind(root,key);
				if(p!=NULL){
					printf("find\n");
					line();
					printf("%s\t%d\n",p->key,p->val);
					line();
				}
			}
		}
	}
	return 0;
}

