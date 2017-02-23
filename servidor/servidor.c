//mysql -u root -p
//pones contraseña
//08 codigo pregunta por la ip
//09 codigo de respuesta de la ip
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <pthread.h>
unsigned char mi_mac[6];
unsigned char mi_ip[4];
unsigned char tramaenviada[60];
unsigned char tramarecivida[60];
unsigned char tu_mac[6];
unsigned char tu_ip[4];
unsigned char tipoether[2]={0x08,0x06};
unsigned char tipohardware[2] = {0x00, 0x01};
unsigned char tipoprotocolo[2] = {0x08, 0x00};
unsigned char LDH = 6;
unsigned char LDP = 4;
unsigned char codigoenvio[2]={0x00,0x01};
unsigned char codigorespuesta[2]={0x00,0x02};
unsigned char macpadre[6];
unsigned char ipinfractor[4];
unsigned char macverdadera[6];
FILE *ipmac;
int cod=0,j=0;
pthread_t aux[254];
typedef struct servidor
{
	unsigned char ip[4];
	unsigned char mac[6];
	struct servidor *sig;
}servidor;
servidor *nvo,*p,*cab;
void start(){cab=NULL;}
int obtenerDatos(int packet_socket,char *nombre[])
{
	int indice,i;
	struct ifreq interfaz;
	strcpy(interfaz.ifr_name,nombre[1]);
	if(ioctl(packet_socket,SIOCGIFINDEX,&interfaz)==-1)
	{
		perror("\nError al obtener el indice");
		return 0;
	}
	else
	{
		indice=interfaz.ifr_ifindex;
		if(ioctl(packet_socket, SIOCGIFHWADDR, &interfaz) == -1)
			perror("Error al obtener la dirección MAC.\n");
		else
		{
			memcpy(mi_mac, interfaz.ifr_hwaddr.sa_data, 6);
			printf("Tu direccion MAC es:\t\t");
			for(i = 0; i < 6; i++)
			{
				printf("%.2x", mi_mac[i]);
				if(i < 5)
					printf(":");
			}
			printf("\n");				
		}
		if(ioctl(packet_socket, SIOCGIFADDR, &interfaz) == -1)
			perror("Error al obtener la dirección IP.\n");
		else
		{
			printf("Tu dirección IP es:\t\t");
			for(i = 2; i < 6; i++)
			{
				mi_ip[i - 2] = interfaz.ifr_addr.sa_data[i];
				printf("%d", mi_ip[i - 2]);
				if(i < 5)
					printf(".");
			}
			printf("\n");
		}	
		return indice;
	}
}
void desarchiva()
{
	if((ipmac=fopen("ipmac.txt","r"))!=NULL)
	{
		while(!feof(ipmac))
		{
			if(feof(ipmac))
				{;}
			else
			{
				nvo=(servidor*)malloc(sizeof(servidor));
				fscanf(ipmac,"%x.%x.%x.%x\t%x:%x:%x:%x:%x:%x\n",(unsigned int *)&nvo->ip[0],(unsigned int *)&nvo->ip[1],(unsigned int *)&nvo->ip[2],(unsigned int *)&nvo->ip[3],(unsigned int *)&nvo->mac[0],(unsigned int *)&nvo->mac[1],(unsigned int *)&nvo->mac[2],(unsigned int *)&nvo->mac[3],(unsigned int *)&nvo->mac[4],(unsigned int *)&nvo->mac[5]);
				nvo->sig=NULL;
				if(cab==NULL)
					cab=nvo;
				else
				{
					for(p=cab;p->sig!=NULL;p=p->sig){;}
					p->sig=nvo;
				}
			}
		}
		fclose(ipmac);
	}
	else
		printf("Error al guardar las ip y las mac");

}
void imprime()
{
	int i;
	for(p=cab;p!=NULL;p=p->sig)
	{
		for(i=0;i<4;i++)
			printf("%.d.",p->ip[i]);
		printf("\t");
		for(i=0;i<6;i++)
			printf("%.2x:",p->mac[i]);
		printf("\n");
	}
}
void enviatrama(int packet_socket, int indice, unsigned char *tramaenviada)
{
	int tam;
	struct sockaddr_ll nic;
	memset(&nic, 0x00, sizeof(nic));
	nic.sll_family = AF_PACKET;
	nic.sll_protocol = htons(ETH_P_ALL);
	nic.sll_ifindex = indice;
	tam = sendto(packet_socket, tramaenviada, 60, 0, (struct sockaddr *)&nic, sizeof(nic));
	if(tam == -1)
		perror("\nError al enviar\n\n");
	else
		;//printf("\nenviado ala ip:  %d.%d.%d.%d\n",tu_ip[0],tu_ip[1],tu_ip[2],tu_ip[3]);
}
void estructuratramaenviar(int opc)
{
	if(opc==0)
	{
		memset(tu_mac,0xff,6);
		memcpy(codigorespuesta,codigoenvio,2);
		memcpy(mi_ip,tu_ip,6);
	}
	memcpy(tramaenviada + 0,tu_mac, 6);
	memcpy(tramaenviada + 6,mi_mac, 6);
	memcpy(tramaenviada + 12, tipoether, 2);
	memcpy(tramaenviada + 14, tipohardware, 2);
	memcpy(tramaenviada + 16, tipoprotocolo, 2);
	memcpy(tramaenviada + 18, &LDH, 1);
	memcpy(tramaenviada + 19, &LDP, 1);
	memcpy(tramaenviada + 20, codigorespuesta, 2);
	memcpy(tramaenviada + 22, mi_mac, 6);
	memcpy(tramaenviada + 28, tu_ip, 4);
	memcpy(tramaenviada + 32,tu_mac,6);
	memcpy(tramaenviada + 38, tu_ip, 4);	
}
int comprueba(unsigned char *tu_ip,unsigned char *tu_mac)
{	int opc=1,i;
	for(p=cab;p!=NULL&&opc==1;p=p->sig)
	{
		if(!memcmp(p->ip,tu_ip,4))
		{
			if(!memcmp(p->mac,tu_mac,6))
				opc=2;
			else
				opc=0;
		}
		else
			opc=1;
	}
	return opc;
}
void imprimemacip(unsigned char  *tu_ip,unsigned char  *tu_mac)
{
	int i;
	for(i=0;i<4;i++)
		printf("%.d.",tu_ip[i]);
	puts("");
	for(i=0;i<6;i++)
		printf("%.2x.",tu_mac[i]);
	puts("");
}
void recibetrama(int indice,int packet_socket,unsigned char *tramarecivida, int longitud)
{   //8.25.100.141
	int tam,opc,i;		
	memset(macpadre,0xff,6);
/*	ipinfractor[0]=8;
	ipinfractor[1]=25;
	ipinfractor[2]=100;
	ipinfractor[3]=141;*/
	puts("\n");
	while(1)  //usleep(2000);
	{
		tam=recvfrom(packet_socket,tramarecivida,longitud,0,NULL,0);
		if(tam==-1)
			{perror("\nError al recibir trama");}
		else
		{
			if(!memcmp(tramarecivida+0,macpadre,6))
			{	
				if(!memcmp(tramarecivida+20,codigoenvio,2))
				{
					if(!memcmp(tramarecivida+12,tipoether,2))
					{
//						if(!memcmp(tramarecivida+28,ipinfractor,4))						
//						{
							cod=1;
							memcpy(tu_ip,tramarecivida+28,4);
							memcpy(tu_mac,tramarecivida+6,6);
							imprimemacip(tu_ip,tu_mac);				
							opc=comprueba(tu_ip,tu_mac);
							if(opc==2)
								puts("\nip y mac coinsiden :)\n");
							if(opc==1)
								puts("\nla ip no se encuentra en la base de datos\n");
							if(opc==0)
							{
								puts("\ninfractor!!!\n");
								estructuratramaenviar(1);
	  							enviatrama(packet_socket, indice,tramaenviada);
								estructuratramaenviar(0);
	  							enviatrama(packet_socket, indice,tramaenviada);
	  						}		
//						}
					}
				}
			}
		}
	}
}
void *todo(void *args)
{
	int indice,paquete;
	indice=((int *)args)[0];
	paquete=((int *)args)[1];
	printf("indice=%d\npaquete=%d",indice,paquete);
	recibetrama(indice,paquete,tramarecivida,60);
	return("ya esta");
}
void espera(int args[2])
{
	while(cod==0)
	{
		;
	}
	j++;
	cod=0;
	if(j<254)
	{
		pthread_create(&aux[j],NULL,todo,(void *)args);
		espera(args);
	}
	if(j==254)
	{
		j=0;
	}
}
int main (int argi,char **argc)
{   
	int packet_socket,indice,error;
	int indpaque[2];
	packet_socket = socket(AF_PACKET,SOCK_RAW, htons(ETH_P_ALL));
	start();
 	desarchiva();	
	if(packet_socket==-1)
        	perror("\nError al abrir socket...");
	else
	{ 
		printf("\nExito al abrir el socket...\n");
		indice=obtenerDatos(packet_socket,argc);
/*		pthread_t hilo;
		indpaque[0]=indice;
		indpaque[1]=packet_socket;
		error=pthread_create(&hilo,NULL,todo,(void *)indpaque);
		if(error!=0)
			printf("no se pudo crear el hilo");
		espera(indpaque);
		pthread_join(aux[254],NULL);
		printf("\n\n\n");*/
		imprime();
	}
	return 0;
}

