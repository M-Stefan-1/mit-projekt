#include "stm8s.h"
#include "milis.h"
#include "LCD_I2C.h"
#include "delay.h"
#include <stdio.h>

// #include "uart1.h"


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

uint32_t time = 0;
int cas1;
int cas2;
float rozdil;
int rychlost;
int brana1;
int brana2;


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(SENSOR_PORT, SENSOR_1, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(SENSOR_PORT, SENSOR_2, GPIO_MODE_IN_FL_NO_IT);
    //enableInterrupts();

    LCD_I2C_Init(0x27, 16, 2);
    LCD_I2C_SetCursor(0,0);
    init_milis();
    
    //TIM4_TimeBaseInit(TIM4_PRESCALER_128,250);
    //TIM4_Cmd(ENABLE);
    // init_uart1();
}



void obrazovka(int8_t SMER)
{
    
    LCD_I2C_Clear();
    

    if (SMER == 1)
    {
        LCD_I2C_SetCursor(0,0);
        LCD_I2C_Print("Smer: Dovnitr" );
        LCD_I2C_SetCursor(0,1);
        sprintf(text2, "Rych: %2d.%03d m/s",rychlost/1000, rychlost%1000);
        LCD_I2C_Print(text2);
        
    }
    else if (SMER == 2)
    {
        LCD_I2C_SetCursor(0,0);
        LCD_I2C_Print("Smer: Ven" );
        LCD_I2C_SetCursor(0,1);
        sprintf(text2, "Rych: %2d.%03d m/s",rychlost/1000, rychlost%1000);
        LCD_I2C_Print(text2);
        
    }
    else 
    {
        LCD_I2C_SetCursor(0,0);
        LCD_I2C_Print("Smer: " );
        LCD_I2C_SetCursor(0,1);
        LCD_I2C_Print("Rychlost: " );
    }
    
}

int main(void)
{   

    setup();
    obrazovka(0);
    
    
    while (1)
    {

        
        
        if(GPIO_ReadInputPin(SENSOR_PORT,SENSOR_1)!=RESET)
        {
            
            cas1 = milis();
            brana1 = 1;
        
        }
       
        else if(GPIO_ReadInputPin(SENSOR_PORT,SENSOR_2)!=RESET)
        {   
            
            cas2 = milis();
            brana2 = 1;
        } 
        
        if(cas1 < cas2 && brana1 == 1 && brana2 == 1)
        {   
            rozdil = (cas2 - cas1);
            rychlost = 200000 / rozdil;
            brana1 = 0;
            brana2 = 0;
            cas1 = 0;
            cas2 = 0;
            obrazovka(2);
            delay_ms(500);
        }
        
        else if(cas1 > cas2 && brana1 == 1 && brana2 == 1)
        {
            rozdil = (cas1 - cas2);
            rychlost = 200000 / rozdil;
            brana1 = 0;
            brana2 = 0;
            cas1 = 0;
            cas2 = 0;  
            obrazovka(1);
            delay_ms(500);
        }

        
        
        
    }
}



/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
