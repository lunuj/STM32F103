//
// Created by lunuj on 2023/11/17.
//

#ifndef __SERIAL_H
#define __SERIAL_H

#include "main.h"
//#include "syscall.h"
#include <stdio.h>
#include <stdarg.h>

void Serial_Init(void);
void Serial_SendByte(u8 Byte);
void Serial_SendArrary(u8 *Arrary, u16 Length);
void Serial_SendString(char *String);
void Serial_SendNum(int Num);
void Serial_Printf(char *format, ...);
void Serial_SendPack(void);
void Serial_SetPack(u8 tx[4]);
u8 Serial_GetRxFlag(void);
u8* Serial_GetRxCach(void);

#endif
