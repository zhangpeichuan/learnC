#ifndef RELAYER_H__
#define RELAYER_H__
#define	RELAYER_JOBMAX	10000
enum{
	STATE_RUNNING = 1,
	STATE_CANCELED,
	STATE_OVER
};
struct relayer_stat_st{
	int		state;
	int		fd1;
	int		fd2;
	int64_t	count12,count21;
	
	//	struct timerval	start,end;
};

/*
 *return >= 0		成功，返回当前任务的ID
 *		== -EINVAL	失败，参数非法
 *		== -ENOSPC	失败，任务数组满
 *		== -ENOMEM	失败，内存申请失败
 * */
int relayer_addjob(int fd1,int fd2);

/*
 *return == 0		成功，指定任务成功取消
 *		== -EINVAL	失败，参数非法
 *		== -EBUSY	失败，任务早已被取消
 * */
int relayer_canceljob(int id);

/*
 *return == 0		成功，指定任务已终止并返回状态
 *		 == -EINVAL	失败，参数非法
 *		
 *
 * */
int relayer_waitjob(int id,struct relayer_stat_st *);

/*
 *return == 0		成功，指定任务已终止并返回状态
 *		 == -EINVAL	失败，参数非法
 *		
 *
 * */
int relayer_statjob(int id,struct relayer_stat_st *);

#endif
