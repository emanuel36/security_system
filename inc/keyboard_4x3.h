#include <stdio.h>

#define LINHA_1		44
#define LINHA_2		26	
#define LINHA_3		46
#define LINHA_4		65
#define COLUNA_1	45
#define COLUNA_2	23
#define COLUNA_3	47
#define BUZZER		27
#define LED_R		69
#define LED_G		68

int read_keyboard();
void init_keyboard();
void wrong_passw_sign();
void correct_passw_sign();
void task_keyboard();