#include "red.h"
#include "ping.h"
int i,ctapac[3]={0,0,0},intime=0;
unsigned char ethertypeping[2]={0x08,0x00};
unsigned char tramapingenv[74];
unsigned char tramapingrec[74];
void estadisticas(int *tiempopac,unsigned char *tuip,int pac)
{
	int min,max,med=0;
	min=tiempopac[0];
	max=tiempopac[0];
	for(i=0;i<ctapac[1];i++)
	{
		//printf("%d  ",tiempopac[i]);
		if(tiempopac[i]<min)
			min=tiempopac[i];
		if(tiempopac[i]>max)
			max=tiempopac[i];
		med=med+tiempopac[i];
	}
	med=med/ctapac[1];
	printf("\n\nestadisticas ping para ");putip(tuip);puts(":\n");
	printf("paquetes enviados=%d, recividos=%d, perdidos=%d\n",ctapac[0],ctapac[1],ctapac[2]);
	printf("(%d %% ",(ctapac[2]*100)/pac);printf("perdidos),\n");
	printf("tiempos aproximados de ida y vuelta en milisegundos:\n");
	printf("minimo=%dms, maximo=%dms, media=%dms\n\n",min,max,med);
}
int compruebared(sred *cabr,unsigned char *tuip)
{
        unsigned char miipmas[4];
        unsigned char tuipmas[4];
        for(i=0;i<4;i++)
        {
                miipmas[i]=cabr->ip[i]&cabr->mascara[i];
                tuipmas[i]=tuip[i]&cabr->mascara[i];
        }
        if(!memcmp(miipmas,tuipmas,4))
                return 1;
      	return 0;
}
void checksum(int limi, int lims, unsigned char *check0, unsigned char *check1, unsigned char *mtrama)
{
	unsigned int suma=0;
	unsigned short aux;
	for(i=limi;i<lims;i+=2)
	{
		aux=mtrama[i];
		aux=(aux<<8)+mtrama[i+1];
		suma=suma+aux;
	}
	suma=(suma&0x0000FFFF)+(suma>>16);
	*check0=(unsigned char)~(suma);
        *check1=(unsigned char)~(suma>>8);
}
int reciveping(sred *cabr,unsigned char *tuip,int *tiempopac,int sec,int tamtra)
{
        int tamano;
        struct timeval start, end;
        long int ptime=0;
	gettimeofday(&start, NULL);
        while( ptime < 100)//ciclo que recibira tramas
        {
                tamano = recvfrom(cabr->paquete,tramapingrec,74,0,NULL,0);
                if(tamano == -1)
                        printf("Error al recibir ping");
                else
                {
                        if(!memcmp(tramapingrec,cabr->mac,6)&&!memcmp(tramapingrec+12,ethertypeping,2)&&!memcmp(tramapingrec+26,tuip,4)&&!memcmp(tramapingrec+30,cabr->ip,4))
                        {
                               	gettimeofday(&end, NULL);
                                ptime =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
                                ctapac[1]++;
				tiempopac[intime]=ptime;intime++;
                                printf("\nrespuesta desde ");putip(tuip);
                       printf(": bytes=74 tiempo=%ldms ttl=%d",ptime,tramapingenv[22]);
				return(1);
                        }
                }
                gettimeofday(&end, NULL);
                ptime =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
        }
        printf("\nrespuesta desde ");putip(tuip);
        printf(": fallida time=%ldms ttl=%d",ptime,tramapingenv[22]);
	ctapac[2]++;
	return(0);
}
void enviaping(sred *cabr,unsigned char *tuip,int *tiempopac,int sec,int tamtra)
{
        struct sockaddr_ll nic;
        int tamano;
        memset(&nic, 0, sizeof(struct sockaddr_ll));
        nic.sll_family= AF_PACKET;
        nic.sll_protocol = htons(ETH_P_ALL);
        nic.sll_ifindex=cabr->indice;
        tamano =sendto(cabr->paquete,tramapingenv,tamtra,0,(struct sockaddr *)&nic, sizeof(struct sockaddr_ll));
        if(tamano == -1)               
                perror("\nError al enviar ping");
	else
		{ctapac[0]++;reciveping(cabr,tuip,tiempopac,sec,tamtra);}
		
}
void estructuraping(sred*cabr,unsigned char *tumac,unsigned char *tuip,int secuencia,int ttl,int red,int *tiempopac,char *mensaje)
{
	memset(tramapingenv+0,0x00,74);
	if(red)
		memcpy(tramapingenv+0,tumac,6);
	else
		memcpy(tramapingenv+0,cabr->macenlace,6);
        memcpy(tramapingenv + 6,cabr->mac,6);
	tramapingenv[12]=0x08;//ethertipe ping
	tramapingenv[13]=0x00;//ethertipe ping
        ///sigue todo lo del encabezado ip
	tramapingenv[14]=0x45;//version ip
	tramapingenv[15]=0x00;//tiposervicio
	tramapingenv[16]=0x00;//longitud ip
	tramapingenv[17]=28+strlen(mensaje);//0x3c;//longitud ip
	tramapingenv[18]=0x10;
	tramapingenv[19]=0x00;
	tramapingenv[20]=0x00;
	tramapingenv[21]=0x00;	
        memcpy(tramapingenv +22,&ttl,1);
	tramapingenv[23]=0x01;//protocolo ping
	tramapingenv[24]=0x00;//checsum
	tramapingenv[25]=0x00;//checsum
	memcpy(tramapingenv +26,cabr->ip,4);
        memcpy(tramapingenv +30,tuip,4);
	checksum(14,33,&tramapingenv[25],&tramapingenv[24],tramapingenv);
        //ahora se llena el encabezado udp
	tramapingenv[34]=0x08;
	tramapingenv[35]=0x00;
	tramapingenv[36]=0x00;
	tramapingenv[37]=0x00;
	tramapingenv[38]=0x00;
	tramapingenv[39]=0x01;     
	tramapingenv[40]=0x00;
        memcpy(tramapingenv +41,&secuencia,1);
	memcpy(tramapingenv +42,mensaje,strlen(mensaje));
	checksum(34,74,&tramapingenv[37],&tramapingenv[36],tramapingenv);
//	checksum(34,(41+strlen(mensaje)),&tramapingenv[37],&tramapingenv[36],tramapingenv);
	enviaping(cabr,tuip,tiempopac,secuencia,(42+strlen(mensaje)));
}
