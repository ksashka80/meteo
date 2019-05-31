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

