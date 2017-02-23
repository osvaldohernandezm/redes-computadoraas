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
#ifndef __RED_H__
#define __RED_H__
typedef struct sred
{
	int indice,paquete;
	unsigned char ip[4];
	unsigned char mac[6];
	unsigned char mascara[4];
	unsigned char ipenlace[4];
	unsigned char macenlace[6];
	unsigned char ippu[4];
}sred;
FILE *puerta,*ippublica,*host;
void parametros(int ari,char **arc,int *ttl,int *pac,unsigned char *tuip,char *mensaje);
void putip(unsigned char *ip);
void putmac(unsigned char *mac);
void putdatos(sred *cabr);
sred * datosred(char *interfaz,int paq);
#endif
