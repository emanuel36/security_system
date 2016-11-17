#include <stdio.h>

void init_gpio(unsigned int , unsigned int);
void set_gpio_high(unsigned int );
void set_gpio_low(unsigned int );
int get_value(unsigned int);
void blink(unsigned unt);

#define INPUT  		0
#define OUTPUT 		1
#define LOW    		0
#define HIGH   		1