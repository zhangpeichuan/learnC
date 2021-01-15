#ifndef	PIPEOPEN_H__
#define	PIPEOPEN_H__

#define	PIDMAX		1024

int pid_open(mode_t mode);

int pid_read(int pid,void *buf,size_t count);

int pid_write(int pid,const void *buf,size_t count);

void pid_close(int pid);
#endif
