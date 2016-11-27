#include <stdio.h>
#include <unistd.h>
#include "functions.h"
#include "keyboard_4x3.h"

void init_keyboard(){
	init_gpio(LINHA_1, INPUT);
	init_gpio(LINHA_2, INPUT);
	init_gpio(LINHA_3, INPUT);
	init_gpio(LINHA_4, INPUT);
	init_gpio(COLUNA_1, OUTPUT);
	init_gpio(COLUNA_2, OUTPUT);
	init_gpio(COLUNA_3, OUTPUT);
	init_gpio(BUZZER_K, OUTPUT);
	init_gpio(LED_R, OUTPUT);
	init_gpio(LED_G, OUTPUT);
	init_gpio(BIT_0, OUTPUT);
	init_gpio(BIT_1, OUTPUT);
	init_gpio(BIT_2, OUTPUT);
	init_gpio(BIT_3, OUTPUT);
	init_gpio(BL, OUTPUT);
	set_gpio_high(LED_R);
}

int read_keyboard(){
	int numero = 10;

	set_gpio_high(COLUNA_1);

	if(get_value(LINHA_1)){
		numero = 1;
	}

	if(get_value(LINHA_2)){
		if(numero != 10){
			return -1;
		}
		numero = 4;
	}

	if(get_value(LINHA_3)){
		if(numero != 10){
			return -1;
		}
		numero = 7;
	}

	if(get_value(LINHA_4)){
		return -1;
	}

	set_gpio_low(COLUNA_1);
	set_gpio_high(COLUNA_2);

	if(get_value(LINHA_1)){
		if(numero != 10){
			return -1;
		}
		numero = 2;
	}

	if(get_value(LINHA_2)){
		if(numero != 10){
			return -1;
		}
		numero = 5;
	}

	if(get_value(LINHA_3)){
		if(numero != 10){
			return -1;
		}
		numero = 8;
	}

	if(get_value(LINHA_4)){
		if(numero != 10){
			return -1;
		}
		numero = 0;
	}

	set_gpio_low(COLUNA_2);
	set_gpio_high(COLUNA_3);

	if(get_value(LINHA_1)){
		if(numero != 10){
			return -1;
		}
		numero = 3;
	}

	if(get_value(LINHA_2)){
		if(numero != 10){
			return -1;
		}
		numero = 6;
	}

	if(get_value(LINHA_3)){
		if(numero != 10){
			return -1;
		}
		numero = 9;
	}

	if(get_value(LINHA_4)){
		return -1;
	}
	
	set_gpio_low(COLUNA_3);

	return numero;
}

void wrong_passw_sign(){
	set_gpio_low(LED_R);
	usleep(100000);

	set_gpio_high(BUZZER_K);
	set_gpio_high(LED_R);
	usleep(200000);
	set_gpio_low(LED_R);
	set_gpio_low(BUZZER_K);
	usleep(200000);

	set_gpio_high(BUZZER_K);
	set_gpio_high(LED_R);
	usleep(200000);
	set_gpio_low(LED_R);
	set_gpio_low(BUZZER_K);
	usleep(200000);

	set_gpio_high(BUZZER_K);
	set_gpio_high(LED_R);
	usleep(200000);
	set_gpio_low(BUZZER_K);
}

void correct_passw_sign(){
	set_gpio_low(LED_R);
	set_gpio_high(LED_G);
	set_gpio_high(BUZZER_K);
	usleep(700000);
	set_gpio_low(BUZZER_K);
}

void count_display(){
	int numero = 9;
	set_gpio_high(BL);
	while(numero >= 0){
		if(numero & 0x1)	set_gpio_high(BIT_0);
		else				set_gpio_low(BIT_0);

		if(numero & 0x2)	set_gpio_high(BIT_1);
		else				set_gpio_low(BIT_1);

		if(numero & 0x4)	set_gpio_high(BIT_2);
		else				set_gpio_low(BIT_2);

		if(numero & 0x8)	set_gpio_high(BIT_3);
		else				set_gpio_low(BIT_3);

		numero--;
		sleep(1);

		set_gpio_high(BUZZER_K);
		usleep(15000);
		set_gpio_low(BUZZER_K);
	}
	set_gpio_high(BUZZER_K);
	usleep(500000);
	set_gpio_low(BUZZER_K);
	set_gpio_low(BL);
	set_gpio_high(LED_R);
	set_gpio_low(LED_G);
}

void show_number(int number){
	set_gpio_high(BL);
	if(number & 0x1)	set_gpio_high(BIT_0);
	else				set_gpio_low(BIT_0);

	if(number & 0x2)	set_gpio_high(BIT_1);
	else				set_gpio_low(BIT_1);

	if(number & 0x4)	set_gpio_high(BIT_2);
	else				set_gpio_low(BIT_2);

	if(number & 0x8)	set_gpio_high(BIT_3);
	else				set_gpio_low(BIT_3);
}