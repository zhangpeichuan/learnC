#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define     STRSIZE     20 
//strcpy strncpy 
static char *mystrcpy(char * dst,const char * src){
    char *ret = dst;
    if(dst !=NULL && src !=NULL)
        while((*dst++ = *src++) !='\0');
    return ret;
}
static char *mystrncpy(char *dest,const char *src,int n){
    int i;
    for(i = 0;i< n && (dest[i] = src[i]);i++)
                ;
    for(;i< n ;i++)
        dest[i] = '\0';
    return dest;
}
int main(void){
    char str1[] = "Helloworld";
    char str2[STRSIZE];
    puts(str1);
//    mystrcpy(str2,str1);   
    mystrncpy(str2,str1,9);
    puts(str2);
    mystrncpy(str2,str1,10);
    puts(str2);
    mystrncpy(str2,str1,11);
    puts(str2);
    return 0;
}
