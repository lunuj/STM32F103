#ifndef __MYI2C_H
#define __MYI2C_H

#define I2C_PORT GPIOB
#define I2C_SCL GPIO_Pin_0 //定义I2C协议scl
#define I2C_SDA GPIO_Pin_1

void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_End(void);
void MyI2C_SendByte(u8 Byte);
u8 MyI2C_ReceiveByte(void);
void MyI2C_SendAck(u8 AckBit);
u8 MyI2C_ReceivAck(void);

#endif


