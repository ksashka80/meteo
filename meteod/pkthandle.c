// FILE: 	pkthandle.c
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#include <stdio.h>
#include <mysql/mysql.h>
#include <time.h>

#include "def.h"
#include "main.h"
#include "log.h"
#include "datapkt.h"

extern CONTROL control;
extern CONFIG config;

void HandlePacket(char* buff, int length)
{
    char msg[BUFF_SIZE];
    MYSQL *con=mysql_init(NULL);

    time_t cur_time;
    struct tm* t;

    cur_time=time(NULL);
    t=localtime(cur_time);

    if(con==NULL)
    {
	snprintf(msg,BUFF_SIZE,"Ошибка создания подключения к базе данных: %s",mysql_error(con));
	logWrite(msg);
	return;
    }

    if(mysql_real_connect(con,"localhost",config.dbUserName,config.dbPass,config.dbBaseName,0,NULL,0)==NULL)
    {
	snprintf(msg,BUFF_SIZE,"Ошибка подключения к базе данных: %s",mysql_error(con));
	logWrite(msg);
	mysql_close(con);
	return;
    }
    

    mysql_close(con);
}