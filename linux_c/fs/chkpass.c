#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>

int main(int argc,char **argv){
	char *input_pass,*cypted_pass;
	struct spwd *shadowline;
	if(argc < 2){
		fprintf(stderr,"Usage ....\n");
		exit(1);
	}
	if(access("/etc/shadow",R_OK)){
		perror("access error");
		exit(1);
	}

	input_pass = getpass("check your Password:");
	
	
	shadowline = getspnam(argv[1]);
	
	cypted_pass = crypt(input_pass,shadowline->sp_pwdp);
	
	if(strcmp(shadowline->sp_pwdp,cypted_pass) == 0)
		puts("ok");
	else
		puts("false");

	return 0;
}
