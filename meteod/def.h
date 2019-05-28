// FILE: 	def.h
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#ifndef __DEF_H__
#define __DEF_H__

#define BUFF_SIZE 1024

#define RET_CODE_OK		 0
#define RET_CODE_LOG_OPEN_ERROR	-1
#define RET_CODE_FORK_FAIL	-2

#define DEFAULT_LOG_FILENAME "/var/log/meteod.log"
#define DEFAULT_CONFIG_FILENAME "/etc/meteo.conf"

#define LOG_FAIL_EXIT			0
#define LOG_FAIL_IGNOR			1
#define LOG_FAIL_SYSLOG			2

#define DEBUG_LEVEL_SILENT		0
//#define DEBUG_LEVEL_LOW		1
#define DEBUG_LEVEL_NORMAL		2
//#define DEBUG_LEVEL_			3
#define DEBUG_LEVEL_FULL		4

#endif // __DEF_H__

