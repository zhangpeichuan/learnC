 #include <stdio.h>
 #include <stdlib.h> 
 #include "proj.h"

static int i = 100;

static void func(void)
{

    printf("[%s]: i = %d\n",__FUNCTION__,i);

}
void call_func()
{
    func();
}
