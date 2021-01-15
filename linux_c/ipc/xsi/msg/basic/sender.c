#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "proto.h"
int main(){
	key_t key;
	int		msgid;
	struct msg_st sbuf;
	key = ftok(KEYPATH,KEYPROJ);
	if(key < 0){
		perror("ftok()");
		exit(1);
	}
	msgid = msgget(key,IPC_EXCL);
	if(msgid < 0){
		perror("msgget()");
		exit(1);
	}
	strcpy(sbuf.name,"zhangsan");
	sbuf.math = rand()%80;
	sbuf.chinese = rand()%90;
	sbuf.mtype = 1;

	if(msgsnd(msgid,&sbuf,sizeof(sbuf)-sizeof(long),0) < 0){
		perror("msgsnd()");
		exit(1);
	}
	puts("OK");	
	exit(0);
}
