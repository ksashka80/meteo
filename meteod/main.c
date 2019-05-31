// FILE: 	main.c
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

#include "def.h"
#include "main.h"
#include "daemon.h"
#include "log.h"
#include "signals.h"

CONFIG config;
CONTROL control;

int main(int argc,char* argv[])
{
    initDefaults();

    logOpen();
    // Запускаем процесс демонизации
    goToDaemon();

    while(!control.exit_flag)
    {
	sleep(1000);
    }

    logWrite("Завершение работы демона");
    if(control.debug_level>DEBUG_LEVEL_SILENT) syslog(LOG_NOTICE,"Завершение работы демона");
    logClose();
    return RET_CODE_OK;
}

void initDefaults()
{
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