#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
/*
int errfunc_(const char *epath,int eerrno){
    puts(epath);
    fprintf(stderr,"error msg %s \n",stderror(eerrno));
    return 0;
}*/
//#define PAT "/etc/a*.conf"
#define PAT "/etc/.*"

int main(){
    glob_t glob_t_ret;
    int err = 0;
    err = glob(PAT,0,NULL,&glob_t_ret);
    if(err){
        printf("error code = %d \n",err);
        exit(1);
    }
    for (int i = 0; i < glob_t_ret.gl_pathc; i++)
    {
        puts(glob_t_ret.gl_pathv[i]);
    }
    globfree(&glob_t_ret);
    exit(0);
}