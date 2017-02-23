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
#ifndef __PING_H__
#define __PING_H__
void estadisticas(int *tiempopac,unsigned char *tuip,int pac);
int compruebared(sred *cabr,unsigned char *tuip);
void checksum(int limi, int lims, unsigned char *check0, unsigned char *check1, unsigned char *mtrama);
int reciveping(sred *cabr,unsigned char *tuip,int *tiempopac,int sec,int tamtra);
void enviaping(sred *cabr,unsigned char *tuip,int *tiempopac,int sec,int tamtra);
void estructuraping(sred*cabr,unsigned char *tumac,unsigned char *tuip,int secuencia,int ttl,int red,int *tiempopac,char *mensaje);
#endif
