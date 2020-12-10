#include <stdio.h>
#include <stdlib.h>
/**
 *score [90-100]    A
 *      [80-90]     B
 *      [70-80]     C
 *      [60-70]     D
 *      [0-60]      E
 */
void score()
{
    int score;
    printf("Please input score [0,100]:\n");
    scanf("%d",&score);

    if(score>100|| score <0){
        fprintf(stderr,"input error!\n");
        exit(0);
    }
    switch(score/10)
    {
    case 10:
    case 9:
      puts("A");
      break;
    case 8:
      puts("B");
      break;
    case 7:
      puts("C");
      break;
    case 6:
      puts("D");
      break;
    default:
      puts("E");
      break;
    }
}
int main()
{
    score();
}
