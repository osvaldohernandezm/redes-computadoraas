#include <string.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <sys/types.h>
#include <net/if.h>
#include <features.h>
#include <arpa/inet.h>
#include <asm/types.h>
#include <unistd.h>
#include <sys/time.h>
#ifndef __ANALISA_H__
#define __ANALISA_H__
int dsapandssap(unsigned char goi,unsigned char roc);
int innusu(unsigned char env);
int chekonebyte(unsigned char byteone);
int chektwobytes(unsigned char byteone,unsigned char bytetwo,int opc);
void *analisatrama(void *args);
#endif
