#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WEIGHT 3.0E-23
#define KQ		950
static void water(void)
{
	float num;
	float sum;

	printf("Please input num:");
	scanf("%f",&num);
	if(num <=0)
	{
		fprintf(stderr,"Input error! \n");
		exit(1);
	}
	sum = num*KQ /WEIGHT;

	printf("total is %e \n",sum);

	return ;
}

static void area(void)
{
	float a,b,c;
	float p,s;

	printf("Please input:");
	scanf("%f%f%f",&a,&b,&c);
	if(a+b <=c || b+c<=a || b+c<=a)
	{
		fprintf(stderr,"EINVAL \n");
		exit(1);
	}
	printf("a = %f \t b = %f \t c= %f\n",a,b,c);
	p=1.0/2*(a+b+c);

	printf("p = %f \n",p);
	s=sqrt(p*(p-a)*(p-b)*(p-c));
	
	printf("area is %f \n",s);

	return ;
	
}
static void root(void)
{
	float a,b,c,disc;
	float x1,x2;
	
	printf("Please input:");
	scanf("%f%f%f",&a,&b,&c);
	disc = b*b-4*a*c;
	if(disc<0)
	{
		fprintf(stderr,"EINVAL \n");
		exit(1);
	}else if (disc ==0){
		printf("x= %f \n",-b/(2*a));
	}else{
		printf("disc %f\n",disc);
		x1=(-b+sqrt(disc))/2*a;
		x2=(-b-sqrt(disc))/2*a;
		printf("x1 = %f x2= %f \n",x1,x2);
	}
	
}

int main()
{
	//water();
	//area();
	root();
}
//一个水分子的质量大约为3.0e-23g,一夸克水大约有950克，编写程序，要求从终端输入水的夸克数，然后，显示这么多夸克水中韩好友多个个水分子
//终端输入三角形的三边长，求面积
//p= 1/2*(a+b+c) s=sqrt[p(p-a)(p-b)(p-c)]
//从终端输入abc的值，求方程的跟
//ax^2+bx+c=0,设b^2 -4ac>0
//x1=(-b+sqrt(b*b-4ac)/2a
//x2=(-b-sqrt(b*b-4ac)/2a
