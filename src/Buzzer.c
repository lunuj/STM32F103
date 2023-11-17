/*
 * @Author: lunuj
 * @Date: 2023-09-18 21:48:08
 * @LastEditTime: 2023-09-18 22:11:19
 * @FilePath: \test\Hardware\Buzzer.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#include "stm32f10x.h"
#include "Buzzer.h"

/**
 * @description: 初始化蜂鸣器
 * @return {*}
 */
void Buzzer_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = BUZZER_PORT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOA, BUZZER_PORT, Bit_SET);
}

/**
 * @description: 蜂鸣器状态设置
 * @param {int} status:输入蜂鸣器状态,0为关闭,其他为打开
 * @return {*}
 */
void Buzzer_SET(int status){
    if (status == 0)
    {
        GPIO_WriteBit(GPIOA, BUZZER_PORT, Bit_SET);
    } else{
        GPIO_WriteBit(GPIOA, BUZZER_PORT, Bit_RESET);
    }
}

/**
 * @description: 蜂鸣器状态翻转
 * @return {*}
 */
void Buzzer_Turn(void){
    if (GPIO_ReadOutputDataBit(GPIOA, BUZZER_PORT)==0)
    {
        GPIO_SetBits(GPIOA,BUZZER_PORT);
    }else{
        GPIO_ResetBits(GPIOA,BUZZER_PORT);
    }
}