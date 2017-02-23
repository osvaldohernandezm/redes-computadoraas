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
void printfmac(unsigned char *mimac);
void printfip(unsigned char *miip);
void archiva(unsigned char *tuip,unsigned char *tumac);
void resivetrama(int pac,unsigned char *mimac,unsigned char *tuip,unsigned char *tumac);
void enviatrama(unsigned char *mimac,unsigned char *tuip,int pac,int indi,unsigned char *tumac);
void estructuratrama(unsigned char *miip,unsigned char *mimac,unsigned char *tuip,unsigned char *tumac,int pac,int indi);
int datosdered(char *interfas,unsigned char *miip,unsigned char *mimac,unsigned char *mascara,unsigned char *enlace,int paq);
#endif
