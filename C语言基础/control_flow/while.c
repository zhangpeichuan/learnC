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
    while(i<=RIGHT)
    {
    sum +=i;
    i++;
    }
    printf("sum %d\n",sum);
    */
    int start,end=10;

    printf("Please enter:");
    scanf("%d",&start);
    while(start<=end)
    {
        sum +=start;
        start++;
    }
    printf("start %d \n",start);
    printf("sum %d \n",sum);


    return 0;
}
