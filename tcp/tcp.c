#include "red.h"
#include "tcp.h"
int i,cta=200;
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
	if(limi==26){suma=30;}
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
        int tamano,ptime=0,k,bandera=0;
        struct timeval start, end;
	gettimeofday(&start, NULL);
        while( ptime<1000){
                tamano = recvfrom(cabr->paquete,tramarec,74,0,NULL,0);
                if(tamano == -1)
                        {printf("Error al recibir ping");}

		if(!memcmp(cabr->mac,tramarec+0,6)&&!memcmp(cabr->tuip,tramarec+26,4)&&tramarec[47]==0x12){//syncronia ack abierto
				pthread_mutex_lock(&mutexpa);
				puerto=(((puerto>>16)+tramarec[34])<<8)+tramarec[35];
//				printf("\npuerto %d abierto",puerto);
				for(k=0;pa[k]!=0;k++){
					if(pa[k]==puerto){
						bandera=1;		
					}
				}
				if(!bandera){
					pa[ctapa]=puerto;
					ctapa++;	
				}
				pthread_mutex_unlock(&mutexpa);
				if(tramarec[34]==puerto>>8&&tramarec[35]==(puerto&0x00FF)){
					return 1;
				}return 0;
		}
		if(!memcmp(cabr->mac,tramarec+0,6)&&!memcmp(cabr->tuip,tramarec+26,4)&&tramarec[47]==0x14){//reset cerrado
			pthread_mutex_lock(&mutexpc);
			puerto=(((puerto>>16)+tramarec[34])<<8)+tramarec[35];
//			printf("\npuerto %d cerrado",puerto);
			for(k=0;pa[k]!=0;k++){
				if(pc[k]==puerto){
					bandera=1;		
				}
			}
			if(!bandera){
				pc[ctapc]=puerto;
				ctapc++;	
			}
			pthread_mutex_unlock(&mutexpc);
			if(tramarec[34]==puerto>>8&&tramarec[35]==(puerto&0x00FF)){
				return 1;
			}
			return 0;
		}
        	gettimeofday(&end, NULL);
	        ptime =(end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
        }
	return (0);
}
unsigned char envia(unsigned char *tramaenv,unsigned short puerto,unsigned short j){
        struct sockaddr_ll nic;
        int tamano;
        memset(&nic, 0, sizeof(struct sockaddr_ll));
        nic.sll_family= AF_PACKET;
        nic.sll_protocol = htons(ETH_P_ALL);
        nic.sll_ifindex=cabr->indice;
        tamano =sendto(cabr->paquete,tramaenv,58,0,(struct sockaddr *)&nic, sizeof(struct sockaddr_ll));
        if(tamano == -1)               
                {perror("\nError al enviar ping");}
	return(recive(puerto,j));
}
unsigned char estructura(unsigned char *tramaenv,unsigned short puerto,unsigned char red,unsigned short j){
	memset(tramaenv,0,74);
        if(red)
                memcpy(tramaenv+0,cabr->tumac,6);
        else
                memcpy(tramaenv+0,cabr->macenlace,6);
        memcpy(tramaenv+6,cabr->mac,6);
        memcpy(tramaenv+12,ethertypeping,2);
	tramaenv[14]=69;/*ecavesado ip 20 0x45 5*4*/
        tramaenv[15]=0;
        tramaenv[16]=0;
        tramaenv[17]=44;
	tramaenv[18]=cta>>8;
	tramaenv[19]=cta;
	cta++;
	if(cta==0x25000){cta=300;}
        tramaenv[20]=0;//cheksum
        tramaenv[21]=0;
        tramaenv[22]=0x64;//ttl
        tramaenv[23]=6;
        memcpy(tramaenv+26,cabr->ip,4);
        memcpy(tramaenv+30,cabr->tuip,4);
        tramaenv[34]=(puerto+cta)>>8;//puerto origen 2bytes
        tramaenv[35]=(puerto+cta);//d1b5
        tramaenv[36]=puerto>>8;//puerto destino 2byts
        tramaenv[37]=puerto;
        tramaenv[38]=cta>>8;
        tramaenv[39]=(cta+puerto);
        tramaenv[40]=puerto>>8;
        tramaenv[41]=puerto;
        memset(tramaenv+42,0,4);//numero de reconocimiento
        tramaenv[46]=80;//4bytes desplasamiento (0101) el resto reservado (000000),6 bits pero solo estamos agarrando 4 para completar octeto
        tramaenv[47]=2;//syncronia
	tramaenv[48]=0x39;//ventana espacio sobrante en la tramaenviada[74]-(1024),2cheksum,2punturourgente
	tramaenv[49]=0x08;//50,51son de checksum
	tramaenv[54]=0x02;
	tramaenv[55]=0x04;
	tramaenv[56]=0x05;
	tramaenv[57]=0xb4;
        checksum(26,74,&tramaenv[51],&tramaenv[50],tramaenv);
        checksum(14,33,&tramaenv[25],&tramaenv[24],tramaenv);  
	return(envia(tramaenv,puerto,j));
}
