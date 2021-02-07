#ifndef SEARCH_H__
#define SEARCH_H__
typedef	struct BiTNode{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
//顺序表查找
int Sequential_Search(int *a,int n,int key);
//优化带哨兵
int Sequential_Search2(int *a,int n,int key);
//二分查找
int Binary_Search(int *a,int n,int key);
//插值查找
int Interpolation_Search(int *a,int n,int key);
//二叉搜索树
int SearchBST(BiTree T,int key,BiTree f,BiTree *p);
int InsertBST(BiTree *T,int key);
void pre_order(BiTree *T);
#endif
