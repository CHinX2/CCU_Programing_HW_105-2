#ifndef _BST66_H
#define _BST66_H

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

#endif

