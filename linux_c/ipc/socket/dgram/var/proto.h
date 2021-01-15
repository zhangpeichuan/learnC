#ifndef	PROTO_H__
#define	PROTO_H__

#define	RCVPORT		"1989"
#define	NAMEMAX		(512-8-8)
//512 UDP推荐包的大小
//8UDP 包头的大小
//8个字节长度
struct msg_st{
	uint32_t		math;
	uint32_t		chinese;
	uint8_t			name[1];
}__attribute__((packed));


#endif
