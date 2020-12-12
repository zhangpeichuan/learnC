#include <stdio.h>
#include <stdlib.h>

#define N	10

static void fibonacci(void){
	int fib[10] ={1,1};
	int length=sizeof(fib)/sizeof(fib[0]);
	int i,j,tmp;
	for(i=2;i<length;i++){
		fib[i]=fib[i-1]+fib[i-2];
	}
	for(i=0;i<length;i++){
	printf("fib[%d] ",fib[i]);
	}
	printf("\n");
	i=0;
	j=length-1;
	while(i<j)
	{
		
		tmp = fib[j];
		fib[j]=fib[i];
		fib[i]=tmp;
		i++;
		j--;
	}
	for(i=0;i<length;i++){
	printf("fib[%d] ",fib[i]);
	}
	printf("\n");
}
void print_array(int *a[]){
	int i;
	int size = sizeof(a)/sizeof(a[0]);
	for(int i=0;i<size;i++){
		printf(" %d ",a[i]);
	}
}
//冒泡排序
static void bubbleSort(void){
	int a[N] = {12,8,45,30,98,67,2,7,68,11};
	int size = sizeof(a)/sizeof(a[0]);
	for(int i=0;i<size;i++){
		printf(" %d ",a[i]);
	}
	printf("\n");


	int i,j,tmp,count_swap,count_compare;
	for(i=0;i<size-1;i++){
		for(j=0;j<size-1-i;j++){
			if(a[j]>a[j+1]){
			tmp = a[j];
			a[j] = a[j+1];
			a[j+1] = tmp;
			count_swap++;
			}else{
			count_compare++;
			}

		}
	for(int i=0;i<size;i++){
		printf(" %d ",a[i]);
	}
	printf("\n");
	}

	printf(" 排序交换%d次比较%d次\n",count_swap,count_compare);
}
//交换排序
static void partition(void){
	int a[N] = {12,8,45,30,98,67,2,7,68,11};
	int size = sizeof(a)/sizeof(a[0]);
	
	int i,j,pivote,pivoteKey,count_swap,count_compare;
	for(int i=0;i<size;i++){
		printf(" %d ",a[i]);
	}
	
	for(i=0;i<size-1;i++){
		pivote=1+i;
		for(j=pivote;j<size;j++){
			if(a[j]<a[pivote]){
				pivote=j;
			}
			count_compare++;
		}
		if(i!=pivote){
			pivoteKey = a[pivote];
			a[pivote]=a[i];
			a[i]=pivoteKey;
			count_swap++;
		}
			
		for(int i=0;i<size;i++){
		printf(" %d ",a[i]);
	}
		printf("\n");
	}
	for(int i=0;i<size;i++){
		printf(" %d ",a[i]);
	}
	printf(" 排序交换%d次比较%d次\n",count_swap,count_compare);
}
static void base_convert(){
	int num,base;
	int i=0,n[128];
	printf("Please enter the converted num:");
	scanf("%d",&num);
	printf("Please enter the converted base:");
	scanf("%d",&base);
		
	do{
		n[i]= num%base;
		printf(" 百分号 %d 斜杠  %d\n",num%base,num/base);
		num = num/base;
		i++;
	}while(num!=0);
	for(i--;i>=0;i-- ){
		if(n[i]>=10)
			printf("%c",n[i]-10+'A');
		else printf("%d",n[i]);
	}

	printf("\n");
}
//删除法求质数
static void prime(int n){
	int a[1001]={0};
	int len = sizeof(a)/sizeof(a[0]);
	//打印
	for(int i=0;i<len;i++){
		printf("%c \n",a[i]);
	}
	printf("\n");

}

static void cal_prime(){
	char primer[1001]={0};
	int i,j;

	for(i=2;i<1001;i++){
		if(primer[i] ==0){
		for(j= i*2;j<1001;j+=i){
			primer[j]=-1;
		}
	}
	
	}
	for(int i=2;i<1001;i++){
		if(primer[i]==0){
		printf("%d ",i);
		}
	}
	printf("\n");


}
int main(){
	
	//fibonacci();
	//bubbleSort();
	//partition();
	//base_convert();
	cal_prime();
	return 0;
}
