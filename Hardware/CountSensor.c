/*
 * @Author: lunuj
 * @Date: 2023-09-19 14:18:12
 * @LastEditTime: 2023-09-19 14:51:00
 * @FilePath: \test\Hardware\CountSensor.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#include "stm32f10x.h"
#include "CountSensor.h"
u16 CountSensor_Count = 0;
void CountSensor_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = COUNTESENSOR_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);

    EXTI_InitTypeDef EXTI_InitSturcture;
    EXTI_InitSturcture.EXTI_Line = EXTI_Line3;
    EXTI_InitSturcture.EXTI_LineCmd = ENABLE;
    EXTI_InitSturcture.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitSturcture.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitSturcture);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitSttructue;
    NVIC_InitSttructue.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitSttructue.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitSttructue.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitSttructue.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitSttructue);
}

void EXTI3_IRQHandler(void){
    CountSensor_Count++;
    EXTI_ClearITPendingBit(EXTI_Line3);
}

u16 CountSensor_Get(void){
    return CountSensor_Count;
}