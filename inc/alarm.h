#include <pthread.h>

#define SENSOR 			72
#define LED_ALARM 		73
#define BUZZER_ALARM	27

void init_alarm();

void *alarm_on();
void alarm_off();
void task_sensor(pthread_t *alarm, int *alarm_flag);