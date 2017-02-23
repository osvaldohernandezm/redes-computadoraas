//gcc -g3 nombredelprograma.c
//llc&&(eth.addr==00:00:e8:15:bb:75||eth.addr==00:20:18:66:c6:02)
#include "red.h"
#include "llc.h"
#include "analisa.h"
int main(int ari,char **arc)//./a.out wlan0 -r 5-2 -s localhost -u usuario -c clave -b basedatos -i ip -m mac
{
        int paquete=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)),menu=0;
	pthread_t hres[3];
        if(paquete==-1)
                {puts("error al abrir el socket");return 1;}
        else
        {
		macdes=(unsigned char *)malloc(6*sizeof(unsigned char));
		tumac=(unsigned char *)malloc(6*sizeof(unsigned char));
		cabr=NULL;cabt=NULL;
                cabr=datosred(arc[1],paquete);
                putdatos();
		printf("\n\nPresione\n\t1 para generar trafico llc\n\t2 para recivir de la red\n\n");
		scanf("%d",&menu);
		if(menu==1)
		{	
			pthread_create(&hres[0],NULL,resivellc,(void *)(menu-1));
			pthread_create(&hres[1],NULL,fichero,(void *)arc[2]);
		}
		else
			pthread_create(&hres[0],NULL,resivellc,(void *)menu);
		sleep(2);
		pthread_create(&hres[2],NULL,analisatrama,NULL);
		pthread_join(hres[0],NULL);
        }
        return 0;
}
