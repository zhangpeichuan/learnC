#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){

    time_t end;
    int64_t count=0;

    end = time(NULL)+5;

    while (time(NULL) <=end)
    {
        count++;
    }
    printf("count =%lld \n",count);
    

    return 0;
}