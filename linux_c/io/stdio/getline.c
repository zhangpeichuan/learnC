#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	if(argc <2){
		fprintf(stderr,"Usage.....\n");
		exit(0);
	}
	FILE *fp;
	//初始化赋值为空
	char *linebuf=NULL;
	size_t lineSize=0;
	int		count;
	fp = fopen(argv[1],"r");
	if(fp == NULL){
		perror("fopen()");
		exit(1);

	}

	while(1){
	if(getline(&linebuf,&lineSize,fp)<0){
		break;
	}
		count++;
	printf("%d行 %lu %lu\n",count,strlen(linebuf),lineSize);
	}
//	free(linebuf);
	fclose(fp);
	return 0;
}
