#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

void init_gpio(unsigned int gpio, unsigned int direction){
	FILE* f = NULL;
	f = fopen("/sys/class/gpio/export", "w");
	fprintf(f, "%d", gpio);
	fclose(f);
	f = NULL;

	//DIRECTION
	char path[50];
	sprintf(path, "/sys/class/gpio/gpio%d/direction", gpio);
	f = fopen(path, "w");
	
	if(direction == OUTPUT){
		fprintf(f, "out");
		fclose(f);	
	}
	else{
		fprintf(f, "in");
		fclose(f);	
	}
}

///INPUT
int get_value(unsigned int gpio){
	FILE* f = NULL;
	char leitura, path[50];
	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	f = fopen(path, "r");
	leitura = fgetc(f);
	fclose(f);
	if(strncmp(&leitura, "1", 1) == 0){
		return 1;
	}else{
		return 0;
	}
}

//OUTPUT
void set_gpio_high(unsigned int gpio){
	FILE* f = NULL;
	char path[50];

	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	f = fopen(path, "w");
	fprintf(f, "1");
	fclose(f);
}

void set_gpio_low(unsigned int gpio){
	FILE* f = NULL;
	char path[50];

	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	f = fopen(path, "w");
	fprintf(f, "0");
	fclose(f);
}

void blink(unsigned int gpio){
  set_gpio_high(gpio);
  usleep(100000);
  set_gpio_low(gpio);
  usleep(100000);
}
