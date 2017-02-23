#include "red.h"//97CE094DF5 infinitum89130E
#include "arp.h"
unsigned char etertype[2]={0x08,0x06};
unsigned char tramaarpenv[48];
unsigned char tramaarprec[48];
unsigned char codenvio[2]={0x00,0x01};
unsigned char codrespuesta[2]={0x00,0x02};
unsigned char ipaux[4],macaux[6];
int resivearp(sred *cabr)
{
        struct timeval start, end;
        double time;
	gettimeofday(&start, NULL);
        while(time<2000)
        {
                int tam;
                tam=recvfrom(cabr->paquete,tramaarprec,48,0,NULL,0);
                if(tam==-1)
                        {perror("\nError al recibir trama");}
                else
                {
                        if(!memcmp(tramaarprec+20,codrespuesta,2)&&!memcmp(tramaarprec+0,cabr->mac,6)&&!memcmp(tramaarprec+28,ipaux,4))
                        {
                                memcpy(macaux+0,tramaarprec+6,6);
				printf("\npidiendo mac ala ip ");putip(ipaux);printf(" ...");
                                printf("su mac es: ");putmac(macaux);printf("\n");
                                return 0;
                        }
                }
                gettimeofday(&end, NULL);
                time =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;
        }
	return 1;
}
void enviaarp(sred *cabr)
{
        int tam;
        struct sockaddr_ll nic;
        memset(&nic, 0x00, sizeof(nic));
        nic.sll_family = AF_PACKET;
        nic.sll_protocol = htons(ETH_P_ALL);
        nic.sll_ifindex = cabr->indice;
        tam = sendto(cabr->paquete, tramaarpenv,48, 0, (struct sockaddr *)&nic, sizeof(nic));
        if(tam == -1)
                perror("\nError al enviar\n\n");
	else
	{
		if(resivearp(cabr))
			printf("\n respuesta fallida!!! :(");
	}
}
void estructuraarp(sred *cabr,unsigned char *tuip)
{
	memcpy(ipaux,tuip,4);
	memset(tramaarpenv+0,0xff,6);
        memcpy(tramaarpenv+6,cabr->mac,6);
        memcpy(tramaarpenv+12,etertype,2);
	tramaarpenv[14]=0x00;//harware
	tramaarpenv[15]=0x01;//harware
	tramaarpenv[16]=0x08;//protocolo
	tramaarpenv[17]=0x00;//protocolo
        tramaarpenv[18]=0x06;//ldh
        tramaarpenv[19]=0x04;//ldp
        memcpy(tramaarpenv+20,codenvio,2);
        memcpy(tramaarpenv+22,cabr->mac,6);
        memcpy(tramaarpenv+28,cabr->ip,4);
	memset(tramaarpenv+32,0xff,6);
        memcpy(tramaarpenv+38,tuip,4);
	enviaarp(cabr);
}
