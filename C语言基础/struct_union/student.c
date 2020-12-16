#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE    20
struct student_st
{
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};
static void stu_set(struct student_st *p,const struct student_st *q){
    p->id = q->id;
    strncpy(p->name,q->name,NAMESIZE);
    p->math = q->math;
    p->chinese = q->chinese;
    //相当于*p =*q;
}
static void stu_show(struct student_st *p){
    printf("id = %d,name = %s,math =%d chinese = %d \n",p->id,p->name,p->math,p->chinese);

}
static void stu_changename(struct student_st *p,const char *newname){
    strncpy(p->name,newname,NAMESIZE);
}
static void menu(){
    printf("\n1 set \n2 changename \n3 show\n q(Q) for quit\n\n"); 
    printf("Please enter num:");
}
int main(){

    struct  student_st stu,tmp;
    char newname[NAMESIZE];
#if 0
    printf("Please enter for student [id,name,math,chinese]\n");
    scanf("%d%s%d%d",&tmp.id,tmp.name,&tmp.math,&tmp.chinese);

    stu_set(&stu,&tmp);

    stu_show(&stu);

    printf("Please enter newname\n");
    scanf("%s",tmp.name);

    stu_changename(&stu,tmp.name);

    stu_show(&stu);
#endif
    int ret;

    do{
        menu();
        int choice;
        int ret = scanf("%d",&choice);
        if(ret!=1) break;
        switch(choice)
        {
            case 1:
                printf("Please enter for student [id,name,math,chinese]\n");
                scanf("%d%s%d%d",&tmp.id,tmp.name,&tmp.math,&tmp.chinese);
                stu_set(&stu,&tmp);
                break;
            case 2:
                printf("Please enter newname\n");
                scanf("%s",&newname);
                stu_changename(&stu,newname);
                break;
            case 3:
                stu_show(&stu);
                break;
            default:
                exit(0);
                break;

        }
    }while(1);
    return 0;
}
