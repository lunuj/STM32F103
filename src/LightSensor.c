/*
 * @Author: lunuj
 * @Date: 2023-09-18 22:00:11
 * @LastEditTime: 2023-09-18 22:10:24
 * @FilePath: \test\Hardware\LightSensor.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#include "stm32f10x.h"
#include "LightSensor.h"

/**
 * @description: 光敏电阻初始化
 * @return {*}
 */
void LightSensor_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = LIGHTSENSOR_PORT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @description: 获取光敏电阻当前状态
 * @return {*}
 */
u8 LightSensor_Get(void){
    return GPIO_ReadInputDataBit(GPIOA, LIGHTSENSOR_PORT);
}