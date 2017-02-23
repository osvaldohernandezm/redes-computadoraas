#include "red.h"
#include "arp.h"
#include "ping.h"
unsigned char tuip[4],tumac[6];
sred *cabr=NULL;
int main(int ari,char **arc)//./a.out wlan0 192.168.1.95 -t 64 -p 5
{
        int paquete=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)),ttl=64,pac=4,ciclo;
	char *mensaje=(char *)malloc(32*sizeof(char));strcpy(mensaje,"Hola soy adan");
        if(paquete==-1)
                {puts("error al abrir el socket");return 1;}
        else
        {
                parametros(ari,arc,&ttl,&pac,tuip,mensaje);
                cabr=datosred(arc[1],paquete);
                putdatos(cabr);
                int tiempopac[pac];
                printf("\n\nHaciendo ping a ");putip(tuip);
                printf(" con %d bytes de datos:\n",strlen(mensaje));
                if(compruebared(cabr,tuip))
                {
                        printf("\n\ndentro de la red!\n");
                        estructuraarp(cabr,tuip,tumac);
                        for(ciclo=0;ciclo<pac;ciclo++)
                        {
                                estructuraping(cabr,tumac,tuip,ciclo+1,ttl,1,tiempopac,mensaje);
                        }
                }
                else
                {
                        puts("\nfuera de la red");
                        for(ciclo=0;ciclo<pac;ciclo++)
                        {
                                estructuraping(cabr,tumac,tuip,ciclo+1,ttl,0,tiempopac,mensaje);
                        }
                }
                estadisticas(tiempopac,tuip,pac);
        }
        return 0;
}
