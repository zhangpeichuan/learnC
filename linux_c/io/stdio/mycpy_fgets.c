#include <stdio.h>
#include <stdlib.h>
#define	BUFSIZE	1024
int main(int argc,char **argv){
    FILE    *fp_s,*fp_d;
	char	buf[BUFSIZE];
    if(argc <3){
        fprintf(stderr,"Usage:%s <src_file> <des_file> \n",argv[0]);
        exit(1);
    }
    fp_s = fopen(argv[1],"r");
    if(fp_s == NULL){
        perror("fopen()");
        exit(1);
    }
    fp_d = fopen(argv[2],"w");
     if(fp_d == NULL){
         fclose(fp_s);
        perror("fopen()");
        exit(1);
    }
    while(fgets(buf,BUFSIZE,fp_s) != NULL)
    {

        fputs(buf,fp_d);
    }
    fclose(fp_d);
    fclose(fp_s);

    return 0;
}
