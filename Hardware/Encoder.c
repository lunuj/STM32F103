/*
 * @Author: lunuj
 * @Date: 2023-09-19 14:54:27
 * @LastEditTime: 2023-09-21 17:59:24
 * @FilePath: \test\Hardware\Encoder.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#include "stm32f10x.h"
#include "Encoder.h"
int16_t Encoder_Count = 0;
/**
 * @description: 编码器计数初始化
 * @return {*}
 */
void Encode_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = ENCODER_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);

    EXTI_InitTypeDef EXTI_InitSturcture;
    EXTI_InitSturcture.EXTI_Line = EXTI_Line4 | EXTI_Line5;
    EXTI_InitSturcture.EXTI_LineCmd = ENABLE;
    EXTI_InitSturcture.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitSturcture.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitSturcture);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitSttructue;
    NVIC_InitSttructue.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_InitSttructue.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitSttructue.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitSttructue.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitSttructue);
    NVIC_InitSttructue.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitSttructue.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitSttructue.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitSttructue.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitSttructue);
}
/**
 * @description: 外部中断计数正转
 * @return {*}
 */
void EXTI4_IRQHandler(void){
    if (EXTI_GetITStatus(EXTI_Line4) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
        {
            Encoder_Count=-1;
        }

    }
    EXTI_ClearITPendingBit(EXTI_Line4);

}
/**
 * @description: 外部中断计数反转
 * @return {*}
 */
void EXTI9_5_IRQHandler(void){
    if (EXTI_GetITStatus(EXTI_Line5) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)
        {
            Encoder_Count=1;
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line5);
}

int16_t Encoder_GET(void){
    int16_t temp = Encoder_Count;
    Encoder_Count = 0;
    return temp;
}

/**
 * @description: 编码器测速初始化
 * @return {*}
 */
void Encoder_Speed_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = ENCODER_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 -1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_ICInitTypeDef TIM_ICInitTypeDefStructure;
    TIM_ICStructInit(&TIM_ICInitTypeDefStructure);
    TIM_ICInitTypeDefStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitTypeDefStructure.TIM_ICFilter = 0xf;
    TIM_ICInit(TIM2, &TIM_ICInitTypeDefStructure);

    TIM_ICInitTypeDefStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitTypeDefStructure.TIM_ICFilter = 0xf;
    TIM_ICInit(TIM2, &TIM_ICInitTypeDefStructure);

    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_Cmd(TIM2, ENABLE);
}
/**
 * @description: 获取当前速度值
 * @return {*}
 */
int16_t Encoder_GETSpeed(void){
    int16_t temp = TIM_GetCounter(TIM2);
    TIM_SetCounter(TIM2, 0);
    return temp;
}