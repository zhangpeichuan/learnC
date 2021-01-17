#ifndef	PROTO_H__
#define	PROTO_H__

#include "site_type.h"
#define	DEFAULT_MGROUP	"224.2.2.2"
#define	DEFAULT_PORT	"1989"

#define	CHNR			100

#define	LISTCHNID		0

#define	MINCHNID		1
#define	MAXCHNID		(MINCHNID+CHNNR-1)


#define	MSG_UDP_PACKET		512
#define	MSG_IP_HEAD			20
#define	MSG_UDP_HEAD		8
#define	MSG_CHANNEL_MAX		(MSG_UDP_PACKET-MSG_IP_HEAD-MSG_UDP_HEAD)
#define	MSG_DATA			(MSG_CHANNEL_MAX-sizeof(chnid_t))

#define	MSG_LIST_MAX		(MSG_UDP_PACKET-MSG_IP_HEAD-MSG_UDP_HEAD)
#define	MSG_ENTRY			(MSG_LIST_MAX-sizeof(chnid_t))


struct msg_channel_st{
	chnid_t		chnid;/* must between [MINCHNID,MAXCHNID]*/
	uint8_t		data[1];
}__attribute__((packed));
/*msg_list_st 
1 music:XXXXXXXXXXX
2 sport:XXXXXXXXXXXX
3 ad:XXXXXXXXXXXXXXXX
4 xx:XXXXXXXXXXXXXXXXXXX
*/
struct msg_listentry_st{
	chnid_t		chnid;
	uint8_t		desc[1]
}__attribute__((packed));
struct msg_list_st{
	chnid_t		chnid;/* must be LISTCHNID */
	struct msg_listentry_st entry[1];
}__attribute__((packed));


#endif
