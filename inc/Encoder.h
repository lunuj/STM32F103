/*
 * @Author: lunuj
 * @Date: 2023-09-19 14:54:36
 * @LastEditTime: 2023-09-21 17:40:06
 * @FilePath: \test\Hardware\Encoder.h
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#ifndef __ENCODER_H
#define __ENCODER_H

#define ENCODER_PIN (GPIO_Pin_0 | GPIO_Pin_1)
void Encode_Init(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
int16_t Encoder_GET(void);
void Encoder_Speed_Init(void);
int16_t Encoder_GETSpeed(void);
#endif