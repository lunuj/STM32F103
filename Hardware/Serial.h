#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>
#include <stdarg.h>
void Serial_Init(void);
void Serial_SendByte(u8 Byte);
void Serial_SendArrary(u8 *Arrary, u16 Length);
void Serial_SendString(char *String);
void Serial_SendNum(int Num);
void Serial_Printf(char *format, ...);

u8 Serial_GetRxFlag(void);
u8 Serial_GetRxData(void);
#endif
