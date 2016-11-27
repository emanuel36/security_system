#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "functions.h"
#include "alarm.h"
#include "keyboard_4x3.h"

void init_alarm(){
	init_gpio(SENSOR, INPUT);
	init_gpio(LED_ALARM, OUTPUT);
	init_gpio(BUZZER_ALARM, OUTPUT);
	set_gpio_low(LED_ALARM);
}

void *alarm_on(){
	while(1){
		show_number(8);
		set_gpio_high(BUZZER_ALARM);
		set_gpio_high(LED_ALARM);
		usleep(200000);
		set_gpio_low(BL);
		set_gpio_low(LED_ALARM);
		set_gpio_low(BUZZER_ALARM);
		usleep(200000);
	}
}

void alarm_off(){
	set_gpio_low(LED_ALARM);
	set_gpio_low(BUZZER_ALARM);
}

void task_sensor(pthread_t *alarm, int *alarm_flag){
	if(get_value(SENSOR)){
		pthread_create(alarm, NULL, alarm_on, NULL);
		*alarm_flag = 1;
	}	
}