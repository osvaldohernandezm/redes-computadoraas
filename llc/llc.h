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
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#ifndef __ARP_H__
#define __ARP_H__
#define tamarp 700
typedef struct llc
{
	unsigned char trama[700];
	struct llc *sig;
}llc;
llc *cabt,*nvo,*p;
int insertat(unsigned char *tramallcrec,int tamtr,int df);
void *resivellc(void *args);
int imprime(unsigned char *trama,int lim);
void enviallc(unsigned char *tramallcenv,int tamtr);
void *fichero(void *args);
#endif
