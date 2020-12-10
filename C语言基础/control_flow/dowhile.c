#include <stdio.h>
#include <stdlib.h>

#define LEFT    1
#define RIGHT   100
int main()
{
    int sum=0;
    int i;
/*
    i=LEFT;
    do
    {
    sum +=i;
    i++;
    }while(i<=RIGHT);
    printf("sum %d\n",sum);
  */  
    int start,end=10;

    printf("Please enter:");
    scanf("%d",&start);
    do 
    {
        sum +=start;
        start++;
    }while(start<=end);
    printf("start %d \n",start);
    printf("sum %d \n",sum);




    return 0;
}
