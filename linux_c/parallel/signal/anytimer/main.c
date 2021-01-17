#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "anytimer.h"


static int job1,job2,job3,job4;

static void f2(void *p){
	printf("f2():%s\n",p);
}
static void f1(void *p){
	printf("f1():%s\n",p);
}
static void f3(void *p){
	printf("f3():%s\n",p);
}
static void f4(void *p){
	printf("f4():%s\n",p);
	if(at_pausejob(job3) == 0){

	}else{
		at_resumejob(job3);	
	}
}
int main(){
	puts("Begin!");
	job1 = at_addjob(4,f1,"aaa");
	if(job1 <0){
		fprintf(stderr,"at_addjob:%s \n",strerror(-job1));
		exit(1);
	}
	job2 = at_addjob(2,f2,"bbb");
	job3 = at_addjob(7,f3,"ccc");
	job4 = at_addjob_repeat(5,f4,"ddd");


	puts("End!");
	while (1)
	{
		write(1,".",1);
		sleep(1);
		//pause();
	}
	

	exit(0);
}
