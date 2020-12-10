#include <stdio.h>
#include <stdlib.h>
/*
 * int
     fscanf(FILE *restrict stream, const char *restrict format, ...);
 */
#define STRSIZE 32
void scanf_int()
{
	int i;
	float f;
	printf("Please enter:\n");
//scanf("%d,%f",&i,&f);//分割符不需要加
	scanf("%d%f",&i,&f);
	printf("i = %d \n",i);
	printf("f = %f \n",f);
}
int main()
{
//	scanf_int();
	int i;
	char str[STRSIZE];
	char ch;
	
	printf("Please enter:\n");
	
	scanf("%d",&i);
	getchar();//作用吃掉抑制符
	//scanf("%*c%c",&ch);
	scanf("%c",&ch);
	printf("i = %d ,ch = %c %d \n",i,ch,ch);


/*
	printf("Please enter:\n");
	scanf("%s",str);
	printf("str = %s \n",str);

	int i;
	while(1)
	{
		int ret=scanf("%d",&i);
		if(ret !=1)
		{
			printf("error enter:\n");
			break;
		}
		printf("i = %d \n",i);

	};
*/

	return 0;
}

