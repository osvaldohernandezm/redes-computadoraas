#include "red.h"
#include "tracer.h"
int i,ctapac[3]={0,0,0},intime=0;
unsigned char ethertypeping[2]={0x08,0x00};
unsigned char tramapingenv[74];
unsigned char tramapingrec[74];
void estadisticas(int npac,unsigned char *ipaux)
{
	printf("\n %d",npac);
	if(!ctapac[0]&&!ctapac[1]&&!ctapac[2])
		{printf("\t\t\trespuesta fallida");}
	else
	{
		for(i=0;i<3;i++)
			{printf("\t%d ms",ctapac[i]);}
		printf("\t");putip(ipaux);
	}
	intime=ctapac[0]=ctapac[1]=ctapac[2]=0;
}
int compruebared(sred *cabr,unsigned char *tuip)
{
//      printf("miipp=");printfip(miipp);
        unsigned char miipmas[4];
        unsigned char tuipmas[4];
        for(i=0;i<4;i++)
        {
                miipmas[i]=cabr->ip[i]&cabr->mascara[i];
                tuipmas[i]=tuip[i]&cabr->mascara[i];
        }
//      puts("\nmiipmas=");printfip(miipmas);puts("\n");
//      puts("\ntuipmas");printfip(tuipmas);puts("\n");
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
int reciveping(sred *cabr,unsigned char *tuip,int sec,unsigned char *ipaux)
{
        int tamano;
        struct timeval start, end;
        long int ptime=0;
	gettimeofday(&start, NULL);
        while( ptime < 100)
        {
                tamano = recvfrom(cabr->paquete,tramapingrec,74,0,NULL,0);
                if(tamano == -1)
                        printf("Error al recibir ping");
                else
                {
			if(tramapingrec[34]==0x0b&&tramapingrec[35]==0x00)
			{
				gettimeofday(&end,NULL);
                		ptime =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;
//				printf("dentro de 0b %d\n",intime);
				memcpy(ipaux,tramapingrec+26,4);
				ctapac[intime]=ptime;
				intime++;
				return 0;
			}
			else
			{
				if(!memcmp(tramapingrec,cabr->mac,6)&&!memcmp(tramapingrec+12,ethertypeping,2)&&!memcmp(tramapingrec+26,tuip,4)&&!memcmp(tramapingrec+30,cabr->ip,4))
                        	{
//					puts("dentro if");
	                               	gettimeofday(&end, NULL);
	                                ptime =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
					memcpy(ipaux,tramapingrec+26,4);
	                                ctapac[intime]=ptime;intime++;
	                                /*printf("\nrespuesta desde ");putip(tuip);
        		               printf(": bytes=32 tiempo=%dms ttl=%d",(int)ptime,tramapingenv[22]);*/
					return(1);
                	        }
			}
                }
                gettimeofday(&end, NULL);
                ptime =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
        }
//	puts("fuera de wile");
	ctapac[intime]=0;intime++;
	return(0);
}
int enviaping(sred *cabr,unsigned char *tuip,int sec,unsigned char *ipaux,int tamtra)
{
        struct sockaddr_ll nic;
        int tamano;
        memset(&nic, 0, sizeof(nic));
        nic.sll_family= AF_PACKET;
        nic.sll_protocol = htons(ETH_P_ALL);
        nic.sll_ifindex=cabr->indice;
        tamano =sendto(cabr->paquete,tramapingenv,tamtra,0,(struct sockaddr *)&nic, sizeof(nic));
        if(tamano == -1)               
                perror("\nError al enviar ping");
	else
	{
		if(reciveping(cabr,tuip,sec,ipaux))
			return 1;
	}
	return 0;	
}
int estructuraping(sred*cabr,unsigned char *tumac,unsigned char *tuip,int secuencia,int ttl,int red,unsigned char *ipaux,char *mensaje)
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
	tramapingenv[17]=28+strlen(mensaje);//longitud ip
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
	memcpy(tramapingenv+42,mensaje,strlen(mensaje));
	checksum(34,74,&tramapingenv[37],&tramapingenv[36],tramapingenv);
	if(enviaping(cabr,tuip,secuencia,ipaux,(42+strlen(mensaje))))
		return (1);
	return (0);
}
