#ifndef _HASH77_H
#define _HASH77_H

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

#endif

