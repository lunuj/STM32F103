/*
 * @Author: lunuj
 * @Date: 2023-09-18 15:46:40
 * @LastEditTime: 2023-09-18 21:40:55
 * @FilePath: \test\Hardware\LED.c
 * @Description: 按键控制led灯亮灭模块,其中led采用低电平触发,key采用高电平触发
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */

#include "stm32f10x.h"
#include "LED.h"

/**
 * @description: led模块的初始化函数
 * @return {*}
 */
void LED_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_0 | LED_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOA, LED_0|LED_1, Bit_SET);
}

/**
 * @description: 指定led端口,设置端口状态
 * @param {uint16_t} LED:此处输入led所在的端口位置
 * @param {int} status:此处输入改变led的状态,0为关闭,其他数值为打开
 * @return {*}
 */
void LED_SET(uint16_t LED, int status){
    if (status == 0)
    {
        GPIO_WriteBit(GPIOA, LED, Bit_SET);
    } else{
        GPIO_WriteBit(GPIOA, LED, Bit_RESET);
    }
}

/**
 * @description: 指定led端口使其状态反转
 * @param {u16} LED:此处输入led端口位置
 * @return {*}
 */
void LED_Turn(u16 LED){
    if (GPIO_ReadOutputDataBit(GPIOA, LED)==0)
    {
        GPIO_SetBits(GPIOA,LED);
    }else{
        GPIO_ResetBits(GPIOA,LED);
    }
}