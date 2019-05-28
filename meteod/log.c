// FILE: 	log.c
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "def.h"
#include "main.h"
#include "log.h"

extern CONFIG config;
extern CONTROL control;

void logOpen()
{
    openlog("meteod ",LOG_PID,LOG_DAEMON);
    if(control.debug_level>DEBUG_LEVEL_NORMAL)
	syslog(LOG_NOTICE,"Запуск подсистемы журналирования");
    control.logfile=open(config.log_filename,O_WRONLY|O_CREAT|O_APPEND);
    if(control.logfile==-1)
    {
	//sprintf(msg,"Ошибка открытия журнала (%s): %s",config.log_filename,strerror(errno));
	if(control.debug_level>DEBUG_LEVEL_SILENT) syslog(LOG_ERR,"Ошибка открытия журнала (%s): %s",config.log_filename,strerror(errno));
	if(control.log_fail==LOG_FAIL_EXIT)
	{
	    syslog(LOG_ERR,"Запуск демона не возможен из-за критической ошибки");
	    exit(RET_CODE_LOG_OPEN_ERROR);
	}
    }
    else if(control.debug_level>DEBUG_LEVEL_NORMAL) syslog(LOG_NOTICE,"Журнал (%s) успешн открыт для записи",config.log_filename);
    if(control.debug_level>DEBUG_LEVEL_NORMAL) logWrite("Журнал успешн открыт для записи");
}

void logClose()
{
    if(control.debug_level>DEBUG_LEVEL_NORMAL)
	logWrite("Остановка подсистемы журналирования");
    if(control.logfile!=-1) close(control.logfile);
    if(control.debug_level>DEBUG_LEVEL_NORMAL)
	syslog(LOG_NOTICE,"Остановка подсистемы журналирования");
    closelog();
}

void logWrite(char* msg)
{
    time_t cur_time;
    struct tm* t;
    char buff[BUFF_SIZE];

    cur_time=time(NULL);
    t=localtime(&cur_time);

    if(control.logfile==-1)
    {
	if(control.log_fail==LOG_FAIL_IGNOR) return;
	syslog(LOG_INFO,"%s",msg);
	return;
    }

    snprintf(buff,BUFF_SIZE,"%02d-%02d-%d %02d:%02d:%02d [%d] - %s\n",t->tm_mday,t->tm_mon+1,t->tm_year+1900,t->tm_hour,t->tm_min,t->tm_sec,getpid(),msg);
    write(control.logfile,buff,strlen(buff));
}