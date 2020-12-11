#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
static void test1(float moneyA ,float rateA,float moneyB ,float rateB){
    float sumA,sumB;

   for (int i=1;;i++){
         sumA = moneyA*(1+rateA)*i;
        sumB = moneyB*pow((1+rateB),i);
        if(sumA <=sumB){    
        printf("sumA= %.2f sumB= %.2f year=%d \n",sumA,sumB,i);
        return;
        }else{
        printf("sumA= %.2f sumB= %.2f year=%d \n",sumA,sumB,i);
        }
    }
}
static void test2(){
    int sum1,sum2,num;
    int count1,count2;
    do{
        printf("Please input num:");
        scanf("%d",&num);
        if(num%2 ==0){
            sum2 +=num;
            count2++;
            printf("%d 偶数 sum2 = %d  count2 = %d avg = %d\n",num,sum2,count2,sum2/count2);
        }else{
            sum1 +=num;
            count1++;
            printf("%d 偶数 sum1 = %d  count1 = %d avg = %d\n",num,sum1,count1,sum1/count1);}
        }while(num !=0);
}
static void test3(){
    int sum_a,sum_e,sum_i,sum_o,sum_u;
    char str[1024];
    printf("Please input char:\n");
    scanf("%s",&str);
    printf("%s\n",str);
    for(int i=0 ;i<strlen(str);i++){
        int ch = *(str+i);
        switch (ch)
        {
            case 'A':
            case 'a':
             sum_a +=1;
             break;
        case 'E':
        case 'e':
            sum_e +=1;
            break;
        case'I':
        case 'i':
            sum_i +=1;
            break;
        case 'O':
        case 'o':
            sum_o +=1;
            break;
        case 'U':
        case 'u':
            sum_u +=1;
            break;
        defalut:
            break;
        }

    }

        printf("sum_a%d \n",sum_a);
        printf("sum_e%d \n",sum_e);
        printf("sum_i%d \n",sum_i);
        printf("sum_o%d \n",sum_o);
        printf("sum_u%d \n",sum_u);


}
int fibonacci(int n){
    if (n==0)return 0;
    if (n==1)return 1;
    return fibonacci(n-1)+fibonacci(n-2);
}
static void test4(){
    for(int i=0;i<=40;i++){
    printf("fibonacci f(%d) = %d\n",i,fibonacci(i));
    }
}
void test5(int n)
{
    for(int i=1;i<=n;i++)
    {
    for(int j=1;j<=i;j++)
    {
    printf("%d*%d=%d ",j,i,i*j);
    }
    printf("\n");
    }
}
void isNarcissistic(int i)
{
    long n1,n2,a;
    for(n1=pow(10,i-1);n1< pow(10,i);n1++)
    {
        n2=0;
        for(int j=0;j<i;j++){
            a = pow(10,j);
            a = n1 /a ;
            a = a % 10;
            
            a = pow(a,i);
    
            n2 = n2+a;
        }
        if(n1 == n2){
            printf("n1 %ld\n",n1);
        }


    }
}
void test7()
{
    for(int i=3;i<=4;i++)
    {
    isNarcissistic(i);
    }
    return;
    for(int i=100;i<1000;i++)
    {
        int a,b,c;

        //水仙花数，个十百位的两种取法 依次求余
        //分解个位十位百位
        a = i/1%10;
        b = i/10%10;
        c = i/100%10;
        


        
        if((pow(a,3)+ pow(b,3)+ pow(c,3))==i)
        {
            printf("i %d\n",i);
            printf("i个位 %d\n",i%10);
            printf("i十位 %d\n",i/10-10*i/100);
            printf("i百位 %d\n",i/100);
        }
     }
}
void test6()
{
    int cock, hen, chicken;
    for(cock=0;cock<=20;cock++){
        for(hen=0;hen<=33;hen++){
            for(chicken=0;chicken<=100;chicken++){
                if((cock+hen+chicken==100) && (cock*5+hen*3+chicken/3.0==100))
                  printf("cock %d hen %d chicken%d\n",cock,hen,chicken);
            }
        }

    }
}
int checkPrimeNumber(int n)
{
    int flag=1;
    for(int i=2;i<=n/2;i++){
        if(n%i==0){
            flag=0;
            break;
        }
    }
    return flag;
}
void test8()
{
    for(int i=2;i<100;i++){
        int flag = checkPrimeNumber(i);
        if (flag==0) {
        //    printf("%d 是素数\n",i);
        }else{
            printf("%d 是质数 \n",i);
        }
    }
}

static void test9(){

    int line=6,chars=6;
    char ch;
    for(int i=0;i<line;i++){
        for(ch = 'A'+i;ch<'A'+chars;ch++){
            printf("%c",ch);
        }
        printf("\n");
    }

}
void test10(int n)
{
    int i,j,k;
    for(i=1;i<=n;i++){
        for(j=n-i;j>0;j--){
            printf("#");

        } 
        for(k=1;k<i*2;k++){
                printf("*");
        }
        printf("\n");
     }   
    for(i =1;i<=n-1;i++){
        for(j=0;j<i;j++){
            printf("#");

        }
      for(k=1;k<(n-i)*2;k++){
                printf("*");
        }
        printf("\n");
    
    }
   

    

}
static void test11(){
    int sum;
    int num;
    printf("Please enter the first integer (Q to quit):");
    //判断输入是否是整形合法
    while(scanf("%d",&num)==1){
    sum +=num;
    printf("Please enter the first integer (Q to quit):");
    
    }
    printf("sum = %d",sum);
}
static void test12(){
    float S;
    for(int i=1;;i++){
        S = M_PI*pow(i,2);
        if(S<=100.0){
            printf("r = %d S= %.2f\n",i,S);
        }else{
            printf("r = %d S= %.2f\n",i,S);
            break;
        }
    }
}
int main()
{

   //test1(100,0.1,100,0.05);
    //test2();
   // test3();
   //test4();
  // test5(9);
   //test7();
    //test6();
    //test9();
    //test10(7);
    test11();
    //test12();
    return 0;
}
