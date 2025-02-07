#ifndef	MYPIPE_H__
#define MYPIPE_H__

#define	PIPESIZE		1024
#define	MYPIPE_READ		0x00000001UL
#define	MYPIPE_WRITE	0x00000002UL
#define	MYPIPE_RDWR		0x00000003UL


typedef	void	mypipe_t;

int mypipe_register(mypipe_t *,int opmap);

int mypipe_unregister(mypipe_t *,int opmap);

mypipe_t *mypipe_init(void);

int mypipe_read(mypipe_t *,void *buf,size_t count);

int mypipe_write(mypipe_t *,const void *buf,size_t count);

int mypipe_destroy(mypipe_t *);
#endif
