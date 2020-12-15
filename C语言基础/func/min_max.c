#include <stdio.h>
#include <stdlib.h>

static int min(int x,int y,int z){
    int tmp;

    tmp = x < y ? x : y;
    
    return tmp < z ? tmp : z;

}
static int max(int x,int y,int z){
     int tmp;

    tmp = x > y ? x : y;
    
    return tmp > z ? tmp : z;

}
static int dist(int x,int y,int z){
    return max(x,y,z)- min(x,y,z);
}
int main(void){
    int a =3,b=4,c=5;
    int result = dist(a,b,c);
    printf("result %d \n",result);


    return 0;
}
