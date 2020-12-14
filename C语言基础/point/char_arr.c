#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){

#if 0
	char str[] = "I Love China!";	
	char *p = str+7;

	puts(str);
	puts(p);
#endif

#if 0
	char str[] = "hello";
	printf("sizeof = %d strlen %d \n ",sizeof(str),strlen(str));
//F	str = "world";
	strcpy(str,"world");	
	puts(str);
#endif

	char *str = "hello";
	printf("szieof %d strlen %d \n",sizeof(str),strlen(str));
//F	strcpy(str,"world");
	str ="world";
	puts(str);


	return 0;

}
