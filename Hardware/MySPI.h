#ifndef __MYSPI_H__
#define __MYSPI_H__

#define MySPI_SCK GPIO_Pin_0
#define MySPI_SS GPIO_Pin_1
#define MySPI_MISO GPIO_Pin_10
#define MySPI_MOSI GPIO_Pin_11


void MySPI_Init(void);

void MySPI_W_SS(u8 BitValue);

void MySPI_W_SCK(u8 BitValue);

u8 MySPI_R_MISO(void);

void MySPI_Start();

void MySPI_Stop();

u8 MySPI_SwapByte(u8 ByteSwap);

#endif // __MYSPI_H__


