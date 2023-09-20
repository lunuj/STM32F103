/*
 * @Author: lunuj
 * @Date: 2023-09-19 14:54:27
 * @LastEditTime: 2023-09-19 16:00:35
 * @FilePath: \test\Hardware\Encoder.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#include "stm32f10x.h"
#include "Encoder.h"
int16_t Encoder_Count = 0;

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