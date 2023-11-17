#include "stm32f10x.h"
#include "MPU6050.h"
#include "MyI2C.h"
#include "MPU6050.h"

/**
 * @brief MPU6050芯片初始化
 * @retval 无
 */
void MPU6050H_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_ClockSpeed = 50000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_Init(I2C2, &I2C_InitStructure);

    I2C_Cmd(I2C2, ENABLE);
}

/**
 * @brief MPU6050芯片指定地址写寄存器
 * @param {u8} RegAddress: 指定寄存器地址
 * @param {u8} Data: 指定写内容
 * @retval 无
 */
void MPU6050H_WriteReg(u8 RegAddress, u8 Data){
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050H_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    MPU6050H_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED );

    I2C_SendData(I2C2, RegAddress);
    MPU6050H_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    I2C_SendData(I2C2, Data);
    MPU6050H_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTOP(I2C2, ENABLE);
}

/**
 * @brief MPU6050芯片读取指定地址寄存器
 * @param {u8} RegAddress: 所读寄存器地址
 * @retval {u8} 读出寄存器地址内容
 */
u8 MPU6050H_ReadReg(u8 RegAddress){
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050H_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    MPU6050H_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED );

    I2C_SendData(I2C2, RegAddress);
    MPU6050H_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050H_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
    MPU6050H_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED );

    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);

    MPU6050H_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);

    u8 Data = I2C_ReceiveData(I2C2);

    I2C_AcknowledgeConfig(I2C2, ENABLE);

    return Data;
}


/**
 * @brief MPU6050读取陀螺仪加速器数值
 * @param {int16_t} AG: 二维数组用以存放数据
 * @retval 无
 */
void MPU6050H_GetDate(int16_t AG[2][3]){
    AG[0][0] = (MPU6050H_ReadReg(MPU6050_ACCEL_XOUT_H) << 8) | MPU6050H_ReadReg(MPU6050_ACCEL_XOUT_L);
    AG[0][1] = (MPU6050H_ReadReg(MPU6050_ACCEL_YOUT_H) << 8) | MPU6050H_ReadReg(MPU6050_ACCEL_YOUT_L);
    AG[0][2] = (MPU6050H_ReadReg(MPU6050_ACCEL_ZOUT_H) << 8) | MPU6050H_ReadReg(MPU6050_ACCEL_ZOUT_L);
    AG[1][0] = (MPU6050H_ReadReg(MPU6050_GYRO_XOUT_H) << 8) | MPU6050H_ReadReg(MPU6050_GYRO_XOUT_L);
    AG[1][1] = (MPU6050H_ReadReg(MPU6050_GYRO_YOUT_H) << 8) | MPU6050H_ReadReg(MPU6050_GYRO_YOUT_L);
    AG[1][2] = (MPU6050H_ReadReg(MPU6050_GYRO_ZOUT_H) << 8) | MPU6050H_ReadReg(MPU6050_GYRO_ZOUT_L);
}


void MPU6050H_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT){
    uint32_t Timeout = 10000;
    while(I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS && Timeout-- != 0);
}
