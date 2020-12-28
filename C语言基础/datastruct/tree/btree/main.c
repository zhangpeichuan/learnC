#include <stdio.h>
#include <stdlib.h>
#define  NAMESIZE    32 
typedef struct score_st{
    int     id;
    char    name[NAMESIZE];
    int     math;
    int     chinese;
}score;

static void scoreprint(score *record){
    printf("%d %s %d %d\n",record->id,record->name,record->math,record->chinese);
}


typedef struct node_st{
    score   data;
    struct node_st *l,*r;
}btree;

int insert(btree **root,score *data){
    btree *node;
    if(*root == NULL){
        node = malloc(sizeof(*node));
        if(node == NULL)
          return -1;
        node->data = *data;
        node->l = NULL;
        node->r = NULL;

        *root = node;

        return 0;
    }

    if(data->id <= (*root)->data.id)
        return insert(&((*root)->l),data);
    else
        return insert(&((*root)->r),data);
}
score *find(btree *root,int id){
    if(root == NULL)
        return NULL;

    if(id == root->data.id) 
        return &root->data;

    if(id < root->data.id)
        return find(root->l,id);
    else
        return find(root->r,id);

}
//左倒，然后根据层数打印tab,右根左
//          D
//      C   
//          E
//  A
//          F
//      B
//          G
void draw(btree *root,int level){
    if(root == NULL)
        return;
    draw(root->r,level+1);
    for(int i=0;i<level;i++){
        printf("    ");
    }
    scoreprint(&root->data);
    draw(root->l,level+1);

}
void display(btree *root){
    draw(root,0);
}


//比当前节点小的左走，大的右走
int main(void){
    int     arr[] = {1,2,3,7,6,5,9,8,4};
    btree   *tree = NULL;
    score   tmp,*data;
    int     i,ret;
    for(i = 0;i<sizeof(arr)/sizeof(*arr);i++)
    {
        tmp.id=arr[i];
        snprintf(tmp.name,NAMESIZE,"stu%d",arr[i]);
        tmp.math = rand()%100;
        tmp.chinese = rand()%100;
        ret = insert(&tree,&tmp);
        if(ret ==0)
          printf("插入成功\n");
        else
          printf("插入失败\n");

    }
    display(tree);
    int tmpid = 12;
    data = find(tree,tmpid);
    if(data == NULL)
      printf("can not find tmpid = %d\n",tmpid);
    else
      scoreprint(data);

    exit(0);
}
