#include <stdio.h>

/*
 * 顺序查找，a位数组，n为要查找的数组个数，key为查找关键字
 * */
int Sequential_Search(int *a,int n,int key){
    int i;
    for(i = 1;i<=n;i++){
        if(a[i] == key)
          return i;
    }
    return -1;
}
/*
 *有哨兵顺序查找
 * */
int Sequential_Search2(int *a,int n,int key){
    int i;
    a[0] = key;
    i = n;
    while(a[i] !=key){
        i--;
    }
    return i;
}

