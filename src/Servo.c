/*
 * @Author: lunuj
 * @Date: 2023-09-20 00:25:20
 * @LastEditTime: 2023-09-20 00:28:20
 * @FilePath: \test\Hardware\Servo.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#include "stm32f10x.h"
#include "PWM.h"

void Servo_Init(void){
    PWM_Init();
}

void Servo_SerAngle(float Angle){
    PWM_SetComparel(Angle / 180 * 2000 + 500);
}