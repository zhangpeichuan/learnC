#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>

int main(int argc,char **argv){
    struct passwd *pwdline;

    if(argc <2){

        fprintf(stderr,"Usage .....");
        exit(1);
    }
    pwdline = getpwuid(atoi(argv[1]));
    char *name = pwdline->pw_name;
    puts(name);


    return 0;
}