#include "red.h"//97CE094DF5 infinitum89130E
#include "arp.h"
#include "mysql.h"
unsigned char etertype[2]={0x08,0x06};
unsigned char tramaarpenv[48];
unsigned char tramaarprec[48];
unsigned char codenvio[2]={0x00,0x01};
unsigned char codrespuesta[2]={0x00,0x02};
unsigned char ipaux[4],macaux[6];
unsigned char macpadre[6];
int h=0,tam=0,basura;
long int idhilo=0;
void inmac()
{
	printf("\ninfractor por paso de parametro mac");
        memcpy(ipaux+0,tramaarprec+28,4);
       	pthread_mutex_unlock(&mutex);
        estructuraarp(ipaux,tumac,1);
}
void inip()
{
	printf("\ninfractor por paso de parametro ip");
       	memcpy(macaux+0,tramaarprec+6,6);
       	pthread_mutex_unlock(&mutex);
       	estructuraarp(tuip,macaux,1);

}
void inrango()
{
	if((int)tramaarprec[31]>=cabr->r1&&(int)tramaarprec[31]<=cabr->r2)
       	{
        	printf("\ninfractor por paso de parametro rango");
               	memcpy(ipaux+0,tramaarprec+28,4);
                memcpy(macaux+0,tramaarprec+6,6);
                pthread_mutex_unlock(&mutex);
                estructuraarp(ipaux,macaux,1);
	}
}
void matahilo(long int id)
{
	pthread_mutex_unlock(&mutex);
	if(idhilo!=id)
	{printf("\nel hilo con id %ld muere",id);pthread_detach(pthread_self());pthread_exit(NULL);}
}
void *resivearp(void *args)
{
	pthread_mutex_lock(&mutex);
//	if(h==0)
//		{idhilo=pthread_self();printf("\nel hilo 0 es %ld",idhilo);}
	if(h<254)
		{pthread_create(&hres[h],NULL,resivearp,NULL);h++;}
	//else
	//	{pthread_create(&hres[h],NULL,resivearp,NULL);h=1;}
        while(1)
        {
                tam=recvfrom(cabr->paquete,tramaarprec,48,0,NULL,0);
                if(tam==-1)
                        {perror("\nError al recibir trama");}
                else
                {
			if(!memcmp(tramaarprec+12,etertype,2)&&!memcmp(tramaarprec+0,macpadre,6)&&tramaarprec[41]!=cabr->ipenlace[3])
			{
				/*if(cabr->r2!=0)
				{inrango();matahilo(pthread_self());}
				if(!memcmp(tramaarprec+28,tuip,4))
				{inip();matahilo(pthread_self());}
				if(!memcmp(tramaarprec+6,tumac,6))
				{inmac();matahilo(pthread_self());}*/
	                        if(!memcmp(tramaarprec+20,codenvio,2))
        	                {
					memcpy(ipaux+0,tramaarprec+38,4);//printf("\nip = ");putip(ipaux);
                        	        memcpy(macaux+0,tramaarprec+6,6);//printf("\nmac = ");putmac(macaux);;
					if(comprueba(ipaux,macaux)==1)
					{
						estructuraarp(ipaux,macaux,1);
//						matahilo(pthread_self());
					}
        	                }
			}
                }
        }
	return ("ya termine");
}
void enviaarp()
{
        int tam;
        struct sockaddr_ll nic;
        memset(&nic, 0x00, sizeof(nic));
        nic.sll_family = AF_PACKET;
        nic.sll_protocol = htons(ETH_P_ALL);
        nic.sll_ifindex = cabr->indice;
        tam = sendto(cabr->paquete, tramaarpenv,48, 0, (struct sockaddr *)&nic, sizeof(struct sockaddr_ll));
        if(tam == -1)
                perror("\nError al enviar\n\n");
}
void estructuraarp(unsigned char *tuip,unsigned char *tumac,int opc)//son las de la trama
{
	pthread_mutex_lock(&mutex2);
	for(basura=0;basura<2;basura++)
	{
		if(!basura)
		{
			memcpy(tramaarpenv+0,tumac,6);
			memcpy(tramaarpenv+20,codrespuesta,2);
			memcpy(tramaarpenv+32,tumac,6);
		}
		else
		{
			memset(tramaarpenv+0,0xff,6);
			memcpy(tramaarpenv+20,codenvio,2);
			memset(tramaarpenv+32,0x00,6);
		}	
        	memcpy(tramaarpenv+6,cabr->macbase,6);
	        memcpy(tramaarpenv+12,etertype,2);
		tramaarpenv[14]=0x00;//harware
		tramaarpenv[15]=0x01;//harware
		tramaarpenv[16]=0x08;//protocolo
		tramaarpenv[17]=0x00;//protocolo
        	tramaarpenv[18]=0x06;//ldh
	        tramaarpenv[19]=0x04;//ldp
        	memcpy(tramaarpenv+22,cabr->macbase,6);
	        memcpy(tramaarpenv+28,tuip,4);
        	memcpy(tramaarpenv+38,tuip,4);
		enviaarp();
	}
		pthread_mutex_unlock(&mutex2);
}
