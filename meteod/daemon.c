// FILE: 	daemon.c
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "def.h"
#include "main.h"
#include "log.h"

extern CONTROL control;
extern CONFIG config;

void goToDaemon()
{
    pid_t pid;
    int x;
    char buff[BUFF_SIZE];

    if(control.debug_level>DEBUG_LEVEL_NORMAL)
	logWrite("Начало функции демонизации goToDaemon()");

    pid=fork();
    if(pid<0)
    {
	snprintf(buff,BUFF_SIZE,"Ошибка функции fork(): %s",strerror(errno));
	logWrite(buff);
	exit(RET_CODE_FORK_FAIL);
    }
    if(pid>0)
    {
	if(control.debug_level>DEBUG_LEVEL_NORMAL)
	    logWrite("Завершение процесса-родителя");
	exit(RET_CODE_OK);
    }

    if(setsid()<0)
    {
	snprintf(buff,BUFF_SIZE,"Ошибка функции setsid(): %s",strerror(errno));
	logWrite(buff);
	exit(EXIT_FAILURE);
    }

    // Настройка диспозиции сигналов..

    //
    if(control.debug_level>DEBUG_LEVEL_NORMAL)
	    logWrite("Повторный вызов функции fork()");
    pid=fork();
    if(pid<0)
    {
	snprintf(buff,BUFF_SIZE,"Ошибка функции fork(): %s",strerror(errno));
	logWrite(buff);
	exit(RET_CODE_FORK_FAIL);
    }
    if(pid>0)
    {
	if(control.debug_level>DEBUG_LEVEL_NORMAL)
	    logWrite("Завершение процесса-родителя");
	exit(RET_CODE_OK);
    }

    umask(0);
    chdir("/");
    for(x=sysconf(_SC_OPEN_MAX);x>=0;x--)
    {
	if(x!=control.logfile) close(x);
    }

    if(control.debug_level>DEBUG_LEVEL_NORMAL)
	    logWrite("Перешли в режим демона");
    return;
}