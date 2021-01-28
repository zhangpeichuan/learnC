#ifndef	CLIENT_H__
#define	CLIENT_H__

#include <proto.h>
//#include "../include/proto.h"//修改makefile
#define		DEFAULT_PLAYCMD		"/usr/bin/mpg123 - > /dev/null"
#define		DEFAULT_EN
struct client_conf_st{
	char	*rcvport;
	char	*mgroup;
	char	*player_cmd;
};
extern struct client_conf_st client_conf;
#endif
