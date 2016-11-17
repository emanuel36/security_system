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
	init_gpio(BUZZER, OUTPUT);
	init_gpio(LED_R, OUTPUT);
	init_gpio(LED_G, OUTPUT);
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

int main(){
	int senha_digitada = 0, contador = 0, numero, senha = 360601;
	init_keyboard();


	while(contador < 6){	
		leitura:
		numero = read_keyboard();
		if(numero == 10){
			goto leitura;	
		} 
		else if(numero < 0){
			printf("Erro!\n");
			break;	
		}else{
			set_gpio_high(BUZZER);
			usleep(3000);
			set_gpio_low(BUZZER);
			senha_digitada *= 10;
			senha_digitada += numero;
			usleep(500000);
		} 
		contador++;
	}
	if(senha_digitada == senha){
		set_gpio_low(LED_R);
		set_gpio_high(LED_G);
	}else{
		blink(LED_R);
		blink(BUZZER);
		blink(LED_R);
		blink(BUZZER);
		blink(LED_R);
		blink(BUZZER);
		senha_digitada = 0;
		contador = 0;
		goto leitura;
	}	
}