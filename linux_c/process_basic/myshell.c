#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <glob.h>
#define DELIMS  " \t\n"
typedef struct cmd_st
{
    glob_t  glob_t_res;
}cmd;

static void prompt(void){
    printf("mysh-0.1$ ");
}
static void parse(char *line,cmd *res){
    char *tok;
    int flag = 0;
    while (1)
    {   
        tok = strsep(&line,DELIMS);
        if(tok == NULL)
            break;
        if(tok[0] == '\0')
            continue;
        glob(tok,GLOB_NOCHECK|GLOB_APPEND*flag,NULL,&res->glob_t_res); 
        flag=1;
    }
    

}
int main(int argc,char **argv){
    char    *linebuf = NULL;
    size_t  linebuf_size = 0;
    cmd     cmd_res;
    pid_t   pid;
    while (1)
    {
        prompt();
        if(getline(&linebuf,&linebuf_size,stdin)<0)
            break;
        parse(linebuf,&cmd_res);
        if (0)//内部命令
        {
            /* code */
        }else{
            pid = fork();
            if(pid <0){
                perror("fork()");
                exit(1);
            }
            if(pid == 0){
                execvp(cmd_res.glob_t_res.gl_pathv[0],cmd_res.glob_t_res.gl_pathv);
                perror("execvp()");
                exit(1);

            }else{
                wait(NULL);
            }

        }
        
    }
    



    exit(0);
}
