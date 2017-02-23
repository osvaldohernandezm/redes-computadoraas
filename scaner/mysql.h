#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#ifndef __MYSQL_H__
#define __MYSQL_H__
MYSQL *con;
MYSQL_RES *res;
MYSQL_ROW row;
char consulta[150];
int conecta(char **miarg);
int usebase(char *nbase);
int creabase(char *nbase);
int creatabla(char *ntabla);
int inserta(unsigned char *ip,unsigned char *mac);
#endif
