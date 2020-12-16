#include <stdio.h>
#include <stdlib.h>
//内存中存放相关类型的补码
union test_un {
    int     i;
    float   f;
    double  d;
    char    ch;
    float   f1;
};

int main(){
    union test_un a;
    union test_un *p = &a;
    a.f = 3.45678;

    printf("sizeof %d\n",sizeof(a));

    printf("a.f = %f\n",a.f);
    printf("%d\n",a.i);
    printf("a.f1 = %f\n",a.f1);
    printf("p->f1 = %f\n",p->f1);





    return 0;
}
