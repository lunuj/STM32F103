/*
 * @Author: lunuj
 * @Date: 2023-09-14 16:18:48
 * @LastEditTime: 2023-11-17 15:28:02
 * @FilePath: \test\src\main.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */


#include "main.h"

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
	while (1)
	{
		Delay_ms(250);
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13));
	}
	

}