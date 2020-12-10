#include <stdio.h>
#include <limits.h>
#include <float.h>

#include <math.h>
#include <string.h>
/**
 不同的硬件平台各个类型有差异
 */
void printLine()
{
    printf("--------------------\n");
}
//float类型比大小 | f - 0| <= 10^-6 //0.000001
void float_func(float f)
{
    if (fabs(f-0) <= 1e-6) {
        printf("小于\n");
    }else{
        printf("大于\n");
    }
}
int main()
{
    printf("sizeof(short)= %llu\n",sizeof(short));//2
    printf("sizeof(int)= %llu\n",sizeof(int));//4
    printf("sizeof(long)= %llu\n",sizeof(long));//4
    printf("sizeof(long long)= %llu\n",sizeof(long long));//8
    printLine();
    
    printf("sizeof(float)= %llu\n",sizeof(float));//4
    printf("sizeof(double)= %llu\n",sizeof(double));//8
    printf("sizeof(long double)= %llu\n",sizeof(long double));//8
    printLine();
    printf("sizeof(char)= %llu\n",sizeof(char));//
    printLine();
    printf("FILENAME_MAX = %u\n",FILENAME_MAX);
    printLine();
    printf("CHAR_MIN = %d CHAR_MAX = %d\n",CHAR_MIN,CHAR_MAX);
    printf("SHRT_MIN = %d SHRT_MAX = %d\n",SHRT_MIN,SHRT_MAX);
    printf("INT_MIN = %d INT_MAX = %d\n",INT_MIN,INT_MAX);
    printf("LONG_MIN = %ld LONG_MAX = %ld\n",LONG_MIN,LONG_MAX);
    printf("LLONG_MIN = %lld LLONG_MAX = %lld\n",LLONG_MIN,LLONG_MAX);
    printLine();
    printf("UCHAR_MAX = %u\n",UCHAR_MAX);
    printf("USHRT_MAX = %u\n",USHRT_MAX);
    printf("UINT_MAX = %u\n",UINT_MAX);
    printf("ULONG_MAX = %lu\n",ULONG_MAX);
    printf("ULLONG_MAX = %llu\n",ULLONG_MAX);
    printLine();
    
    printf("FLT_MIN = %e FLT_MAX = %e\n",FLT_MIN,FLT_MAX);
    printf("DBL_MIN = %le DBL_MAX = %le\n",DBL_MIN,DBL_MAX);
    printf("LDBL_MIN = %Le LDBL_MAX = %Le\n",LDBL_MIN,LDBL_MAX);
    printLine();
    
    char array[] = "I Miss You so much!";
    printf("char array[1024] = \"I Miss You so much!\";\n");
    printf("sizeof(array) = %llu\n",sizeof(array));
    printf("strlen(array) = %llu\n",strlen(array));
    printLine();
    //字符串指针
    char *array_pointer = "I Miss You so much!";
    printf("char * array_pointer = \"I Miss You so much!\";\n");
    printf("sizeof(array_pointer) = %llu\n",sizeof(array_pointer));
    printf("strlen(array_pointer) = %llu\n",strlen(array_pointer));
    printLine();
    int i;
    for (int i=0; i<strlen(array); ++i) {
        printf("array[%02d] = %c\n",i,array[i]);
    }
    
    
    float f1 = 0.0001;
    float f2 = 0.0000001;
    float_func(f1);
    float_func(f2);

    
    return 0;
}

