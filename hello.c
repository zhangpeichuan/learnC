#include <stdio.h>
#include <stdlib.h>

/*
void main(void)
void main(int argc,char **argv);//char *argv[]
int main(int argc,char **argv);
int main(void);
*/
void show_bits(int n)
{
    int i = 0;
    for(i=0;i<32;i++)
        printf("%d",(n&(1u<<(31-i)))!=0?1:0);
    putchar('\n');
}
int main(void)
{

	printf("Hello world!\n");
#if 0
5 8
对应的二进制    0101        1000
============================================
    AND     &   按位与，用来获取后N位的原数据
    按位与(都是1，才为1，否则为0）
    0101
    1000
&   0000---->0(十进制）
============================================
    OR      |   
    按位或（都是0，才是0，否则为1）
    0101
    1000
|   1101---->13（十进制)
=============================================
    XOR     ^
    按位异或(相等才为0，否则为1）
    0101
    1000
^   1101----->13(十进制)
============================================
#endif




    int x = 8;
    printf("x = %d before\n",x);
    show_bits(x);
    printf("右移3位赋值>>=3\n");
    x >>=3;
    show_bits(x);
    printf("右移3位赋值>>=3\n");
    printf("x = %d after\n",x);
    printf("\n"); 
    
    x = 8;
    printf("x = %d before\n",x);
    show_bits(x);
    printf("右移3位赋值<<=3\n");
    x <<=3;
    show_bits(x);
    printf("x = %d after\n",x);
    printf("\n"); 
    
    x = 0x02;
    printf("x = %d before\n",x);
    show_bits(x);
    x &=0x01;
    show_bits(0x01);
    printf("按位与后赋值 x &=0x01\n");
    show_bits(x);
    printf("x = %d after\n",x);
    printf("\n"); 

    x = 0x02;
    printf("x = %d before\n",x);
    show_bits(x);
    x ^=0x01;
    show_bits(0x01);
    printf("按位异或后赋值 x ^=0x01\n");
    show_bits(x);
    printf("x = %d after\n",x);
    printf("\n"); 

    x = 0x02;
    printf("x = %d before\n",x);
    show_bits(x);
    x |=0x01;
    show_bits(0x01);
    printf("按位或后赋值 x |=0x01\n");
    show_bits(x);
    printf("x = %d after\n",x);
    printf("\n"); 






//	exit(0);

}
