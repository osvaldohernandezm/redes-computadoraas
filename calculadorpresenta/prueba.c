#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <mysql/mysql.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define HOST "localhost"
#define USER "root"
#define PASS "toor"
#define BASE "prueba"
#define PORT 3306
#define IP 4
#define MAC 12
MYSQL *con;
MYSQL_RES *res;

int compararIP(unsigned char *);
void convertirMAC(unsigned char *,unsigned int *);

int main(void)
{
	int resp;
	unsigned char *ip;
	ip = (char *)malloc(sizeof(char)*IP);
	con = mysql_init(NULL);
	if(!mysql_real_connect(con,HOST,USER,PASS,BASE,PORT, NULL,0))
	{
		perror("\nError al conectar con la base\n");
		return (-1);
	}
	else
	{
		printf("\n\nConexion Exitosa!!!, %s\n\n",BASE);
	}
	printf("Introduzca la IP a buscar:\n");
	gets(ip);
	resp = compararIP(ip);
	if(resp == 1)
	{
		printf("\nSI ME SALIO\n");
	}
	else
	{
		perror("\nNO ME SALIO :(!!!\n");
	}
	return 1;
}

int compararIP(unsigned char *dirIP)
{
	int num = 0, i;
	MYSQL_ROW row;
	unsigned char MACnums[MAC], *MACpuntos;
	unsigned int MAChex[6];
	char consulta[200];
	sprintf(consulta,"SELECT MAC from macs_rec where IP = '%s' ",dirIP);
	if(mysql_query(con,consulta) == 0)
	{
		res = mysql_use_result(con);
		while(row = mysql_fetch_row(res))
		{
			MACpuntos = row[0];
			if(MACpuntos != NULL)
			{
				printf("\nLa direccion mac es: %s\n",MACpuntos);
				memcpy(MACnums,MACpuntos,2);
				memcpy(MACnums+2,MACpuntos+3,2);
				memcpy(MACnums+4,MACpuntos+6,2);
				memcpy(MACnums+6,MACpuntos+9,2);
				memcpy(MACnums+8,MACpuntos+12,2);
				memcpy(MACnums+10,MACpuntos+15,2);
				convertirMAC(MACnums, MAChex);
				for(i = 0; i < 6; i++)
				{
					printf("%.2x",MAChex[i]);
				}
				num = 1;
			}
		}
	}
	return num;
}
void convertirMAC(unsigned char *cadenaMAC, unsigned int *hex)
{
	unsigned char hexbyte[3] = {0};
	int octetos[sizeof(cadenaMAC)/2],d,i;
	for(d=0,i = 0;d<strlen(cadenaMAC);d+=2,i++)
	{
	        hexbyte[0]=cadenaMAC[d];
	        hexbyte[1] =cadenaMAC[d+1];
		sscanf(hexbyte,"%x",&octetos[d/2]);
		memcpy(hex+i,&octetos[d/2],2);
	}		
}
