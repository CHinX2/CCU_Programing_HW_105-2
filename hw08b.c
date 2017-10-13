// Homework 08
//Chinese word segmentation
// ---
// Build : 2017 05 28
// Log : 2017 05 28 - SF
//       2017 06 02 - insert
//       2017 06 03 - insert & hash OK
//                    bug fix ->del extra char
// ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WordL 60

typedef struct a{
	char key[WordL];
	int cnt;
	struct a* next;
}cNode;

int getline(char*);
cNode* insert(cNode*,char*);
cNode* wSearch(cNode*,char*);
unsigned long cHash(char*);
int wSeg(char*,cNode*);

int main(int argc,char* argv[])
{
	int stin = 0;
	FILE *dic;
	FILE *text;
	if(argc==3)
	{
		dic=fopen(argv[argc-2],"r");
		text=fopen(argv[argc-1],"r");
	}
	else if(argc==2)
	{
		dic=fopen(argv[argc-1],"r");
		stin = 1;
	}

	char keyin[WordL]={'\0'};
	cNode** dtab=malloc(sizeof(cNode*)*100);
	while(fgets(keyin,WordL,dic))
	{
		//		printf("ist ");

		char* ptr=keyin;
		int k = keyin[0];
		while(k>=0)
		{
			ptr++;
			k=*ptr;
			if(*ptr=='\0')break;
		}
		if(*ptr!='\0')
		{
			char head[3]={'\0'};
			memcpy(head,ptr,2);
			if(k<0){
				unsigned long num = cHash(head);
				//				printf("head:%s ",head);
				*(ptr+strlen(ptr)-1)='\0';
				dtab[num] = insert(dtab[num],ptr);
				//				printf("success\n");
			}
		}

	}

	char line[10000]={'\0'};
	if(stin == 0)
	{
		while(fgets(line,10000,text))
		{
			char* ptr = line;
			char k[5]={'\0'};
			while(*ptr != '\0' && *ptr != '\n' && *ptr)
			{
				int n,len;
				while(*ptr < 0)
				{
					char head[3]={'\0'};
					memcpy(head,ptr,2);
					n = cHash(head);
					len = wSeg(ptr,dtab[n]);
					if(len < 2)break;
					ptr+=len;
				}
				int a=0;
				while(*ptr == ' ' ||(*ptr >= 32 && *ptr <= 126))
				{
					a=1;
					putchar(*ptr);
					ptr++;
				}
				if(a==1)
				{
					printf("\n");
					a = 0;
				}
			}
			strcpy(line,k);
			//		printf("end\n");
		}
	}
	else{
		while(fgets(line,10000,stdin))
		{
			char* ptr = line;
			char k[5]={'\0'};
			while(*ptr != '\0' && *ptr != '\n' && *ptr)
			{
				int n,len;
				while(*ptr < 0)
				{
					char head[3]={'\0'};
					memcpy(head,ptr,2);
					n = cHash(head);
					len = wSeg(ptr,dtab[n]);
					if(len < 2)break;
					ptr+=len;
				}
				int a=0;
				while(*ptr == ' ' ||(*ptr >= 32 && *ptr <= 126))
				{
					a=1;
					putchar(*ptr);
					ptr++;
				}
				if(a==1)
				{
					printf("\n");
					a = 0;
				}
			}
			strcpy(line,k);
			//      printf("end\n");
		}
	}

	fclose(dic);
	if(stin==0)fclose(text);
	//	printf("end\n");
	return 0;
}

int getlen(char* key)
{
	int n = strlen(key);
	char* ptr = key;
	char test[3]={'\0'};
	test[0]=-95;
	test[1]=93;
	int i=0;
	while(*ptr!='\0')
	{
		if(*ptr<0){
			char tmp[3]={'\0'};
			memcpy(tmp,ptr,2);
			if(memcmp(tmp,test,2)==0)return i;
			ptr+=2;
			i+=2;
		}
		if(*ptr == ' ' || *ptr == '('|| *ptr == '?')
		{
			key[i]='\0';
			return i;
		}
		else if(*ptr>0 && i>1)return i;
	}
	return n;
}

cNode* insert(cNode* head,char* key)
{
	cNode* tmp = (cNode*)malloc(sizeof(cNode));
	int len = getlen(key);
	//	printf("%d ",len);
	if(len < 3)
	{
		free(tmp);
		return head;
	}
	//	printf("in2 ");
	memcpy(tmp->key,key,len);
	tmp->cnt = 0;
	tmp->next = head;
	//	printf("%s\n",tmp->key);
	return tmp;
}

unsigned long cHash(char* head)
{
	unsigned long n=0;
	int i;
	for(i=0;i<3;i++)
	{
		n+=(head[i]<<5)+head[i];
		if(n>=100)n%=100;
	}
	if(n>=100)n%=100;
	//	printf("hash:%d %s ",(int)n,head);
	return n;
}

int wSeg(char* line,cNode* list)
{
	int i;
	for(i=WordL-1;i>=3;i-=2)
	{
		char *tmp=malloc(sizeof(char)*i);
		memcpy(tmp,line,i-1);
		tmp[i]='\0';
		//		printf("%d ",i);
		if(wSearch(list,tmp)!= NULL )
		{
			return i-1;
		}
	}
	if(line[0]<0)
	{
		char tet[3]={'\0'};
		memcpy(tet,line,2);
		printf("%s\n",tet);
		return 2;
	}
	return 0;
}

cNode* wSearch(cNode* line,char* key)
{
	cNode* now = line;
	unsigned int n = strlen(key);
	while(now != NULL)
	{
		if(strlen(now->key)==n && memcmp(now->key,key,n) == 0)
		{
			now->cnt++;
			printf("%s\n",now->key);
			return now;
		}
		now = now->next;
	}
	return NULL;
}

