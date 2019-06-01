// FILE: 	main.c
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

#include "def.h"
#include "main.h"
#include "daemon.h"
#include "log.h"
#include "signals.h"

CONFIG config;
CONTROL control;

int main(int argc,char* argv[])
{
    int sock_lst,sock_con;
    int pid,length;
    struct sockaddr_in srvaddr;
    socklen_t len;
    char msg[BUFF_SIZE];
    char buff[BUFF_SIZE];
    char ipaddr[IP_STRING_LENGTH];

    initDefaults();

    logOpen();
    // Запускаем процесс демонизации
    goToDaemon();

    sock_lst=socket(AF_INET,SOCK_STREAM,0);
    if(sock_lst==-1)
    {
	snprintf(msg,BUFF_SIZE,"Ошибка создания сокета: %s",strerror(errno));
	logWrite(msg);
	exitDaemon();
    }
    memset(&srvaddr,0,sizeof(srvaddr));
    srvaddr.sin_family=AF_INET;
    srvaddr.sin_port=htons(config.server_port);
    srvaddr.sin_addr.s_addr=htonl(INADDR_ANY);

    if((bind(sock_lst,(struct sockaddr*)&srvaddr,sizeof(srvaddr)))==-1)
    {
	snprintf(msg,BUFF_SIZE,"Ошибка связывания сокета: %s",strerror(errno));
	logWrite(msg);
	exitDaemon();
    }
    if((listen(sock_lst,PKT_QUEUE_LENGTH))==-1)
    {
	snprintf(msg,BUFF_SIZE,"Ошибка очереди подключений: %s",strerror(errno));
	logWrite(msg);
	exitDaemon();
    }

    while(!control.exit_flag)
    {
	//sleep(1000);
	sock_con=accept(sock_lst,(struct sockaddr*)&srvaddr,&len);
	if(sock_con==-1 && control.debug_level>DEBUG_LEVEL_NORMAL)
	{
	    snprintf(msg,BUFF_SIZE,"Ошибка обработки запроса из очереди подключений:%s",strerror(errno));
	    logWrite(msg);
	    continue;
	}
	if(control.debug_level>DEBUG_LEVEL_NORMAL)
	{
	    inet_ntop(AF_INET,&(srvaddr.sin_addr),ipaddr,INET_ADDRSTRLEN);
	    snprintf(msg,BUFF_SIZE,"Создаём отдельный поток для обработки входящего подключения с IP-адреса: %s",ipaddr);
	    logWrite(msg);
	}
	pid=fork();
	if(pid<0)
	{
	    if(control.debug_level>DEBUG_LEVEL_SILENT)
	    {
		snprintf(msg,BUFF_SIZE,"Ошибка функции fork():%s",strerror(errno));
		logWrite(msg);
	    }
	    close(sock_con);
	    continue;
	}
	if(pid>0)
	{
	    close(sock_con);
	    continue;
	}
	while((length=recv(sock_con,buff,BUFF_SIZE,0)))
	{
	    if(control.debug_level>DEBUG_LEVEL_NORMAL)
	    {
		snprintf(msg,BUFF_SIZE,"Получено %d байт(а)",length);
		logWrite(msg);
	    }
	}
	close(sock_con);
	close(sock_lst);
	if(control.debug_level>DEBUG_LEVEL_NORMAL) logWrite("Завершение потока, обрабатывающего подключение");
	exit(RET_CODE_OK);
    }

    logWrite("Завершение работы демона");
    if(control.debug_level>DEBUG_LEVEL_SILENT) syslog(LOG_NOTICE,"Завершение работы демона");
    logClose();
    return RET_CODE_OK;
}

void initDefaults()
{
    config.server_port=DEFAULT_SERVER_PORT;
    strcpy(config.log_filename,DEFAULT_LOG_FILENAME);
    control.debug_level=DEBUG_LEVEL_FULL;
    control.log_fail=LOG_FAIL_EXIT;
    control.logfile=-1;
    control.exit_flag=0;
}

void exitDaemon()
{
    logWrite("Завершение работы демона");
    logClose();
    exit(RET_CODE_OK);
}