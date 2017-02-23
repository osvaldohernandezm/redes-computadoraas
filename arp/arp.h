#include <stdio.h>
#include <stdlib.h>
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
#ifndef __ARP_H__
#define __ARP_H__
int resivearp(sred *cabr);
void enviaarp(sred *cabr);
void estructuraarp(sred *cabr,unsigned char *tuip);
#endif
