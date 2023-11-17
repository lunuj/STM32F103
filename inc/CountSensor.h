#ifndef __COUNTSENSOR_H
#define __COUNTSENSOR_H

#define COUNTESENSOR_PIN GPIO_Pin_3
void CountSensor_Init(void);
void EXTI3_IRQHandler(void);
u16 CountSensor_Get(void);
#endif