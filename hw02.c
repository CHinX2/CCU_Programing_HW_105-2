// Homework #2
// Sort
// --- 
// *using rand(),srand()
// a.Insertion Sort
// b.Selection Sort
// c.Bubble Sort
// d.Merge Sort
// e.Quick Sort
// ---
// Build : 2017 03 06
// Log : 2017 03 06 SF,Insert,Bub
//       2017 03 07 Select,Quick
//       2017 03 08 Merge 
//					@test4[1000000] -> segmentation fault
//       2017 03 09 Bug fixed->malloc()
//                  test
// ---

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define nA 1000
#define nB 10000
#define nC 100000
#define nD 1000000

void sInsert(int*,int);
void sSelect(int*,int);
void sBub(int*,int);
void sMerge(int*,int);
void sQuick(int*,int);
void mPrint(int*,int*);
void copy(int*,int*,int);
//void qSort(int*,int,int);
void mSort(int*,int*,int,int);
int cmp(const void*,const void*);

int main()
{
	int test1[nA],test2[nB],test3[nC];
	int test4[nD];
	int i;

//  [Time]
//	clock_t start,end;
//	double diff;//ms
//	start=clock();
//	end=clock();
//	diff=end-start;
//	printf("%f\n",diff/CLOCKS_PER_SEC);

	srand(time(NULL));
	for(i=0;i<nA;i++)test1[i]=rand();
	for(i=0;i<nB;i++)test2[i]=rand();
	for(i=0;i<nC;i++)test3[i]=rand();
	for(i=0;i<nC;i++)test4[i]=rand();

//test1
	sInsert(test1,nA);
	sSelect(test1,nA);
	sBub(test1,nA);
	sMerge(test1,nA);
	sQuick(test1,nA);
//test2
	sInsert(test2,nB);
	sSelect(test2,nB);
	sBub(test2,nB);
	sMerge(test2,nB);
	sQuick(test2,nB);
//test3
	sInsert(test2,nB);
	sSelect(test2,nB);
	sBub(test2,nB);
	sMerge(test3,nC);
	sQuick(test3,nC);
//test4
	sMerge(test4,nD);
	sQuick(test4,nD);

	return 0;
}
void mPrint(int*test,int*test2)
{
	int i;
	printf("Before	After\n");
	for(i=0;i<100;i++)
	{
		 printf("%d	%d\n",test[i],test2[i]);
	}
	return;
}
void sInsert(int*test,int size)
{
	int result[size];
	int i,j,tmp;
	copy(result,test,size);
	for(i=1;i<size;i++)
	{
		tmp=result[i];
		for(j=i-1;j>=0&&result[j]>tmp;j--)
		{
			result[j+1]=result[j];
		}
		result[j+1]=tmp;
	}
	printf("Insertion Sort\n");
	mPrint(test,result);
	return;
}
void sSelect(int*test,int size)
{
	int result[size];
	int i,j,min,tmp;
	copy(result,test,size);
	for(i=0;i<size;i++)
	{
		min=i;
		for(j=i+1;j<size;j++)
		{
			if(result[min]>result[j])min=j;
		}
		if(i!=min)
		{
			tmp=result[min];
			result[min]=result[i];
			result[i]=tmp;
		}
	}
	printf("Selection Sort\n");
	mPrint(test,result);
	return;
}
void sBub(int*test,int size)
{
	int result[size];
	int i,j,tmp;
	copy(result,test,size);
	for(i=size-1;i>0;i--)
	{
		for(j=0;j<i;j++)
		{
			if(result[j]>result[j+1])
			{
				tmp=result[j+1];
				result[j+1]=result[j];
				result[j]=tmp;
			}
		}
	}
	printf("Bubble Sort\n");
	mPrint(test,result);
	return;
}
void sMerge(int*test,int size)
{
    int *result=(int*)malloc(sizeof(int)*size);
    int *tmp=(int*)malloc(sizeof(int)*size);
    copy(result,test,size);
    mSort(result,tmp,0,size-1);
    printf("Merge Sort\n");
    mPrint(test,result);
    free(result);
    free(tmp);
    return;
}
void sQuick(int*test,int size)
{
    int *result=(int*)malloc(sizeof(int)*size);
    copy(result,test,size);
    qsort(result,size,sizeof(result[0]),cmp);
    printf("Quick Sort\n");
    mPrint(test,result);
    free(result);
    return;
}
void copy(int*test,int*source,int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		test[i]=source[i];
	}
	return;
}
void mSort(int*test,int*tmp,int front,int end)
{
	if(front>=end)return;
	int size=end-front;
	int mid=(size/2)+front;
	int f1=front,e1=mid,f2=mid+1,e2=end;
	int now=front;
	mSort(test,tmp,f1,e1);
	mSort(test,tmp,f2,e2);
	while(f1<=e1&&f2<=e2)
	{
		if(test[f1]<test[f2])tmp[now++]=test[f1++];
		else tmp[now++]=test[f2++];
	}
	while(f1<=e1)tmp[now++]=test[f1++];
	while(f2<=e2)tmp[now++]=test[f2++];
	for(now=front;now<=end;now++)
	{
		test[now]=tmp[now];
	}
	return;
}
int cmp(const void*s1,const void*s2)
{
	return *(int*)s1-*(int*)s2;
}
/*void qSort(int*test,int front,int end)
{
	if(front>end)return;
	int mid=test[end];
	int left=front,right=end-1;
	int tmp;
	while(left<right)
	{
	    while(test[left]<mid&&left<right)left++;
	    while(test[right]>=mid&&left<right)right--;
	    tmp=test[left];
	    test[left]=test[right];
	    test[right]=tmp;
	}
	if(test[left]>=test[end])
	{
	     tmp=test[left];
	     test[left]=test[end];
	     test[end]=tmp;
	}
	else left++;
	if(left!=0)qSort(test,front,left-1);
	qSort(test,left+1,end);
	return;
}*/

