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
#ifndef __TCP_H__
#define __TCP_H__
unsigned short pa[200],pc[200],ctapa,ctapc;
pthread_mutex_t mutex,mutexpc,mutexpa;
unsigned char compruebared();
void checksum(int limi, int lims, unsigned char *check0, unsigned char *check1, unsigned char *mtrama);
unsigned char recive(unsigned short puerto,unsigned short j);
unsigned char envia(unsigned char *tramaenv,unsigned short puerto,unsigned short j);
unsigned char estructura(unsigned char *tramaenv,unsigned short puerto,unsigned char red,unsigned short j);
#endif
