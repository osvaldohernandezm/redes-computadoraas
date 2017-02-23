//udi.2011
//service mysql start
//mysql -u root -p
//pones contraseña
//arp -an //mustra la ip de mi router
//netstat -nr
#include "arp.h"
unsigned char mimac[6];
unsigned char miip[4];
unsigned char mascara[4];
unsigned char enlace[4];
unsigned char tumac[6];
unsigned char tuip[4];
void *todo(void *arg)
{
	tuip[3]=((int *)arg)[2];
	int indice,paquete;
	indice=((int *)arg)[0];
        paquete=((int *)arg)[1];
	estructuratrama(miip,mimac,tuip,tumac,paquete,indice);
//        enviatrama(paquete,indice,tramaenviada);
//        recibetrama(paquete,tramarecivida,60);
        return("ya ta");
}
int main(int ari,char **arc)
{
	pthread_t hilo[255];
	int paquete=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)),miindice,i,arg[3];
	if(paquete==-1)
		{puts("error al abrir el socket"); exit(-1);}
        else
        {
//              printf("paquete:\t%d\n",paquete);
                printf("\n\n");
                miindice=datosdered(arc[1],miip,mimac,mascara,enlace,paquete);
		arg[0]=miindice;
                arg[1]=paquete;
                memcpy(tuip+0,miip,3);
                for(i=0;i<255;i++)
                {
                        arg[2]=i;
                        pthread_create(&hilo[i],NULL,todo,(void *)arg);
                        usleep(100000);         
                } 
	}
	return(0);
}
