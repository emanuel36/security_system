#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "alarm.h"
#include "keyboard_4x3.h"
#include "alarm.h"
#include "functions.h"

void main(){
	int  i, senha_digitada = 0, numero, senha = 3601, tentativas = 3, alarm_flag = 0;
	pthread_t alarm;

	init_keyboard();
	init_alarm();

	for(i = 0; i < 4; i++){	
		inicio:
		show_number(tentativas);

		leitura:
		if(!alarm_flag)	task_sensor(&alarm, &alarm_flag);
		numero = read_keyboard();
		if(numero == 10){
			goto leitura;	
		} 
		else if(numero < 0){
			goto erro;
		}else{
			set_gpio_high(BUZZER_K);
			usleep(30000);
			set_gpio_low(BUZZER_K);
			senha_digitada *= 10;
			senha_digitada += numero;
			usleep(500000);				
		}
	}
	if(senha_digitada == senha){
		if(alarm_flag)	pthread_cancel(alarm);
		alarm_off();
		alarm_flag = 0;
		correct_passw_sign();
		count_display();
		tentativas = 3;
		senha_digitada = 0;
		i = 0;
		goto inicio;
	}else{
		erro:
		tentativas--;
		show_number(tentativas);
		wrong_passw_sign();
		if(tentativas == 0){
			pthread_create(&alarm, NULL, alarm_on, NULL);
			alarm_flag = 1;
		}	
		senha_digitada = 0;
		i = 0;
		goto leitura;
	}
}