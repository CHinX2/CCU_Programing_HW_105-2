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
//       2017 03 16 3-1 finish
//       2017 03 20 3-2 SF
// ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxStu 10000
#define nameL 105
#define idL 105
#define phoneL 105
#define ON 1
#define OFF 0

struct addr{
	int number;
	char *id;
	char *name;
	char *phone;
	int age;
};
//exist or not
int isExist(struct addr* test1,char* test2,int num)
{
	if(num==0)return 0;
	int i;
	for(i=0;i<num;i++)
	{
		if(strcmp(test1[i].id,test2)==0)return 1;
	}
	return 0;
}
//struct copy
void strtCpy(struct addr* test1,struct addr* test2,int num)
{
	test1[num].id=test2->id;
	test1[num].name=test2->name;
	test1[num].phone=test2->phone;
	test1[num].age=test2->age;
	test1[num].number=num+1;
	printf("%s,%s,%s,%d\n",test1[num].id,test1[num].name,test1[num].phone,test1[num].age);
	return;
}
//read in til ','
int dataInput(char* test,char*c,int len)
{
	int ptr=0;
	char tmp[len];
	int k=0;
	while(*c!=','&&*c!='\n'&&ptr<len)
	{
		tmp[k]=*c;
		k++;
		ptr++;
		c++;
	}
	tmp[k]='\0';
	test=strdup(tmp);
	ptr++;
	return ptr;
}
//remove struct
//void rmStrt(struct addr* test,int num)
//{
//	char strNull[1]={'\0'};
//	strcpy(test[num].id,strNull);
//	strcpy(test[num].name,strNull);
//	strcpy(test[num].phone,strNull);
//	test[num].age=0;
//	test[num].number=0;
//	return;
//}

int main()
{
	struct addr info[MaxStu];
	int readinCnt=0;
	int i;
	int Insert=OFF,List=OFF,Delete=OFF,Update=OFF,Find=OFF,Sort=OFF,Write=OFF,Quit=OFF;
	char *now,c;
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
			int move;
			move=dataInput(tmp.id,now,idL);
			now+=move;
			move=dataInput(tmp.name,now,nameL);
			now+=move;
			move=dataInput(tmp.phone,now,phoneL);
			now+=move;
			tmp.age=atoi(now);

			if(isExist(info,tmp.id,readinCnt)==0)
			{
				strtCpy(info,&tmp,readinCnt);
				readinCnt++;
			}
			else
			{
				printf("Insert error! studentID is exists!\n");
			}
			Insert=OFF;
		}
/*		if(Delete==ON)
		{
			char idTmp[idL];
			int move;
			dataInput(idTmp,now,idL);
			
			if((move=isExist(info,idTmp,readinCnt))==0)
			{
				printf("Delete error! studentID isn't exists!\n");
			}
			else
			{
				rmStrt(info,move-1);
			}
		}
*/		if(List==ON)
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
		if(Quit==ON)
		{
			exit(0);
		}
		printf("Please input command(i/d/u/f/l/s/w/q) and data.\n");
	}
	return 0;
}


