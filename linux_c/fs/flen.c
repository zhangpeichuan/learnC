#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

static off_t flen(const char *fname){
    struct stat statres;
    
    if(stat(fname,&statres) < 0){
        perror("stat()");
        exit(1);
    }
    return statres.st_size;
}
int main(int argc , char  **argv){

    if(argc < 2){
        fprintf(stderr,"Usage .....");
        exit(1);
    }

    off_t size =flen(argv[1]);
    printf("%s %lld\n",argv[1],size);



    return 0;
}
