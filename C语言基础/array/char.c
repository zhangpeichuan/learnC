#include <stdio.h>
#include <stdlib.h>

#define N	10
int main(){
	char str[N] = {'a','b','c'},str1[N],str2[N],str3[N];
	int i;

//(F)	str = "hello";
	scanf("%s%s%s",str1,str2,str3);
	printf("%s\n%s\n%s\n",str1,str2,str3); 

	puts(str);
	scanf("%s",str);

	printf("%s",str);
	puts(str);
	//gets(str);
	//puts(str);
		
/*	
	for(i=0;i<N;i++){
		printf("%c ",str[i]);
	}
	printf("\n");

*/

	return 0;
}
