#include "arp.h"
int i;
unsigned char etertype[2]={0x08,0x06};
unsigned char tramaenviada[48];
unsigned char tramarecivida[48];
unsigned char harware[2]={0x00,0x01};
unsigned char protocolo[2]={0x08,0x00};
unsigned char ldh=6;
unsigned char ldp=4;
unsigned char codenvio[2]={0x00,0x01};
unsigned char codrespuesta[2]={0x00,0x02};
FILE *puerta,*ipmac;
void printfmac(unsigned char *mimac)
{
	for(i=0;i<6;i++)
	{
		printf("%.2x",mimac[i]);
		if(i==5)
			continue;
		printf(":");
	}
}
void printfip(unsigned char *miip)
{
	for(i=0;i<4;i++)
	{
		printf("%d",miip[i]);
		if(i==3)
			continue;
		printf(".");
	}
}
void archiva(unsigned char *tuip,unsigned char *tumac)
{
        int i,j;
        if((ipmac=fopen("ipmac.txt","a+"))!=NULL)
        {
                for(j=28;j<32;j++)
                {
                        fprintf(ipmac,"0x%.2x",tuip[j]);
                        if(j<31)
                        {fprintf(ipmac,".");}
                        if(j==31)
                        {fprintf(ipmac,"\t");}
                }       
	        for(i=6;i<12;i++)
               	{
                        fprintf(ipmac,"0x%.2x",tumac[i]);
                        if(i<11)
                        {fprintf(ipmac,"%s",":");}
                        if(i==11)
                        {fprintf(ipmac,"\n");}
           	}            
                fclose(ipmac);
        }       
        else
                printf("Error al guardar las ip y las mac");
}
void resivetrama(int pac,unsigned char *mimac,unsigned char *tuip,unsigned char *tumac)
{
        struct timeval start, end;
        long mtime, seconds, useconds;
        gettimeofday(&start, NULL);
        while(mtime<1000000)  //usleep(2000);
        {
                int tam;
                tam=recvfrom(pac,tramarecivida,48,0,NULL,0);
                if(tam==-1)
                        {perror("\nError al recibir trama");}
                else    
                {
                        if(!memcmp(tramarecivida+20,codrespuesta,2)&&!memcmp(tramarecivida+0,mimac,6))
                        {
                                memcpy(tumac+0,tramarecivida+6,6);
                                printf("\nsu mac es:\t\t");
                                printfmac(tumac);
                                printf("\n");
                                archiva(tuip,tumac);
                                break;          
                        }       
                }       
                gettimeofday(&end, NULL);
                seconds  = end.tv_sec  - start.tv_sec;
                useconds = end.tv_usec - start.tv_usec;
                mtime = ((seconds) * 1000000 + useconds/1000.0) + 0.5;
        }       

        int tam,resp=0;
        while(resp==0)
        {
                tam=recvfrom(pac,tramarecivida,48,0,NULL,0);
                if(tam==-1)
                        {perror("\nError al recibir trama");}
                else
                {
                        if(!memcmp(tramarecivida+20,codrespuesta,2)&&!memcmp(tramarecivida+0,mimac,6))
                        {
                                resp=1;
				memcpy(tumac+0,tramarecivida+6,6);
                                printf("\nsu mac es:\t\t");
				printfmac(tumac);
                                printf("\n");
                                break;
                        }
                }
        }
}
void enviatrama(unsigned char *mimac,unsigned char *tuip,int pac,int indi,unsigned char *tumac)
{
        int tam;
        struct sockaddr_ll nic;
        memset(&nic, 0x00, sizeof(nic));
        nic.sll_family = AF_PACKET;
        nic.sll_protocol = htons(ETH_P_ALL);
        nic.sll_ifindex = indi;
        tam = sendto(pac, tramaenviada,48, 0, (struct sockaddr *)&nic, sizeof(nic));
        if(tam == -1)
                perror("\nError al enviar\n\n");
        else
        {
                printf("\npidiendo mac ala ip ");printfip(tuip);printf(" ...\n");
		resivetrama(pac,mimac,tuip,tumac);
        }
}
void estructuratrama(unsigned char *miip,unsigned char *mimac,unsigned char *tuip,unsigned char *tumac,int pac,int indi)
{
        memset(tumac,0xff,6);
        memcpy(tramaenviada+0,tumac,6);
        memcpy(tramaenviada+6,mimac,6);
        memcpy(tramaenviada+12,etertype,2);
        memcpy(tramaenviada+14,harware,2);
        memcpy(tramaenviada+16,protocolo,2);
        memcpy(tramaenviada+18,&ldh,1);
        memcpy(tramaenviada+19,&ldp,1);
        memcpy(tramaenviada+20,codenvio,2);
        memcpy(tramaenviada+22,mimac,6);
        memcpy(tramaenviada+28,miip,4);
        memcpy(tramaenviada+32,tumac,6);
       	memcpy(tramaenviada+38,tuip,4);
        enviatrama(mimac,tuip,pac,indi,tumac);
}
int datosdered(char *interfaz,unsigned char *miip,unsigned char *mimac,unsigned char *mascara,unsigned char *enlace,int paq)
{
	int indice;
	struct ifreq infointerfaz;
	strcpy(infointerfaz.ifr_name,interfaz);
	if(ioctl(paq,SIOCGIFINDEX,&infointerfaz)==-1)
                {perror("\nerror al obtener indice");exit(-1);}
        indice=infointerfaz.ifr_ifindex;
//	printf("indice:\t\t%d",indice);
        if(ioctl(paq,SIOCGIFHWADDR,&infointerfaz)==-1)
        {perror("\nerro al obtener la mac");}
        else
        {
                memcpy(mimac,infointerfaz.ifr_hwaddr.sa_data,6);
                printf("\nmi direccion mac:\t\t");
                printfmac(mimac);
        }
	if(ioctl(paq,SIOCGIFADDR,&infointerfaz)==-1)
                {perror("\nerro al obener la ip");}
        else
        {
                printf("\nmi direccion ip :\t\t");
		memcpy(miip+0,infointerfaz.ifr_addr.sa_data+2,4);
                printfip(miip);
        }
	if(ioctl(paq,SIOCGIFNETMASK,&infointerfaz)==-1)
                {perror("\nerror al obtener la mascara de subrred");}
        else
        {
                printf("\nmi mascara de subred:\t\t");
                memcpy(mascara,infointerfaz.ifr_netmask.sa_data+2,4);
               	printfip(mascara);
        }
	system("arp -an > puerta.dat");
        if((puerta=fopen("puerta.dat","r"))!=NULL)
        {
	fscanf(puerta,"? (%d.%d.%d.%d",(int*)&enlace[0],(int*)&enlace[1],(int*)&enlace[2],(int*)&enlace[3]);
        printf("\nmi puerta de enlase :\t\t");
        printfip(enlace);
        }
        else
                {printf("\nError al abrir el archivo");exit(-1);}
        fclose(puerta);
        return indice;
}
