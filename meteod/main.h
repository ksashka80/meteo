// FILE: 	main.h
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#include <linux/limits.h>

#ifndef __MAIN_H__
#define __MAIN_H__

typedef struct
{
    char log_filename[PATH_MAX];
    int server_port;
    char dbUserName[MYSQL_MAX_USERNAME_LEN];
    char dbPass[MYSQL_MAX_PASS_LEN];
    char dbBaseName[MYSQL_MAX_DATABASE_NAME_LEN];
} CONFIG;

typedef struct
{
    int debug_level;
    int log_fail;
    int logfile;
    int exit_flag;
} CONTROL;

// Прототипы функций
void initDefaults();
void exitDaemon();

#endif // __MAIN_H__

