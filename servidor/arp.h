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
pthread_mutex_t mutex,mutex2;
pthread_t hres[255];
unsigned char macpadre[6];
void inmac();
void inip();
void inrango();
void matahilo(long int id);
void *resivearp(void *args);
void enviaarp();
void estructuraarp(unsigned char *tuip,unsigned char *tumac,int opc);
#endif
