//service mysql start
//mysql -u root -p
//pones contraseña
//show databases; (para ver todas las bases de datos)
//create database NOMBRE DE LA BASE; (para crear una base)
//use NOMBRE DE LA BASE; (para seleccionar una base de datos a usar)
//create table NOMBRE DE LA BASE(NOMBRE DEL ATRIBUTO VARCHAR(40),NOMBRE DE ATRIBUTO INT,.... );(creas una tabla de base)
//select *from NOMBRE DE LA TABLE; (ves el contenido de la tabla selexionada)
//insert into NOMBRE DE LA TABLA values('adan','5540027762'),('mary','55314689')...;(meter elementos ala tabla)
//update NOMBRE DE LA TABLA set atributo='5540034687' where nombre='adan';(cambia el atribuno del elemento adan)
//delete from NOMBRE DE LA TABLA where nombre='mary';(borra el elemnto o tupla mary completo )

#include <stdio.h>
#include <stdlib.h>
//#include <mysql.h>
#include <mysql/mysql.h>
#define HOST "localhost"	//nombre del servidor local
#define USER "root"		//nombre de usuario
#define PASS "toor"	//pasword del usuario
#define DB "prueba"		//nombre de la base de datos
void mustra(MYSQL *con,char *consulta0,MYSQL_ROW row,MYSQL_RES *res);
void agrega(MYSQL *con,char *persona, char *telefono);
void elimina(MYSQL *con,char *eliminal);
void modifica_tel(MYSQL *con,char *new_tel,char *per_tel);
int main(void)
{
	MYSQL *con;
	MYSQL_ROW row;
	MYSQL_RES *res;
	char persona[20],eliminar[20],per_tel[20];
	char telefono[10],new_tel[10];
	char consulta0[1024];
	int opcion=1;
	con=mysql_init(NULL);
	if(!mysql_real_connect(con,HOST,USER,PASS,BD,3
06,NULL,0))
	{
		fprintf("stderr,%s\n",mysql_error(con));
		return 1;
	}
	fprintf(stdout,"->Conectado a Base de datos: %s\n",DB);
	sprintf(consulta0,"SELECT *FROM persona");
	do
	{
		getchar();
		system("clear");
		fprintf(stdout,"0 salir\t\t   \n");
		fprintf(stdout,"1 mostrar persona\t\t   \n");
		fprintf(stdout,"2 insertar persona\t\t   \n");
		fprintf(stdout,"3 eliminar persona\t\t   \n");
		fprintf(stdout,"4 modificar tel de persona\t\t   \n");
		fscnaf(stdin,"%d",&opcion);
		switch(opcion)
		{
			case 0: break;
			case 1:
			fprintf(stdout,"\nDatos actuales en la DB\n");
			muestra(con,consulta0,row,res);
			getcjar();
			break;
			case 2:
			fprintf(stdout,"ponga el nombre de la persona \n");
			fscanf(stdin,"%s",&persona);
			fprintf(stdout,"ponga el telefono de la persona\n");
			fscanf(stdin,"%s",&telefono);
			agrega(con,persona,telefono);
			break;
			case 3:
			fprintf(stdout,"ingrese el nombre de la persona a eliminar\n");
			fscanf(stdin,"%s",&eliminar);
			elimina(con,eliminar);
			break;
			case 4:
			fprintf(stdout,"ingrese el nombre de la persona a modificar \n");
			fscanf(stdin,"%s",&per_tel);
			fprintf(stdout,"ingrese el nuevo telefono para la persona\n");
			fscanf(stdin,"%s",&new_tel);
			modifica_tel(con,new_tel,per_tel);
			break;
			default: fprintf(stdout,"opcion invalida\n");
		}
	}while(opcion!=0);
	mysql_close(con);
	fprintf(stdout,"conexion terminada\n");
}
void muestra(MYSQL *con,char *consulta0,MYSQL_ROW row,MYSQL_RES *res)
{
	if(mysql_query(con,consulta0)==0)
	{
		res=mysql_use_result(con);
		printf("  nombre  \ttelefono  \n");
		while((row=mysql_fetch_row(res)))
		{
			printf("  %s\t ",row[0]);
			printf("  %s\t",row[1]);
		}
		if(!mysql_eof(res))
		{
			printf("error de lectrura %s\n",mysql_error(con));
		}	
	}
}
void agrega(MYSQL *con,char *persona,char *telefono)
{
	char consulta[1024];
	sprintf(consulta,"INSERT INTO persona VALUES('%s','%s')",persona,telefono);
	if(mysql_query(con,consulta)==0)
		fprintf(stdout,"\nDatos insertados con exito\n");	
}
void elimina(MYSQL *con,char *eliminar)
{
	char consulta[1024];
	sprintf(consulta,"DELETE FROM persona WHERE nombre='%s'",eliminar);
	if(mysql_query(con,consulta)==0)
		fprintf(stdout,"\nPersona eliminada con exito");	
}
void modifica_tel(MYSQL *con,char *new_tel,char *per_tel)
{
	char consulta[1024];
	sprintf(consulta,"UPDATE persona SET telefono='%s' WHERE nombre='%s'",new_tel,per_tel);
	if(mysql_query(con,consulta==0))
		fprintf(stdout,"\n #de telefono modificado con exito\n");
}
