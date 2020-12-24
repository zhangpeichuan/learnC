#include <stdio.h>

int main(){
    char *ptr = "abc";
    printf("%s  \n",ptr);
    ptr[0] = 'x';
    printf("%s  \n",ptr);
    return 0;
    
}
