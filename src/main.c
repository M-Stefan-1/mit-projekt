#include "stm8s.h"
#include "milis.h"
#include "LCD_I2C.h"
#include "delay.h"
#include <stdio.h>
#include "uart2.h"


#define SENSOR_PORT GPIOC
#define SENSOR_1 GPIO_PIN_5
#define SENSOR_2 GPIO_PIN_6
#define LED_PORT GPIOD
#define LED_PIN GPIO_PIN_4

#define LOW(BAGR) GPIO_WriteLow(BAGR##_PORT, BAGR##_PIN)
#define HIGH(BAGR) GPIO_WriteHigh(BAGR##_PORT, BAGR##_PIN)
#define REVERSE(BAGR) GPIO_WriteReverse(BAGR##_PORT, BAGR##_PIN)

#define READ(BAGR) GPIO_ReadInputPin(BAGR##_PORT, BAGR##_PIN)
#define PUSH(BAGR) (GPIO_ReadInputPin(BAGR##_PORT, BAGR##_PIN) == RESET)


int8_t SMER;

char text1[48];
char text2[48];

int cas1;
int cas2;
float rozdil;
int rychlost;
int brana1;
int brana2;


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(SENSOR_PORT, SENSOR_1, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(SENSOR_PORT, SENSOR_2, GPIO_MODE_IN_FL_NO_IT);
    //enableInterrupts();

    init_milis();
    
    //TIM4_TimeBaseInit(TIM4_PRESCALER_128,250);
    //TIM4_Cmd(ENABLE);
    init_uart2();
}

void main(void)
{   

    setup();

    uint64_t time = 0;
    
    while (1)
    {
        delay_ms(1000);
        REVERSE(LED);
    }
}



/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
