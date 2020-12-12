#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *strlen & sizeof
 *strcpy & strncpy
 *strcat & strncat
 *strcmp & strncmp
 *
 * */
#define STRSIZE 32
int main(){

	char str[STRSIZE] = "hello";
	char str1[STRSIZE] = "aworld";
	char str2[STRSIZE] = "helloa";
	
	printf("strcmp %d \n",strcmp(str,str1));
	printf("strncmp %d \n",strncmp(str,str2,5));

#if 0
	char str[STRSIZE] = "hello";
//	strcat(str," ");
//	strcat(str,"world");
//	puts(str);
	puts(str);
	strncat(str," ",STRSIZE);
	strncat(str,"world",STRSIZE);
	puts(str);
#endif

#if 0
	char str[STRSIZE];
	
//	strcpy(str,"abc");
//	strcpy(str,"abceeeeeeeee");
	strncpy(str,"abceeeeeeeee",STRSIZE);
	puts(str);

#endif


#if 0
	char str[10]="hello\0abc";
	printf("strlen %ld \n",strlen(str));
	printf("sizeof %ld \n",sizeof(str));
#endif
	return 0;
}
