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
    if(score>=90){
        printf("A");
    }else if(score>=80){
        printf("B");
    }else if(score>=70){
        printf("C");
    }else if(score>=60){
        printf("D");
    }else{
        puts("E");
    }
}
void scoreloop()
{
    int quit;
    while(quit==0){
    score();
    printf("0 for quit\n");
    scanf("%d",&quit);
    }
}
/*
 *闰年判断条件，被4整除但不能被100整除或者被400整除
 * */
void leapYear()
{
    int year;
    puts("Please input a year");
    scanf("%d",&year);
    if((year %4 ==0) && (year %100 !=0) || year %400 ==0)
      printf("%d is leap year.\n",year);
    else
      printf("%d is not leap year.\n",year);

}
int main()
{
    leapYear();
    score();
    int x = 1,y = 1, z = 2;
    if(x ==y)
    {
     if(y==z)
            printf("a==b==c\n");
    
    }
    else
      printf("a!=b\n");
   /*
    if(x ==y)
        if(y==z)
            printf("a==b==c\n");
    else
      printf("a!=b\n");
    */

    int a =9 , b = 10;
#if 0
    if(b++ < a)
      printf("1\n" );
    else
      printf("0\n" );
      
    printf("a = %d , b = %d\n",a,b);
#endif
    printf("a = %d , b = %d\n",a,b);
    printf(" %d\n",(++a >=b?++a:b++));
    printf("a = %d , b = %d\n",a,b);
    printf(" %d\n",(++b <a?++a:b++));
    printf("a = %d , b = %d\n",a,b);
    return 0;
}
