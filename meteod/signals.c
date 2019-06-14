// FILE: 	signals.c
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "def.h"
#include "main.h"
#include "signals.h"
#include "log.h"

extern CONTROL control;

void signalHandlersConfigFail();
void handlerSIGUSR1(int sig);
void handlerSIGUSR2(int sig);
void handlerSIGHUP(int sig);
void handlerSIGCHLD(int sig);

void signalHandlersConfig()
{
    struct sigaction act;
    sigset_t sigset;

    memset(&act,0,sizeof(act));
    act.sa_handler=handlerSIGUSR1;

    if((sigemptyset(&sigset))==-1) signalHandlersConfigFail();
    if((sigaddset(&sigset,SIGUSR1))==-1) signalHandlersConfigFail();
    act.sa_mask=sigset;
    act.sa_handler=handlerSIGUSR1;
    sigaction(SIGUSR1,&act,0);

    if((sigemptyset(&sigset))==-1) signalHandlersConfigFail();
    if((sigaddset(&sigset,SIGUSR2))==-1) signalHandlersConfigFail();
    act.sa_mask=sigset;
    act.sa_handler=handlerSIGUSR2;
    sigaction(SIGUSR2,&act,0);

    if((sigemptyset(&sigset))==-1) signalHandlersConfigFail();
    if((sigaddset(&sigset,SIGHUP))==-1) signalHandlersConfigFail();
    act.sa_mask=sigset;
    act.sa_handler=handlerSIGHUP;
    sigaction(SIGHUP,&act,0);

    if((sigemptyset(&sigset))==-1) signalHandlersConfigFail();
    if((sigaddset(&sigset,SIGCHLD))==-1) signalHandlersConfigFail();
    act.sa_mask=sigset;
    act.sa_handler=handlerSIGCHLD;
    sigaction(SIGCHLD,&act,0);



    if(control.debug_level>DEBUG_LEVEL_NORMAL) logWrite("Обработчик сигналов установлен");
}

void handlerSIGUSR1(int sig)
{
    logWrite("Получен сигнал SIGUSR1");
    control.exit_flag=1;
}

void handlerSIGUSR2(int sig)
{
    logWrite("Получен сигнал SIGUSR2");
}

void handlerSIGHUP(int sig)
{
    logWrite("Получен сигнал SIGHUP");
}

void handlerSIGCHLD(int sig)
{
    waitpid(-1,NULL,WNOHANG);
}

void signalHandlersConfigFail()
{
    char buff[BUFF_SIZE];

    snprintf(buff,BUFF_SIZE,"Критическая ошибка. Не возможно настроить обработчик сигналов: %s",strerror(errno));
    logWrite(buff);
    exitDaemon();

}
