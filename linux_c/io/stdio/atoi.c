#include <stdio.h>
#include <stdlib.h>

int main(){
	char buf[1024];
	int year = 2014,month = 5,day =13;

	printf("%d-%d-%d\n",year,month,day);

	sprintf(buf,"%d-%d-%d",year,month,day);
	puts(buf);

	snprintf(buf,1024,"%d-%d-%d",year,month,day);
	puts(buf);










	char str[] = "123456";
	char str1[] = "123a456";
	char str2[] = "123\0456";
	printf("%d\n",atoi(str));
	printf("%d\n",atoi(str1));
	printf("%d\n",atoi(str2));


	return 0;
}
