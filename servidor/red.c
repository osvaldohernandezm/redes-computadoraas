#include "red.h"
int i;
void parametros(int ari,char **arc,char **miarg)
{
	tuip=(unsigned char *)malloc(4*sizeof(unsigned char));
	tumac=(unsigned char *)malloc(6*sizeof(unsigned char));
        for(i=0;i<ari;i++)
        {
		if(!memcmp(arc[i],"-r",2))
		{
			sscanf(arc[i+1],"%d-%d",&cabr->r1,&cabr->r2);
		}
		if(!memcmp(arc[i],"-s",2))
		{
			memcpy(miarg[0],arc[i+1],50);
		}
		if(!memcmp(arc[i],"-u",2))
		{
			memcpy(miarg[1],arc[i+1],50);
		}
		if(!memcmp(arc[i],"-c",2))
		{
			memcpy(miarg[2],arc[i+1],50);
		}
		if(!memcmp(arc[i],"-b",2))
		{
			memcpy(miarg[3],arc[i+1],50);
		}
		if(!memcmp(arc[i],"-i",2))
		{
			sscanf(arc[i+1],"%d.%d.%d.%d",(int*)&tuip[0],(int*)&tuip[1],(int*)&tuip[2],(int*)&tuip[3]);
		}
		if(!memcmp(arc[i],"-m",2))
		{
			sscanf(arc[i+1],"%x:%x:%x:%x:%x:%x",(unsigned int *)&tumac[0],(unsigned int *)&tumac[1],(unsigned int *)&tumac[2],(unsigned int *)&tumac[3],(unsigned int *)&tumac[4],(unsigned int *)&tumac[5]);
		}	
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
void putdatos()
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
                fscanf(puerta,"? (%d.%d.%d.%d) en %x:%x:%x:%x:%x:%x",(int*)&nvor->ipenlace[0],(int*)&nvor->ipenlace[1],(int*)&nvor->ipenlace[2],(int*)&nvor->ipenlace[3],(unsigned int *)&nvor->macenlace[0],(unsigned int *)&nvor->macenlace[1],(unsigned int *)&nvor->macenlace[2],(unsigned int *)&nvor->macenlace[3],(unsigned int *)&nvor->macenlace[4],(unsigned int *)&nvor->macenlace[5]);
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
