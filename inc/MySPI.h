#ifndef __MYSPI_H__
#define __MYSPI_H__

#define MySPI_CLK RCC_APB2Periph_GPIOA

#define MySPI_GPIO GPIOA

#define MySPI_SS GPIO_Pin_4
#define MySPI_SCK GPIO_Pin_5
#define MySPI_MISO GPIO_Pin_6
#define MySPI_MOSI GPIO_Pin_7

//软件实现SPI
void MySPI_Init(void);
void MySPI_W_SS(u8 BitValue);
void MySPI_W_SCK(u8 BitValue);
u8 MySPI_R_MISO(void);
void MySPI_Start();
void MySPI_Stop();
u8 MySPI_SwapByte(u8 ByteSwap);

//硬件实现SPI
void MySPIH_Init(void);
void MySPIH_W_SS(u8 BitValue);
void MySPIH_Start();
void MySPIH_Stop();
u8 MySPIH_SwapByte(u8 ByteSwap);

#endif // __MYSPI_H__


