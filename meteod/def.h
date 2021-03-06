// FILE: 	def.h
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#ifndef __DEF_H__
#define __DEF_H__

#define BUFF_SIZE 1024
#define MAX_STRING_LENGTH 1024
#define MYSQL_MAX_USERNAME_LEN 33
#define MYSQL_MAX_PASS_LEN 33
#define MYSQL_MAX_DATABASE_NAME_LEN 65
#define IP_STRING_LENGTH 16
#define PKT_QUEUE_LENGTH 10

#define RET_CODE_OK		 0
#define RET_CODE_LOG_OPEN_ERROR	-1
#define RET_CODE_FORK_FAIL	-2

#define DEFAULT_LOG_FILENAME "/var/log/meteod.log"
#define DEFAULT_CONFIG_FILENAME "/etc/meteo.conf"
#define DEFAULT_SERVER_PORT 28028
#define DEFAULT_DB_USER_NAME "meteo"
#define DEFAULT_DB_PASSWORD "meteopass"
#define DEFAULT_DB_DATABASE_NAME "meteo"

#define LOG_FAIL_EXIT			0
#define LOG_FAIL_IGNOR			1
#define LOG_FAIL_SYSLOG			2

#define DEBUG_LEVEL_SILENT		0
//#define DEBUG_LEVEL_LOW		1
#define DEBUG_LEVEL_NORMAL		2
//#define DEBUG_LEVEL_			3
#define DEBUG_LEVEL_FULL		4

#endif // __DEF_H__

