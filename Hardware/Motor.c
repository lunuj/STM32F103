#include "stm32f10x.h"
#include "PWM.h"


void Motor_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    PWM_Init();
}

void Motor_SetSpeed(int8_t speed){
    if (speed >= 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
        GPIO_ResetBits(GPIOA, GPIO_Pin_7);
        PWM_SetComparel(speed);
    } else{
        GPIO_SetBits(GPIOA, GPIO_Pin_7);
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        PWM_SetComparel(-speed);
    }
    
}