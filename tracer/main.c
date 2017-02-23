#include "red.h"
#include "arp.h"
#include "tracer.h"
unsigned char tuip[4],tumac[6];
sred *cabr=NULL;
int main(int ari,char **arc)//./a.out wlan0 192.168.1.95 -t 64 -p 5
{
        int paquete=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)),ttl=64,pac=30,ciclo,j;
        unsigned char *ipaux=(unsigned char *)malloc(4*sizeof(unsigned char));
	char *mensaje=(char *)malloc(32*sizeof(char));
	if(paquete==-1)
                {puts("error al abrir el socket");return 1;}
        else
        {
                parametros(ari,arc,&ttl,&pac,tuip,mensaje);
                cabr=datosred(arc[1],paquete);
                putdatos(cabr);
                printf("\n\ntraza ala direccion ");putip(tuip);
                printf(" sobre un maximo de %d saltos:\n",pac);
                if(compruebared(cabr,tuip))
                {
                        printf("\n\ndentro de la red!\n");
                        estructuraarp(cabr,tuip,tumac);
                        for(ciclo=0;ciclo<pac;ciclo++)
                        {
				for(j=0;j<3;j++)
				{
                                	if(estructuraping(cabr,tumac,tuip,ciclo+1,ciclo+1,1,ipaux,mensaje)&&j==2)
						{estadisticas(ciclo+1,ipaux);puts("\n\ntraza completa");return 0;}
				}
				estadisticas(ciclo+1,ipaux);
                        }
                }
                else
                {
                        puts("\nfuera de la red");
                        for(ciclo=0;ciclo<pac;ciclo++)
                        {
				for(j=0;j<3;j++)
				{
	                                if(estructuraping(cabr,tumac,tuip,ciclo+1,ciclo+1,0,ipaux,mensaje)&&j==2)
						{estadisticas(ciclo+1,ipaux);puts("\n\ntraza completa");return 0;}
				}
				estadisticas(ciclo+1,ipaux);
                        }
                }
        }
        return 0;
}
