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
// ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct b{
	char key[1004];
	int val;
	struct b* left;
	struct b* right;
}bst;

bst* bIns(bst*,char*,int*);
void bDel(bst*,char*);
bst* bFind(bst*,char*);
void bInorder(bst*);
void bCnt(bst*,int);
int bStore(bst*,bst**,int*);
int cmp_d(const void*,const void*);
void line(void);

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
//Print line
void line(void)
{
	printf("----------\n");
	return;
}
//Insert
bst* bIns(bst* root,char* key,int* now)
{
	if(root==NULL)
	{
		root=(bst*)malloc(sizeof(bst));
		strcpy(root->key,key);
		root->val=1;
		(*now)++;
		return root;
	}
	else if(strcmp(root->key,key)==0)
	{
		root->val++;
		return root;
	}
	else if(strcmp(root->key,key)>0)
	{
		root->left=bIns(root->left,key,now);
		return root;
	}
	else if(strcmp(root->key,key)<0)
	{
		root->right=bIns(root->right,key,now);
		return root;
	}
	return root;
}
//Delete
void bDel(bst* root,char* key)
{
	if(root==NULL)return;
	int i=strcmp(root->key,key);
	if(i==0){
		if(root->val>0)
			root->val--;
		return;
	}
	else if(i>0)
	{
		bDel(root->left,key);
	}
	else if(i<0)
	{
		bDel(root->right,key);
	}
	return;
}
//Find
bst* bFind(bst* root,char* key)
{
	if(root==NULL)return NULL;
	int i=strcmp(root->key,key);
	if(i==0 && root->val>0)return root;
	else if(i>0)
	{
		    return bFind(root->left,key);
	}
	else if(i<0)
	{
		    return bFind(root->right,key);
	}
	return NULL;
}
//Inorder Traversal
void bInorder(bst* root)
{
	if(root==NULL)return;
	bInorder(root->left);
	if(root->val > 0){
		printf("%s\t%d\n",root->key,root->val);
	}
	bInorder(root->right);
	return;
}
//Count
void bCnt(bst* root,int now)
{
	int inst=0;
	bst** bsite=malloc(sizeof(bst)*(unsigned long)now);
	bStore(root,bsite,&inst);
	qsort(bsite,(unsigned long)now,sizeof(bst*),cmp_d);
	int i=0;
	for(i=0;i<now;i++)
	{
		if(bsite[i]->val>0)
			printf("%s\t%d\n",bsite[i]->key,bsite[i]->val);
	}
	return;
}
//Store site
int bStore(bst* root,bst** bsite,int* inst)
{
	if(root==NULL)return *inst;
	bsite[*inst]=root;
	(*inst)++;
	bStore(root->left,bsite,inst);
	bStore(root->right,bsite,inst);
	return *inst;
}
//Compair
int cmp_d(const void* a,const void* b)
{
	return (*(bst**)b)->val - (*(bst**)a)->val;
}








