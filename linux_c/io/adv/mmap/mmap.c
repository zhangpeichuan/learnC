#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>



int main(int argc,char *argv[]){
	
	if(argc < 2){
		fprintf(stdout,"Usage ...");
		exit(1);
	}
	int fd;
	struct stat stat_res;
	char *str;
	int i, count;
	fd = open(argv[1],O_RDONLY);
	if(fd <0){
		perror("open()");
		exit(1);
	}
	if(fstat(fd,&stat_res) <0){
		perror("fstat()");
		close(fd);
		exit(1);
	}
	

	str = mmap(NULL,stat_res.st_size,PROT_READ,MAP_SHARED,fd,0); 
	if(str == MAP_FAILED){
		perror("mmap()");
		exit(1);
	}
	close(fd);
	for(i = 0 ;i< stat_res.st_size;i++){
		if(str[i] == 'a')
			count++;
	}
	printf("count %d\n",count);

	munmap(str,stat_res.st_size);
	exit(0);
}
