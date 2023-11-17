#ifndef __MPU6050_H__
#define __MPU6050_H__

#define MPU6050_ADDRESS 0xD0

#define	MPU6050_SMPLRT_DIV		0x19
#define	MPU6050_CONFIG			0x1A
#define	MPU6050_GYRO_CONFIG		0x1B
#define	MPU6050_ACCEL_CONFIG	0x1C

#define	MPU6050_ACCEL_XOUT_H	0x3B
#define	MPU6050_ACCEL_XOUT_L	0x3C
#define	MPU6050_ACCEL_YOUT_H	0x3D
#define	MPU6050_ACCEL_YOUT_L	0x3E
#define	MPU6050_ACCEL_ZOUT_H	0x3F
#define	MPU6050_ACCEL_ZOUT_L	0x40
#define	MPU6050_TEMP_OUT_H		0x41
#define	MPU6050_TEMP_OUT_L		0x42
#define	MPU6050_GYRO_XOUT_H		0x43
#define	MPU6050_GYRO_XOUT_L		0x44
#define	MPU6050_GYRO_YOUT_H		0x45
#define	MPU6050_GYRO_YOUT_L		0x46
#define	MPU6050_GYRO_ZOUT_H		0x47
#define	MPU6050_GYRO_ZOUT_L		0x48

#define	MPU6050_PWR_MGMT_1		0x6B
#define	MPU6050_PWR_MGMT_2		0x6C
#define	MPU6050_WHO_AM_I		0x75

void MPU6050_Init(void);

void MPU6050_WriteReg(u8 RegAddress, u8 Data);

u8 MPU6050_ReadReg(u8 RegAddress);

void MPU6050_GetDate(int16_t AG[2][3]);

void MPU6050_ReadRegS(u8 RegAddress, u8 Data[], int Num);

void MPU6050_GetDateS(int16_t AG[2][3]);


void MPU6050H_Init(void);
void MPU6050H_WriteReg(u8 RegAddress, u8 Data);
u8 MPU6050H_ReadReg(u8 RegAddress);
void MPU6050H_GetDate(int16_t AG[2][3]);
void MPU6050H_WaitEvent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT);

#endif // __MPU6050_H__