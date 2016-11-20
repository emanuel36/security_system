#include <stdio.h>
#include <stdlib.h>
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
	init_gpio(BUZZER, OUTPUT);
	init_gpio(LED_R, OUTPUT);
	init_gpio(LED_G, OUTPUT);
	set_gpio_high(LED_R);
	set_gpio_low(LED_G);
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

	set_gpio_high(BUZZER);
	set_gpio_high(LED_R);
	usleep(200000);
	set_gpio_low(LED_R);
	set_gpio_low(BUZZER);
	usleep(200000);

	set_gpio_high(BUZZER);
	set_gpio_high(LED_R);
	usleep(200000);
	set_gpio_low(LED_R);
	set_gpio_low(BUZZER);
	usleep(200000);

	set_gpio_high(BUZZER);
	set_gpio_high(LED_R);
	usleep(200000);
	set_gpio_low(BUZZER);
}

void correct_passw_sign(){
	set_gpio_low(LED_R);

	set_gpio_high(LED_G);
	set_gpio_high(BUZZER);
	usleep(700000);
	set_gpio_low(BUZZER);
}

void task_keyboard(){
	int  i, senha_digitada = 0, numero, senha = 360601;
	init_keyboard();


	for(i = 0; i < 6; i++){	
		leitura:
		numero = read_keyboard();
		if(numero == 10){
			goto leitura;	
		} 
		else if(numero < 0){
			printf("Erro!\n");
			wrong_passw_sign();
			exit(1);
		}else{
			set_gpio_high(BUZZER);
			usleep(30000);
			set_gpio_low(BUZZER);
			senha_digitada *= 10;
			senha_digitada += numero;
			usleep(500000);				
		}
	}
	if(senha_digitada == senha){
		correct_passw_sign();
	}else{
		wrong_passw_sign();
		senha_digitada = 0;
		i = 0;
		goto leitura;
	}	
}