/*
 * @Author: lunuj
 * @Date: 2023-09-14 16:18:48
 * @LastEditTime: 2023-10-03 16:50:31
 * @FilePath: \test\src\main.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */


#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"
#include "Serial.h"


int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);

	OLED_Init();

	OLED_ShowString(1,1,"Start:");

}