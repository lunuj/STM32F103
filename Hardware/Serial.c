/*
 * @Author: lunuj
 * @Date: 2023-09-30 13:24:05
 * @LastEditTime: 2023-10-03 19:05:41
 * @FilePath: \test\Hardware\Serial.c
 * @Description: 串口通信
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#include "stm32f10x.h"
#include "Serial.h"
#include <stdio.h>
#include <stdarg.h>

u16 RxFlag = 0;

u8 TxCach[4];
u8 RxCach[400];
/**
 * @brief 串口初始化
 * @return {*}
 */
void Serial_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1, ENABLE);

}

/**
 * @brief 向串口发送一个字节数据
 * @param {u8} Byte
 * @retval None
 */
void Serial_SendByte(u8 Byte){
    USART_SendData(USART1, Byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/**
 * @brief 向串口发送一组数组
 * @param {u8} *Arrary: 数组地址
 * @param {u16} Length: 数组长度
 * @retval None
 */
void Serial_SendArrary(u8 *Arrary, u16 Length){
    for (int i = 0; i < Length; i++)
    {
        Serial_SendByte(Arrary[i]);
    }
}

void Serial_SendString(char *String){
    for (int i = 0;String[i]!='\0'; i++)
    {
        Serial_SendByte(String[i]);
    }
    
}

void Serial_SendNum(int Num){
    int thumb = Num/10;
    if (thumb!=0)
    {
        Serial_SendNum(thumb);
    }
    Serial_SendByte(Num%10+'0');
}


int fputc(int ch, FILE *f){
    Serial_SendByte(ch);
    return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

void Serial_SendPack(void){
    Serial_SendByte(0xFF);
    Serial_SendArrary(TxCach, 4);
    Serial_SendByte(0xFE);
}

void Serial_SetPack(u8 tx[4]){
    for (int i = 0; i < 4; i++)
    {
        TxCach[i] = tx[i];
    }
}

void USART1_IRQHandler(void){
    static u8 RxState = 0;
    static u8 pRxPack = 0;
    if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET){
        u8 RxData = USART_ReceiveData(USART1);
        switch (RxState)
        {
        case 0:
            if (RxData == 0xFF)
            {
                RxState = 1;
            }
            if (RxData == '@')
            {
                RxState = 11;
            }
            break;

            
        case 1:
            RxCach[pRxPack++] = RxData;
            if (pRxPack >= 4)
            {
                RxState = 2;
                pRxPack = 0;
            }
            break;
        case 2:
            if (RxData == 0xFE)
            {
                RxState = 0;
                RxFlag = 1;
            }
            break;

            
        case 11:
            if (RxData == '\r')
            {
                RxState = 12;
            } else {
                RxCach[pRxPack++] = RxData;
            }
        case 12:
            if (RxData == '\n')
            {
                RxState = 0;
                RxCach[pRxPack++] = '\0';
                pRxPack = 0;
                RxFlag = 1;
            }
            
        default:
            break;
        }
    }
}

u8 Serial_GetRxFlag(void){
    if (RxFlag == 1)
    {
        RxFlag = 0;
        return 1;
    }
    return 0;
}

u8* Serial_GetRxCach(void){
    return RxCach;
}