#include <stdio.h>
#include <unistd.h>

int add_a_and_b(int a,int b)
{
    return a + b;
}
void bin(int n)
{
    for(int i=31;i>=0;i--){
    printf("%ld",n&1<<i?1:0);
    }
}
int main()
{

    int a[0][4];
    printf("%p %d\n",&a,a[0][0]);
    printf("%p %d\n",&a[0][1],a[0][0]);

    unsigned int j;
    int count=0;
    for(j=4;j>=0;j--){
    bin(j);
    printf("  %p %d %X \n",&j,j,j);
    count ++;
    if(j==0) sleep(1);
    if(count>=10) return(0);
    }

    return add_a_and_b(2,3);
}
