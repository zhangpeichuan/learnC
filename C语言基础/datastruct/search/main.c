#include <stdio.h>
#include <stdlib.h>
#include "search.h"

void test_search(void){
    int a[11]={0,1,16,24,35,47,59,62,73,88,99};
    int key=62;
    printf("%d\n",Binary_Search(a,11,key));
    printf("%d\n",Interpolation_Search(a,11,key));
}
void test_bst_search(void){
	int i;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	BiTree T = NULL;
	for(i = 0;i<10;i++){
		InsertBST(&T,a[i]);
	}
	pre_order(&T);
}
int main(void){
    //test_search();
	test_bst_search();
    return 0;
}
