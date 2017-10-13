// Homework 03
// Contacts
// ---
// -Insert : add a new info -> i,[id],[name],[phone],[age]
// -Delete : delete a exist info -> d,[id]
// -Update : renew one's info -> u,[id],[name],[phone],[age]
// -Find : find fit info -> f.string
// -List : print all data
// -Sort : sortint -> s,[id/name/phone/age]
// -Write : write data into file -> w,[filename]
// ---
// Build : 2017 03 13
// Log : 2017 03 13 SF
//       2017 03 16 3-1 -insert -list ok
//       2017 03 20 3-2 -delete -update ok
//       2017 03 21 3-2 -find -sort -fp ok
//                      -delete update : useless space clean by sorting 
// ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxStu 15000
#define nameL 105
#define idL 50
#define phoneL 30
#define ON 1
#define OFF 0
#define MAX 1000000000

struct addr{
	int number;
	char id[idL];
	char name[nameL];
	char phone[phoneL];
	int age;
};
//exist or not
int isExist(struct addr* test1,char* test2,int num)
{
	if(num==0)return 0;
	int i;
	for(i=0;i<num;i++)
	{
		if(strcmp(test1[i].id,test2)==0)return i+1;
	}
	return 0;
}
//struct copy
void strtCpy(struct addr* test1,struct addr* test2,int num,int index)
{
	strcpy(test1[num].id,test2->id);
	strcpy(test1[num].name,test2->name);
	strcpy(test1[num].phone,test2->phone);
	test1[num].age=test2->age;
	test1[num].number=index+1;
	printf("%s,%s,%s,%d\n",test1[num].id,test1[num].name,test1[num].phone,test1[num].age);
	return;
}
//read in til ','
char *dataInput(char* test,char*c,int len)
{
	int k=0;
	while(*c!=','&&*c!='\n'&&k<len)
	{
		test[k]=*c;
		k++;
		c++;
	}
	test[k]='\0';
	c++;
	return c;
}
//remove struct
void rmStrt(struct addr* test,int num)
{
	char strNull[1]={'\0'};
	printf("%s,%s,%s,%d\n",test[num].id,test[num].name,test[num].phone,test[num].age);

	strcpy(test[num].id,strNull);
	strcpy(test[num].name,strNull);
	strcpy(test[num].phone,strNull);
	test[num].age=0;
	test[num].number=MAX;
	return;
}
//finding target in id/name
void partFind(struct addr* test,char* targ,int num)
{
	int i;
	int suz,tmp;
	for(i=0;i<num;i++)
	{
		if(strstr(test[i].name,targ)!=NULL||strstr(test[i].id,targ)!=NULL||strstr(test[i].phone,targ)!=NULL)
		{
			printf("%s,%s,%s,%d\n",test[i].id,test[i].name,test[i].phone,test[i].age);
		}
		else
		{
			suz=atoi(targ);
			if(test[i].age==suz)printf("%s,%s,%s,%d\n",test[i].id,test[i].name,test[i].phone,test[i].age);
			else
			{
				tmp=test[i].age%10;
				if(tmp!=0&&tmp==suz)printf("%s,%s,%s,%d\n",test[i].id,test[i].name,test[i].phone,test[i].age);
				tmp=test[i].age%100;
				if(tmp!=0&&tmp==suz)printf("%s,%s,%s,%d\n",test[i].id,test[i].name,test[i].phone,test[i].age);
				tmp=test[i].age/10;
				if(tmp!=0&&tmp==suz)printf("%s,%s,%s,%d\n",test[i].id,test[i].name,test[i].phone,test[i].age);
				tmp=(test[i].age/10)%10;
				if(tmp!=0&&tmp==suz)printf("%s,%s,%s,%d\n",test[i].id,test[i].name,test[i].phone,test[i].age);
			}
		}
	}
	return;
}
//compair function for all part
int cmp_id(const void*a,const void*b)
{
	return strcmp((*(struct addr*)a).id,(*(struct addr*)b).id);
}
int cmp_name(const void*a,const void*b)
{
	return strcmp((*(struct addr*)a).name,(*(struct addr*)b).name);
}
int cmp_phone(const void*a,const void*b)
{
	return strcmp((*(struct addr*)a).phone,(*(struct addr*)b).phone);
}
int cmp_age(const void*a,const void*b)
{
	return(*(struct addr*)a).age>(*(struct addr*)b).age?1:-1;
}
int cmp_num(const void*a,const void*b)
{
	return(*(struct addr*)a).number>(*(struct addr*)b).number?1:-1;
}

int main()
{
	struct addr info[MaxStu];
	int readinCnt=0,rmCnt=0,nowinCnt=0;
	int i;
	int Insert=OFF,List=OFF,Delete=OFF,Update=OFF,Find=OFF,Sort=OFF,Write=OFF,Quit=OFF;
	char *now;
	char line[MaxStu];
//Command
	printf("Please input command(i/d/u/f/l/s/w/q) and data.\n");
	while(fgets(line,MaxStu,stdin))
	{
		now=line;
		switch(*now)
		{
			case 'i':
				Insert = ON;
				break;
			case 'd':
				Delete = ON;
				break;
			case 'u':
				Update = ON;
				break;
			case 'f':
				Find = ON;
				break;
			case 'l':
				List = ON;
				break;
			case 's':
				Sort = ON;
				break;
			case 'w':
				Write = ON;
				break;
			case 'q':
				Quit = ON;
				break;
		}
		now+=2;
		if(Insert==ON)
		{
			struct addr tmp;
			now=dataInput(tmp.id,now,idL);
			now=dataInput(tmp.name,now,nameL);
			now=dataInput(tmp.phone,now,phoneL);
			tmp.age=atoi(now);

			if(isExist(info,tmp.id,readinCnt)==0)
			{
				strtCpy(info,&tmp,readinCnt,nowinCnt);
				readinCnt++;
				nowinCnt++;
			}
			else
			{
				printf("Insert error! studentID is exists!\n");
			}
			Insert=OFF;
		}
		if(Delete==ON)
		{
			char idTmp[idL];
			int check;
			dataInput(idTmp,now,idL);
			
			if((check=isExist(info,idTmp,readinCnt))==0)
			{
				printf("Delete error! studentID not exists!\n");
			}
			else
			{
				rmStrt(info,check-1);
				rmCnt++;
			}
			Delete=OFF;
		}
		if(Update==ON)
		{
			struct addr tmp;
			char idTmp[idL];
			int check;
			now=dataInput(idTmp,now,idL);
			now=dataInput(tmp.id,now,idL);
			now=dataInput(tmp.name,now,nameL);
			now=dataInput(tmp.phone,now,phoneL);
			tmp.age=atoi(now);

			if((check=isExist(info,idTmp,readinCnt))!=0)
			{
				    strtCpy(info,&tmp,check-1,check-1);
			}
			else
			{
				    printf("Update error! studentID not exists!\n");
			}
			Update=OFF;
		}
		if(Find==ON)
		{
			char findT[nameL];
			dataInput(findT,now,nameL);

			partFind(info,findT,readinCnt);

			Find=OFF;
		}
		if(List==ON)
		{
			if(readinCnt==0)List=OFF;
			else{
				for(i=0;i<readinCnt;i++)
				{
					printf("%s,%s,%s,%d\n",info[i].id,info[i].name,info[i].phone,info[i].age);
				}
				List=OFF;
			}
		}
		if(Sort==ON)
		{
			char *sortT=(char*)malloc(sizeof(char)*10);
			dataInput(sortT,now,10);
			int idS=OFF,nameS=OFF,phoneS=OFF,ageS=OFF;

			if(strcmp(sortT,"studentID")==0)idS=ON;
			else if(strcmp(sortT,"name")==0)nameS=ON;
			else if(strcmp(sortT,"phone")==0)phoneS=ON;
			else if(strcmp(sortT,"age")==0)ageS=ON;

			if(idS==ON)
			{
				qsort(info,readinCnt,sizeof(info[0]),cmp_id);
				for(i=0;i<readinCnt;i++)
				{
					if(info[i].number!=MAX)
						printf("%s,%s,%s,%d\n",info[i].id,info[i].name,info[i].phone,info[i].age);
				}
			}
			if(nameS==ON)
			{
				qsort(info,readinCnt,sizeof(info[0]),cmp_name);
				for(i=0;i<readinCnt;i++)
				{
					if(info[i].number!=MAX)
					    printf("%s,%s,%s,%d\n",info[i].id,info[i].name,info[i].phone,info[i].age);
				}
			}
			if(phoneS==ON)
			{
				qsort(info,readinCnt,sizeof(info[0]),cmp_phone);
				for(i=0;i<readinCnt;i++)
				{
				    if(info[i].number!=MAX)
				     	printf("%s,%s,%s,%d\n",info[i].id,info[i].name,info[i].phone,info[i].age);
				}
			}
			if(ageS==ON)
			{
				qsort(info,readinCnt,sizeof(info[0]),cmp_age);
				for(i=0;i<readinCnt;i++)
				{
				    if(info[i].number!=MAX)
				     	printf("%s,%s,%s,%d\n",info[i].id,info[i].name,info[i].phone,info[i].age);
				}
			}
			Sort=OFF;
		}
		if(Write==ON)
		{
			FILE *fp;
			char fileN[nameL];
			dataInput(fileN,now,nameL);
			fp=fopen(fileN,"w+");

			for(i=0;i<readinCnt;i++)
			{
				 if(info[i].number!=MaxStu)
				 	fprintf(fp,"%s,%s,%s,%d\n",info[i].id,info[i].name,info[i].phone,info[i].age);
			}
			printf("Writing file successful!\n");
			fclose(fp);
			Write=OFF;
		}
		if(Quit==ON)
		{
			exit(0);
		}
		qsort(info,readinCnt,sizeof(info[0]),cmp_num);
		readinCnt-=rmCnt;
		rmCnt=0;
		printf("Please input command(i/d/u/f/l/s/w/q) and data.\n");
	}
	return 0;
}

