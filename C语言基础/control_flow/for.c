#include <stdio.h>
#include <stdlib.h>

#define LEFT    1
#define RIGHT   100
int main()
{
    int sum=0;
    int i;
    int start,end=10;

    for(int i= LEFT;i<=RIGHT;i++){
        sum +=i;
    }

    printf("sum %d \n",sum);
    sum = 0;
    i = LEFT;
    for(;i<=RIGHT;i++)
    {
    sum +=i;
    }
    printf("sum %d \n",sum);
    sum = 0;
    i = LEFT;
    for(;;)
    {
    sum +=i;
    i++;
    if(i>RIGHT)
      break;
    }
    printf("sum %d \n",sum);



    return 0;
}
