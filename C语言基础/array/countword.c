#include <stdio.h>
#include <stdlib.h>

/*
 *
 *adsf adfsd			adsdfsdf
 *sdfdfad 
 *
 * */

int main(){
	char str[128];
	int count = 0,flag=0,i; 
	gets(str);
	for(i=0;i<str[i] !='\0';i++){
		if(str[i] == ' '){
			flag=0;	
		}else{
			if(flag ==0){
				flag=1;
				count++;
			}
		}
	
	}
	printf("count = %d \n",count);
	exit(0);
}
