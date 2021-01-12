#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(){
#pragma omp parallel sections
{
#pragma omp section
	printf("[%d] Hello \n",omp_get_thread_num());
#pragma omp section
	printf("[%d] World \n",omp_get_thread_num());
#pragma omp section
	printf("[%d] Hello1 \n",omp_get_thread_num());
#pragma omp section
	printf("[%d] World1 \n",omp_get_thread_num());
#pragma omp section
	printf("[%d] Hello2 \n",omp_get_thread_num());
#pragma omp section
	printf("[%d] World2 \n",omp_get_thread_num());
}
	exit(0);
}
