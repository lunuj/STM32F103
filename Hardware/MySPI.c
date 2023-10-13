#include "stm32f10x.h"
#include "MySPI.h"

/**
 * @brief SPI通信初始化
 * @retval 无
 */
void MySPI_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MySPI_SCK | MySPI_SS | MySPI_MOSI;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = MySPI_MISO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

    MySPI_W_SS(1);
    MySPI_W_SCK(0);


}

/**
 * @brief SPI写SS
 * @param {u8} BitValue 修改SS数值0为低电平其他为高电平
 * @retval 无
 */
void MySPI_W_SS(u8 BitValue){
    GPIO_WriteBit(GPIOB, MySPI_SS, (BitAction)BitValue);
}

/**
 * @brief SPI写SCK
 * @param {u8} BitValue 被写入的值
 * @retval 无
 */
void MySPI_W_SCK(u8 BitValue){
    GPIO_WriteBit(GPIOB, MySPI_SCK, (BitAction)BitValue);
}

/**
 * @brief SPI写MOSI
 * @param {u8} BitValue 写入MOSI的值
 * @retval 无
 */
void MySPI_W_MOSI(u8 BitValue){
    GPIO_WriteBit(GPIOB, MySPI_MOSI, (BitAction)BitValue);
}

/**
 * @brief SPI读MISO
 * @retval {u8} MISO的输入值
 */
u8 MySPI_R_MISO(void){
    return GPIO_ReadInputDataBit(GPIOB, MySPI_MISO);
}

/**
 * @brief SPI发送开始状态
 * @retval 无
 */
void MySPI_Start(){
    MySPI_W_SS(0);
}

/**
 * @brief SPI发送结束状态
 * @retval 无
 */
void MySPI_Stop(){
    MySPI_W_SS(1);
}

/**
 * @brief SPI交换一字节数据
 * @param {u8} ByteSwap 交换出的一字节数据
 * @retval {u8} 交换入的一字节数据
 */
u8 MySPI_SwapByte(u8 ByteSwap){
    u8 Data = 0x00;
    for (int i = 0; i < 8; i++)
    {
        // MySPI_W_MOSI(ByteSwap & 0x80);
        // ByteSwap <<= 1;
        // MySPI_W_SCK(1);
        // ByteSwap |= MySPI_R_MISO();
        // MySPI_W_SCK(0);
        MySPI_W_MOSI(ByteSwap & (0x80 >> i));
        MySPI_W_SCK(1);
        Data |= MySPI_R_MISO() << (7 - i);
        MySPI_W_SCK(0);
    }
    return Data;
}