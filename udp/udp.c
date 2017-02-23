#include "red.h"
#include "udp.h"
int i;
unsigned char ethertypeping[2]={0x08,0x00};
unsigned char compruebared(){
        unsigned char miipmas[4];
        unsigned char tuipmas[4];
        for(i=0;i<4;i++){
                miipmas[i]=cabr->ip[i]&cabr->mascara[i];
                tuipmas[i]=cabr->tuip[i]&cabr->mascara[i];
        }
        if(!memcmp(miipmas,tuipmas,4))
                return ((unsigned char )1);
      	return ((unsigned char)0);
}
void checksum(int limi, int lims, unsigned char *check0, unsigned char *check1, unsigned char *mtrama){
	unsigned int suma=0;
        unsigned short aux;
	if(limi==26){suma=25;}
        for(i=limi;i<lims;i+=2){
                aux=mtrama[i];
                aux=(aux<<8)+mtrama[i+1];
                suma=suma+aux;
        }
        suma=(suma&0x0000FFFF)+(suma>>16);
        *check0=(unsigned char)~(suma);
        *check1=(unsigned char)~(suma>>8);
}
unsigned char recive(unsigned short puerto,unsigned short j){
	unsigned char tramarec[74];
        int tamano,ptime=0;
        struct timeval start, end;
	gettimeofday(&start, NULL);
        while( ptime<1000){
                tamano = recvfrom(cabr->paquete,tramarec,74,0,NULL,0);
                if(tamano == -1)
                        {printf("Error al recibir ping");}
		if(!memcmp(cabr->mac,tramarec+0,6)&&tramarec[34]==0x03&&tramarec[64]==(puerto>>8)&&tramarec[65]==(puerto&0x00FF)){
			cerrado++;
			fprintf(fc,"%d\n",puerto);return (1);
		}
        	gettimeofday(&end, NULL);
	        ptime =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
        }
	if(j==2)
		fprintf(fc,"%d\n",puerto);	
	return (0);
}
unsigned char envia(unsigned char *tramaenv,unsigned short puerto,unsigned short j){
        struct sockaddr_ll nic;
        int tamano;
        memset(&nic, 0, sizeof(struct sockaddr_ll));
        nic.sll_family= AF_PACKET;
        nic.sll_protocol = htons(ETH_P_ALL);
        nic.sll_ifindex=cabr->indice;
        tamano =sendto(cabr->paquete,tramaenv,42,0,(struct sockaddr *)&nic, sizeof(struct sockaddr_ll));
        if(tamano == -1)               
                {perror("\nError al enviar ping");}
	return(recive(puerto,j));
}
unsigned char estructura(unsigned char *tramaenv,unsigned short puerto,unsigned char red,unsigned short j){
	srand(pthread_self());
	memset(tramaenv,0,74);
        if(red)
                memcpy(tramaenv+0,cabr->tumac,6);
        else
                memcpy(tramaenv+0,cabr->macenlace,6);
        memcpy(tramaenv+6,cabr->mac,6);
        memcpy(tramaenv+12,ethertypeping,2);
        tramaenv[14]=69;
        tramaenv[15]=0;
        tramaenv[16]=0;
        tramaenv[17]=28;
        tramaenv[18]=(puerto-11+(rand()%33))>>8;
        tramaenv[19]=(puerto-3+(rand()%11));
        tramaenv[20]=0;//cheksum
        tramaenv[21]=0;
        tramaenv[22]=64;//ttl
        tramaenv[23]=17;
        memcpy(tramaenv+26,cabr->ip,4);
        memcpy(tramaenv+30,cabr->tuip,4);
        tramaenv[34]=(puerto+11-(rand()%11))>>8;//d1b5
        tramaenv[35]=(puerto+3-(rand()%33));//d1b5
	tramaenv[36]=puerto>>8;//d1b5
        tramaenv[37]=puerto;
        tramaenv[39]=8;
        checksum(26,74,&tramaenv[41],&tramaenv[40],tramaenv);
        checksum(14,33,&tramaenv[25],&tramaenv[24],tramaenv);	return(envia(tramaenv,puerto,j));
}
