#include <stdio.h>
#include <unistd.h>
#include "functions.h"
#include "alarm.h"

void init_alarm(){
	init_gpio(SENSOR, INPUT);
	init_gpio(LED_ALARM, OUTPUT);
	init_gpio(BUZZER_ALARM, OUTPUT);
}

void alarm_on(){
	while(1){
		set_gpio_high(BUZZER_ALARM);
		set_gpio_high(LED_ALARM);
		usleep(200000);
		set_gpio_low(LED_ALARM);
		set_gpio_low(BUZZER_ALARM);
		usleep(200000);
	}
}

void alarm_off(){
	set_gpio_low(LED_ALARM);
	set_gpio_low(BUZZER_ALARM);
}

void task_sensor(){
	init_alarm();
	while(1){
		if(get_value(SENSOR)){
			alarm_on();
		}
	}
}