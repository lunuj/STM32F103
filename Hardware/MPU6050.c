#include "stm32f10x.h"
#include "MPU6050.h"
#include "MyI2C.h"

/**
 * @brief MPU6050芯片初始化
 * @retval 无
 */
void MPU6050_Init(void){
    MyI2C_Init();
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}
/**
 * @brief MPU6050芯片指定地址写寄存器
 * @param {u8} RegAddress: 指定寄存器地址
 * @param {u8} Data: 指定写内容
 * @retval 无
 */
void MPU6050_WriteReg(u8 RegAddress, u8 Data){
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceivAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceivAck();
    MyI2C_SendByte(Data);
    MyI2C_ReceivAck();
    MyI2C_End();
}

/**
 * @brief MPU6050芯片读取指定地址寄存器
 * @param {u8} RegAddress: 所读寄存器地址
 * @retval {u8} 读出寄存器地址内容
 */
u8 MPU6050_ReadReg(u8 RegAddress){
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceivAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceivAck();

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
    MyI2C_ReceivAck();
    u8 Data = MyI2C_ReceiveByte();
    MyI2C_SendAck(1);
    MyI2C_End();

    return Data;
}

/**
 * @brief MPU6050读取陀螺仪加速器数值
 * @param {int16_t} AG: 二维数组用以存放数据
 * @retval 无
 */
void MPU6050_GetDate(int16_t AG[2][3]){
    AG[0][0] = (MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H) << 8) | MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    AG[0][1] = (MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H) << 8) | MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    AG[0][2] = (MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H) << 8) | MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    AG[1][0] = (MPU6050_ReadReg(MPU6050_GYRO_XOUT_H) << 8) | MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    AG[1][1] = (MPU6050_ReadReg(MPU6050_GYRO_YOUT_H) << 8) | MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    AG[1][2] = (MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H) << 8) | MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
}

/**
 * @brief MPU6050芯片读取指定长度地址寄存器
 * @param {u8} RegAddress: 指定寄存器起始地址
 * @param {u8} Data: 存放数据的数组
 * @param {int} Num: 指定读取数据长度
 * @retval 无
 */
void MPU6050_ReadRegS(u8 RegAddress,u8 Data[], int Num){
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceivAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceivAck();

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
    MyI2C_ReceivAck();
    for (int i = 0; i < Num; i++)
    {
        Data[i] = MyI2C_ReceiveByte();
        if (i==Num -1)
        {
            MyI2C_SendAck(1);
        } else{
            MyI2C_SendAck(0);
        }
    }
    MyI2C_End();
}

/**
 * @brief MPU6050读取数据寄存器内容
 * @param {int16_t} AG: 存放数据的数组
 * @retval 无
 */
void MPU6050_GetDateS(int16_t AG[2][3]){
    u8 Data[12];
    MPU6050_ReadRegS(MPU6050_ACCEL_XOUT_H, Data, 12);
    AG[0][0] = (Data[0] << 8) | Data[1];
    AG[0][1] = (Data[2] << 8) | Data[3];
    AG[0][2] = (Data[4] << 8) | Data[5];
    AG[1][0] = (Data[6] << 8) | Data[7];
    AG[1][1] = (Data[8] << 8) | Data[9];
    AG[1][2] = (Data[10] << 8) | Data[11];
}