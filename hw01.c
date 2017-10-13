// Homework 01
// ===
// Compose a program performs pattern substitution
// -Basic:only sub first pattern
// -[-i]:case insensitive
// -[-a]:sub all matched patterns
// ==Requirement==
// sub [-i] [-a] target_pat source_pat
// ===
// Build : 2017 02 27
// Log : 2017 02 27 Standard Format-1
//       2017 02 28 SF-2
//       2017 03 01 pineapple->pinebanana
// ===

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1005
#define ON 1
#define OFF 0

char *allLower(char*);
int main(int argc,char*argv[])
{
	char *pSource,*pTarget,*pNow,*pNow2,*pHere;
	char line[MAX]={'\0'},line2[MAX]={'\0'};
	char target[MAX]={'\0'},source[MAX]={'\0'};
	int Insen = OFF,All = OFF;
	int i,length,basic=0;
	//pattern insert
	if(argc < 3)exit(0);
	if(argc > 5)exit(0);
	for(i=1;i<argc;i++)
	{
		if(strcmp(argv[i],"-i")==0)
		{
			Insen=ON;
		}
		else if(strcmp(argv[i],"-a")==0)
		{
			All=ON;
		}
		else if(argc-i==2)break;
		else exit(0);
	}
	strcpy(target,argv[i]);
	pTarget=target;
	length=strlen(target);
	i++;
	strcpy(source,argv[i]);
	pSource=source;
	//text insert
	while(fgets(line,MAX,stdin))
	{
		pNow=pNow2=line;
		if(Insen==ON)
		{
			strcpy(line2,line);
			pNow=line2;
			pNow=allLower(pNow);
			pTarget=allLower(pTarget);
		}
		pHere=strstr(pNow,pTarget);
		while(pHere!=NULL)
		{
			if(basic!=0&&All==OFF)break;
			while(pNow!=pHere)
			{
				putchar(*pNow2);
				pNow2++;
				pNow++;
			}
			printf("%s",pSource);
			pNow=pNow+length;
			pNow2=pNow2+length;
			basic++;
			if(All==ON)
			{
				pHere=strstr(pNow,pTarget);
			}
			else break;
		}
		printf("%s",pNow2);
		
	}
	return 0;
}

char *allLower(char* text)
{
	int i,len;
	len=strlen(text);
	for(i=0;i<len;i++)
	{
		*text=tolower(*text);
		text++;
	}
	return text-len;
}

