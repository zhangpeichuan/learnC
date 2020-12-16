#include <stdio.h>
#include <stdlib.h>

#define NAMESIZE    32
struct simp_st{
    int     i;
    char    ch;
   float   f;
//   char    ch1; 顺序互换，内存占用空间增大了4字节,因为int占用4字节，内存对齐
 
};
struct simp_st1{
    int     i;
    char    ch;
   float   f;
 
} __attribute__ ((packed));
struct birthday_st{
    int year;
    int month;
    int day;
};
struct student_st{
    int id;
    char name[NAMESIZE];
    //int year,month,day;嵌套定义
   struct  birthday_st birth;
    struct registed_day_st{
        int year;
        int month;
        int day;
    }regist;
    int math;
    int chinese;
};
  
void func_p(struct simp_st *b){
    printf("指针传递 %lu \n",sizeof(b));
}

void func(struct simp_st b){
    printf("值传递 %lu \n",sizeof(b));
}
int main(){
#if 0    
    struct simp_st  a = {123,456.789,'a'};
    a.i = 223344;
    printf("%d %f %c\n",a.i,a.f,a.ch);
#endif

#if 0    
    //整体赋值
    struct student_st stu ={10011,"Alan",{2001,11,11},{2020,10,1},98,97}; 
    //部分赋值
    struct student_st stu1 = {.math=98,.chinese=97};
    //指针访问赋值
    struct student_st *p_stu = &stu1;
        printf("sizeof stu = %lu %p \n",sizeof(stu),&stu);
    printf("sizeof stu0 = %lu %p \n",sizeof(stu1),&stu1);
    printf("sizeof *p_stu = %lu %p \n",sizeof(*p_stu),p_stu);
    printf("全部初始化%d %s %d %d %d %d %d\n",stu.id,stu.name,stu.birth.year,stu.birth.month,stu.birth.day,stu.math,stu.chinese);
    printf("部分初始化%d %s %d %d %d %d %d\n",stu1.id,stu1.name,stu1.birth.year,stu1.birth.month,stu1.birth.day,stu1.math,stu1.chinese);
    p_stu->math = 88;
    p_stu->chinese = 28;
    p_stu->id = 10012;

printf("指针访问%d %s %d %d %d %d %d\n",p_stu->id,p_stu->name,p_stu->birth.year, p_stu->birth.month, p_stu->birth.day, p_stu->math, p_stu->chinese);
    struct student_st arr[2] = {{20022,"Alan2",{2001,11,11},{2020,10,1},98,97},{30033,"Bird",{2001,13,3},{2013,13,3},88,80}}; 
    

    struct student_st *p = &arr[0];
    for(int i= 0;i<2;i++,p++){
    
printf("指针访问%d %s %d %d %d %d %d\n",p->id,p->name,p->birth.year, p->birth.month, p->birth.day, p->math, p->chinese);

    }
#endif
        
    struct simp_st a;
    struct simp_st *p = &a;

    struct simp_st1 a1;
    struct simp_st1 *q = &a1;
    printf("sizeof(point) = %lu \n",sizeof(p));
    printf("未对齐sizeof(struct) = %lu \n",sizeof(a));
     printf("sizeof(point) = %lu \n",sizeof(q));
    printf("对齐sizeof(struct) = %lu \n",sizeof(a1));
    
    func(a);//相当于func(a.i,a.ch,a.f);

    func_p(p);

    exit(0);
}
