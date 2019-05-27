// FILE: 	main.c
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "def.h"
#include "main.h"
#include "daemon.h"
#include "log.h"

CONFIG config;
CONTROL control;

int main(int argc,char* argv[])
{
    initDefaults();

    logOpen();
    // Запускаем процесс демонизации
    goToDaemon();

    logClose();
    return RET_CODE_OK;
}

void initDefaults()
{
    strcpy(config.log_filename,DEFAULT_LOG_FILENAME);
    control.debug_level=DEBUG_LEVEL_FULL;
    control.log_fail=LOG_FAIL_EXIT;
    control.logfile=-1;
}