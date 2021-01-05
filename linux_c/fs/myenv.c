#include <stdio.h>
#include <stdlib.h>

extern char **environ;
int main(){
    int i;
    static float f;
    
    for (i = 0; environ[i] != NULL; i++)
    {
        printf("%s \n",environ[i]);
    }
    printf("\n\n");    
    puts(getenv("PATH"));
    getchar();
    exit(0);
}
