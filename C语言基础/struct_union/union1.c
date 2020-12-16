#include <stdio.h>
#include <stdlib.h>

/*
struct {
    int     i;
    char    ch;
    union{
        int a;
        char c;
    }un;
    float   f;
};
union{
    int a;
    double  d;
    struct{
        int array[10];
        float   f;
    }c;

};
*/
//32位无符号数 高16位+低16位的值是多少
union {
    struct{
        uint16_t i;
        uint16_t j;
    }x;
    uint32_t   y;
}a;

int main(){
    //uint32_t == unsigned int
    uint32_t i = 0x11223344;
    printf("前十六位%d\n",(i>>16));
    printf("后十六位%d\n",(i&0xFFFF));
    printf("%d \n",((i>> 16) + i& 0xFFFF));

    a.y = 0x11223344;
    printf("union %d \n",(a.x.i+a.x.j));






    return 0;
}
