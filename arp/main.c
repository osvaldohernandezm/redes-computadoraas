/*
http://www.youtube.com/watch?v=0m143AUwTYw&list=UUBtiIu08BaEWQiC-dRZ6jNg
6366356663 infinitum2d4b
3663333833 infinutum6553
3138961954 galaxia
23055C3D1D infinitum7a5b74
6137613938 infinitumfb4
55FF632592 infinitum4A735F
4038801874 infinitum3382
9773BD5834 infinitum17E5E9
97CE094DF5 infinitum89130E
5619693464 infinitum3578
DA44FF536B infinitumC55E2
7D02A1B344 infinitumA4FB79
5536997922	eunice
MARRANA 94:39:e5:6e:e1:d1
JUERO	00:16:6f:c6:50:b7
CelJue	90:c1:15:cc:43:a4
*/
#include "red.h"
#include "arp.h"
unsigned char tuip[4],tumac[6];
sred *cabr=NULL;
void *esvia(void *args)
{
	estructuraarp(cabr,tuip);
	return 0;
}
int main(int ari,char **arc)//./a.out wlan0 -i 192.168.1.95
{
        int paquete=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)),ciclo=1,j;
        if(paquete==-1)
                {puts("error al abrir el socket");return 1;}
        else
        {
                parametros(ari,arc,&ciclo,tuip);
                cabr=datosred(arc[1],paquete);
                putdatos(cabr);
		pthread_t hilo[ciclo];
		if(ciclo>1)
		{
			for(j=0;j<ciclo;j++)
				pthread_create(&hilo[ciclo],NULL,esvia,NULL);
		}
		else
			estructuraarp(cabr,tuip);
		pthread_join(hilo[ciclo],NULL);
        }
        return 0;
}
