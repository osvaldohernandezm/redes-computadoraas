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
	sprintf(consulta,"create table %s(ip char(20) not null,mac char(30) not null,primary key(`ip`,`mac`))",ntabla);
	if(mysql_query(con,consulta))
		printf("erro al crear tabla");//fprintf(stderr, "\n%s", mysql_error(con));exit -1;}
	return 0;
}
int inserta(unsigned char *ip,unsigned char *mac)
{
	sprintf(consulta,"insert into ipmac values('%x.%x.%x.%x','%x:%x:%x:%x:%x:%x')",ip[0],ip[1],ip[2],ip[3],mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	if(mysql_query(con,consulta))
		{fprintf(stderr, "\n%s", mysql_error(con));return 1;}
	return 0;
}
int comprueba(unsigned char *ipin,unsigned char *macin)
{
	sprintf(consulta,"select * from ipmac where ip='%d.%d.%d.%d'",ipin[0],ipin[1],ipin[2],ipin[3]);
	if (mysql_query(con,consulta))
		{fprintf(stderr, "%s\n", mysql_error(con));printf("\n\n\t\t\terror mysql");exit(-1);}
	res=mysql_use_result(con);
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		sscanf(row[0],"%d.%d.%d.%d",(int*)&ipm[0],(int*)&ipm[1],(int*)&ipm[2],(int*)&ipm[3]);
		sscanf(row[1],"%x:%x:%x:%x:%x:%x",(unsigned int *)&macm[0],(unsigned int *)&macm[1],(unsigned int *)&macm[2],(unsigned int *)&macm[3],(unsigned int *)&macm[4],(unsigned int *)&macm[5]);
		if(!memcmp(ipin+0,ipm+0,4))
		{
			if(!memcmp(macin+0,macm+0,6))
			{
				mysql_free_result(res);
				return 0;
			}
			printf("\n\nla mac es incorrecta");
			printf("\nip:");putip(ipin);printf("\tmac:");putmac(macin);
			memcpy(cabr->macbase+0,macm+0,6);
			//printf("cabr->macbase====");putmac(cabr->macbase);
			mysql_free_result(res);
			return 1;
		}
	}
	mysql_free_result(res);
	return 3;
}
