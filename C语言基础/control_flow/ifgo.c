#include <stdio.h>
#include <stdlib.h>

#define LEFT    1
#define RIGHT   100
int main()
{
    int sum=0;
    int i;
    int start,end=10;

    i = LEFT;

loop:
    sum +=i;
    i++;

    if(i<=RIGHT)
      goto loop;
    printf("sum %d \n",sum);



    return 0;
}
