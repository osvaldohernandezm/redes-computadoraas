//gcc -g3 nombredelprograma.c
#include "red.h"
#include "arp.h"
#include "mysql.h"
int main(int ari,char **arc)//./a.out wlan0 -r 5-2 -s localhost -u usuario -c clave -b basedatos -i ip -m mac
{
        int paquete=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)),j;
	char **miarg=(char **)malloc(4*sizeof(char));
        if(paquete==-1)
                {puts("error al abrir el socket");return 1;}
        else
        {
		cabr=NULL;
//		memset(tuip,0x63,4);
//		memset(tumac,0xcc,6);
	        for(j=0;j<4;j++)
                	miarg[j]=(char *)malloc(50*sizeof(char));
		ipm=(unsigned char *)malloc(4*sizeof(unsigned char));
		macm=(unsigned char *)malloc(6*sizeof(unsigned char));
		memset(macpadre+0,0xff,6);
		memcpy(miarg[0],"localhost",9);
		memcpy(miarg[1],"root",4);
		memcpy(miarg[2],"toor",4);
		memcpy(miarg[3],"scaner",6);
                parametros(ari,arc,miarg);
                cabr=datosred(arc[1],paquete);
                putdatos();
		system("service mysql start");
		conecta(miarg);
		usebase(miarg[3]);
		pthread_mutex_init(&mutex,NULL);
		pthread_mutex_init(&mutex2,NULL);
		pthread_create(&hres[0],NULL,resivearp,NULL);
		pthread_join(hres[0],NULL);
        }
        return 0;
}
