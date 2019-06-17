// FILE: 	datapkt.h
// PROJECT:	meteo
// SUBPROJECT:	meteod
// AUTHOR:	Alexandr Kargapolov

#ifndef __DATAPKT_H__
#define __DATAPKT_H__

typedef struct
{
    int sensorID;
    int sersorType;
    float temperature;
    float pressure;
    float humidity;
} DATA_BME280;

typedef struct
{
    int pktVersion;
    unsigned short crc;
    DATA_BME280 data;
} PKT_BME280;


#endif // __DATAPKT_H__

