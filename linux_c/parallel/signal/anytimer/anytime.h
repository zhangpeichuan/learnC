#ifndef ANYTIME_H__
#define ANYTIME_H__



typedef void at_jobfunc_t(void *);

/**
 * @description: 
 * @param {int} sec
 * @param {at_jobfunc_t} *jobp
 * @param {void} *
 * @return {*
 *      >=0 成功，返回任务ID
        == -EINVAL  失败，参数非法   
        == -ENOSPC  失败，数组满
        == -ENOMEM  失败，内存空间不足}
 */
int at_addjob(int sec,at_jobfunc_t *jobp,void * argv);
/**
 * @description: 
 * @param {int} job
 * @return {*} return == 0 成功
 *                    == -EINVAL 指定任务非法
 *                    == -EBUSY   指定任务已完成
 *                    == -ECANCELED 失败指定任务已取消
 */
int at_canceljob(int job);
/**
 * @description: 
 * @param {int} id
 * @return {*} return == 0 成功
 *                    == -EINVAL 指定任务非法
 */
int at_waitjob(int id);
/**
 * @description: 
 * @param {int} job
 * @return {*} return == 0 成功
 *                    == -EINVAL 指定任务非法
 */
int at_pausejob(int job);
/**
 * @description: 
 * @param {int} job
 * @return {*} return == 0 成功
 *                    == -EINVAL 指定任务非法
 */
int at_resumejob(int job);


#endif