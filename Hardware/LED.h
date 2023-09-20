/*
 * @Author: lunuj
 * @Date: 2023-09-18 15:46:45
 * @LastEditTime: 2023-09-18 17:00:35
 * @FilePath: \test\Hardware\LED.h
 * @Description: led头文件
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */

#ifndef __LED_H
#define __LED_H

#define LED_0 GPIO_Pin_0
#define LED_1 GPIO_Pin_1

void LED_Init(void);
void LED_SET(uint16_t LED, int status);
void LED_Turn(u16 LED);

#endif