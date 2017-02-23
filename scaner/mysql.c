#include "mysql.h"
#include "red.h"
int conecta(char **miarg)
{
	con=mysql_init(NULL);
	if(!mysql_real_connect(con,miarg[0],miarg[1],miarg[2],NULL,0,NULL,0))
		{fprintf(stderr, "\n%s", mysql_error(con));exit(-1);}
	return 0;
}
int usebase(char *nbase)
{
	sprintf(consulta,"use %s",nbase);
	if(mysql_query(con,consulta))
		{fprintf(stderr, "\n%s", mysql_error(con));exit(-1);}
	return 0;
}
int creabase(char *nbase)
{
	sprintf(consulta,"create schema %s",nbase);
	if(mysql_query(con,consulta))	
		{fprintf(stderr, "\n%s", mysql_error(con));return 1;}
	usebase(nbase);
	return 0;
}
int creatabla(char *ntabla)
{
	sprintf(consulta,"create table %s(ip char(50) not null,mac char(70) not null,primary key(`ip`,`mac`))",ntabla);
	if(mysql_query(con,consulta))
		printf("erro al crear tabla");//fprintf(stderr, "\n%s", mysql_error(con));exit -1;}
	return 0;
}
int inserta(unsigned char *ip,unsigned char *mac)
{
	sprintf(consulta,"insert into ipmac values('%d.%d.%d.%d','%.2x:%.2x:%.2x:%.2x:%.2x:%.2x')",ip[0],ip[1],ip[2],ip[3],mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	if(mysql_query(con,consulta))
		{fprintf(stderr, "\n%s", mysql_error(con));return 1;}
	return 0;
}
