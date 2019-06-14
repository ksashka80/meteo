// FILE: 	datapkt.h
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#ifndef __DATAPKT_H__
#define __DATAPKT_H__

typedef struct
{
    int sensorID;
    int sersorVersion;
    float temperature;
    float pressure;
    float humidity;
} DATA;

typedef struct
{
    DATA data;
    unsigned short crc;
} DATAPKT;

#endif // __DATAPKT_H__

