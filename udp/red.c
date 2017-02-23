#include "red.h"
int i;
void parametros(int ari,char **arc,unsigned short *runo,unsigned short *rdos)
{
        int yapuso=0;
        for(i=0;i<ari;i++)
        {
                if(!strcmp(arc[i],"-i")&&yapuso==0){
                        sscanf(arc[i+1],"%d.%d.%d.%d",(int*)&cabr->tuip[0],(int*)&cabr->tuip[1],(int*)&cabr->tuip[2],(int*)&cabr->tuip[3]);
                        yapuso=1;
                }
                if(!strcmp(arc[i],"-h")&&yapuso==0){
                        char llamada[100]={"nslookup "};
                        strcat(llamada,arc[i+1]);
                        strcat(llamada," | grep 'Address: ' | cut -d ':' -f2 > host.dat");
                        system(llamada);
                        if((host=fopen("host.dat","r"))!=NULL)
                        {
                                fscanf(host," %d.%d.%d.%d",(int*)&cabr->tuip[0],(int*)&cabr->tuip[1],(int*)&cabr->tuip[2],(int*)&cabr->tuip[3]);
                        }
                        else
                        {printf("error al consegir ip del host %s\n",arc[1]);exit(-1);}
                        yapuso=1;
                        system("rm host.dat");
                }
                if(!strcmp(arc[i],"-r")){
                        sscanf(arc[i+1],"%d-%d",(int*)runo,(int*)rdos);
                }
         }
        if(yapuso==0)//0 es falso y cualquier otro valor !0 verdadero
        {
                printf("ERROR\n porfavor proporcione una IP a hacer el ping\n");
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
        system("rm puerta.dat ippublica.dat");
        return nvor;
}
