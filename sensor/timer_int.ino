#include "timer_int.h"

os_timer_t ledTimer;
os_timer_t measureTimer;
os_timer_t connectionTimer;
bool wifi_led=HIGH;
bool wifi_status=false;
bool time_to_measurement=false;
extern bool connection_timeoute;

void wifi_led_timerCallback(void *pArg)
{
	if(!wifi_status)
	{
		wifi_led=!wifi_led;
	}
	else wifi_led=LOW;
	digitalWrite(ONBOARD_LED,wifi_led);
}

void measure_timerCallback(void *pArg)
{
	time_to_measurement=true;
}

void connection_timerCallback(void *pArg)
{
	connection_timeoute=true;
	os_timer_disarm(&ledTimer);
	os_timer_arm(&ledTimer,WIFI_LED_PERIOD_AP,true);
}

void timers_init(void)
{
	pinMode(ONBOARD_LED, OUTPUT);
	os_timer_setfn(&ledTimer,wifi_led_timerCallback,NULL);
	os_timer_setfn(&measureTimer,measure_timerCallback,NULL);
	os_timer_setfn(&connectionTimer,connection_timerCallback,NULL);
	os_timer_arm(&ledTimer,WIFI_LED_PERIOD_STA,true);
	os_timer_arm(&measureTimer,MEASSUREMENT_INTERVAL,true);
	os_timer_arm(&connectionTimer,WIFI_CONNECTION_TIMEOUT,true);
}
