#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <sys/stat.h>
#include <unistd.h>
#define PATHSIZE    1024
static int path_noloop(const char *path){
    char *pos;
    pos = strrchr(path,'/');
    if(pos == NULL)
        exit(1);

    if(strcmp(pos+1,".") == 0 || strcmp(pos+1,"..") == 0)
        return 0;
    return 1;
}

static int64_t mydu(const char *path){
    static struct  stat stat_res;
    static char    nextpath[PATHSIZE];
    glob_t  g;
    int64_t sum;
    if(0 != lstat(path,&stat_res)){
        perror("lstat()");
        exit(1);
    }
    if(!S_ISDIR(stat_res.st_mode)){
        return stat_res.st_blocks;
    }

    strncpy(nextpath, path, PATHSIZE);
    strncat(nextpath, "/*", PATHSIZE);
    glob(nextpath, 0, NULL, &g);
    strncpy(nextpath, path, PATHSIZE);
    strncat(nextpath, "/.*", PATHSIZE);
    glob(nextpath, GLOB_APPEND, NULL, &g);

    sum = 0;
    for (int i = 0; i < g.gl_pathc; i++)
    {
        if (path_noloop(g.gl_pathv[i]))
            sum += mydu(g.gl_pathv[i]);
    }
	sum +=stat_res.st_blocks;
    printf("%lld	%s\n",sum/2,path);
    globfree(&g);
    return sum;
}

int main(int argc ,char **argv){

    if(argc < 2){
        fprintf(stderr,"Usage ...");
        exit(1);
    }
	//mydu(argv[1]);
    printf("%lld	%s\n",mydu(argv[1])/2,argv[1]);


    return 0;
}
