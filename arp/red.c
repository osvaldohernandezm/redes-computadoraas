#include "red.h"
int i;
void parametros(int ari,char **arc,int *ciclo,unsigned char *tuip)//./a.out wlan0 -i 192.168.1.15
{
        int yapuso=0;
        for(i=0;i<ari;i++)
        {
                if(!memcmp(arc[i],"-i",2)&&yapuso==0)
                {
                        sscanf(arc[i+1],"%d.%d.%d.%d",(int*)&tuip[0],(int*)&tuip[1],(int*)&tuip[2],(int*)&tuip[3]);
                        yapuso=1;
                }
		if(!memcmp(arc[i],"-p",2))
		{
			sscanf(arc[i+1],"%d",ciclo);
		}
         }
        if(yapuso==0)//0 es falso y cualquier otro valor !0 verdadero
        {
                printf("ERROR\n porfavor proporcione una IP \n");
                exit(-1);
        }
}
void putip(unsigned char *ip)
{
	for(i=0;i<4;i++)
	{
		printf("%d",ip[i]);
		if(i==3)
			continue;
		printf(".");
	}
}
void putmac(unsigned char *mac)
{
	for(i=0;i<6;i++)
        {
                printf("%.2x",mac[i]);
                if(i==5)
                        continue;
                printf(":");
        }
}
void putdatos(sred *cabr)
{
	printf("\n\t\tpaquete:\t\t\t%d",cabr->paquete);
	printf("\n\t\tindice:\t\t\t\t%d",cabr->indice);
	printf("\n\t\tip:\t\t\t\t");putip(cabr->ip);
	printf("\n\t\tmac:\t\t\t\t");putmac(cabr->mac);
	printf("\n\t\tmascara:\t\t\t");putip(cabr->mascara);
	printf("\n\t\tip publica:\t\t\t");putip(cabr->ippu);
	printf("\n\t\tip puerta enlace:\t\t");putip(cabr->ipenlace);
	printf("\n\t\tmac puerta enlace\t\t");putmac(cabr->macenlace);
}
sred * datosred(char *interfaz,int paq)
{
        struct ifreq infointerfaz;
	sred *nvor;
        strcpy(infointerfaz.ifr_name,interfaz);
	nvor=(sred *)malloc(sizeof(sred));
	nvor->paquete=paq;
        if(ioctl(paq,SIOCGIFINDEX,&infointerfaz)==-1)
                {perror("\nerror al obtener indice");exit(-1);}
        nvor->indice=infointerfaz.ifr_ifindex;
        if(ioctl(paq,SIOCGIFHWADDR,&infointerfaz)==-1)
                {perror("\nerro al obtener la mac");}
        else
                {memcpy(nvor->mac+0,infointerfaz.ifr_hwaddr.sa_data,6);}
        if(ioctl(paq,SIOCGIFADDR,&infointerfaz)==-1)
                {perror("\nerro al obener la ip");}
        else
                {memcpy(nvor->ip+0,infointerfaz.ifr_addr.sa_data+2,4);}
        if(ioctl(paq,SIOCGIFNETMASK,&infointerfaz)==-1)
                {perror("\nerror al obtener la mascara de subrred");}
        else
                {memcpy(nvor->mascara,infointerfaz.ifr_netmask.sa_data+2,4);}
        system("arp -an > puerta.dat");
        if((puerta=fopen("puerta.dat","r"))!=NULL)
        {
                fscanf(puerta,"? (%d.%d.%d.%d) at %x:%x:%x:%x:%x:%x",(int*)&nvor->ipenlace[0],(int*)&nvor->ipenlace[1],(int*)&nvor->ipenlace[2],(int*)&nvor->ipenlace[3],(unsigned int *)&nvor->macenlace[0],(unsigned int *)&nvor->macenlace[1],(unsigned int *)&nvor->macenlace[2],(unsigned int *)&nvor->macenlace[3],(unsigned int *)&nvor->macenlace[4],(unsigned int *)&nvor->macenlace[5]);
        }
        else
                {printf("\nError al abrir el archivo");exit(-1);}
        fclose(puerta);
	/*system("GET http://www.vermiip.es/  | grep 'Tu IP p&uacute;blica es' | cut -d ':' -f2 | cut -d '/' -f1 > ippublica.dat");
        if((ippublica=fopen("ippublica.dat","r"))!=NULL)
        {
                fscanf(ippublica," %d.%d.%d.%d<",(int*)&nvor->ippu[0],(int*)&nvor->ippu[1],(int*)&nvor->ippu[2],(int*)&nvor->ippu[3]);
        }
        else
                {printf("\nerror al obtener la ip publica");exit(-1);}
        fclose(ippublica);*/
	nvor->sig=NULL;
        system("rm puerta.dat ippublica.dat");
        return nvor;
}
