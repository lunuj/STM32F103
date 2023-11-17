/*
 * @Author: lunuj
 * @Date: 2023-09-19 23:33:16
 * @LastEditTime: 2023-09-20 17:03:06
 * @FilePath: \test\Hardware\PWM.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#include "stm32f10x.h"
#include "PWM.h"


void PWM_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM2);
    // TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted,0x00);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100 -1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_OCInitTypeDef TIM_OC1InitStructure;
    TIM_OCStructInit(&TIM_OC1InitStructure);
    TIM_OC1InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC1InitStructure.TIM_Pulse = 0;
    TIM_OC1Init(TIM2, &TIM_OC1InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetComparel(u16 Compare){
    TIM_SetCompare1(TIM2,Compare);
}

void PWM_SetPrescaler(u16 Prescaler){
    TIM_PrescalerConfig(TIM2, Prescaler, TIM_PSCReloadMode_Immediate);
}