#include <stdio.h>
#include <stdlib.h>
#include "search.h"

int SearchBST(BiTree T,int key,BiTree f,BiTree *p){
	if(!T){
		*p = f;
		return -1;
	}else if(key == T->data){
		*p = T;
		return 0;
	}else if(key < T->data){
		return SearchBST(T->lchild,key,T,p);
	}else
		return SearchBST(T->rchild,key,T,p);
}
int InsertBST(BiTree *T,int key){
	BiTree p,s;
	if(!SearchBST(*T,key,NULL,&p)){
		s = (BiTree)malloc(sizeof(BiTNode));	
		s->data = key;
		s->lchild = s->rchild = NULL;
		if(!p)
			*T = s;
		else if(key < p->data)
			p->lchild = s;
		else 
			p->rchild = s;
		return 0;
	}else{
		return -1;
	}
}
void visit(void *data){
	printf("%d \n",(int)*data);
}
void pre_order(BiTree *T){
	if(T != NULL){
		visit(T->data);
		pre_order(T->lchild);
		pre_order(T->rchild);
	}
}
