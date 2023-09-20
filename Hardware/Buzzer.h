#ifndef __BUZZER_H
#define __BUZZER_H

#define BUZZER_PORT GPIO_Pin_5

void Buzzer_Init(void);
void Buzzer_SET(int status);
void Buzzer_Turn(void);

#endif