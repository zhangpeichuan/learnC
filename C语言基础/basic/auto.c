#include <stdio.h>
#include <stdlib.h>
void func_auto(void)
{
    auto int x = 0;
    x++;
    printf("auto %p-> %d\n",&x,x);

}
void func_static(void)
{
    static int x = 0;
    x++;
    printf("static %p-> %d\n",&x,x);

}
int main()
{
    auto int i;
    int j;
    printf("i = %d\n",i);
    printf("j = %d\n",j);

    static int k;
    printf("k = %d\n",k);


    func_auto();
    func_auto();
    func_auto();

    func_static();
    func_static();
    func_static();


    return 0;
}
