#include "stm32f10x.h"
#include "MySPI.h"
#include "W25Q64.h"
#include "W25Q64_lns.h"

/**
 * @brief W25Q64初始化
 */
void W25Q64_Init(void){
    MySPI_Init();

}

/**
 * @brief W25Q64读取ID
 * @param MID [u8*] 得到的W25Q64的厂商ID
 * @param DID [u16*] 得到的W25Q64的设备ID
 */
void W25Q64_ReadID(u8* MID, u16* DID){
    MySPI_Start();
    MySPI_SwapByte(W25Q64_JEDEC_ID);
    *MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID <<= 8;
    *DID|=MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    MySPI_Stop();
}

/**
 * @brief W25Q64写使能
 */
void W25Q64_WriteEnable(void){
    MySPI_Start();
    MySPI_SwapByte(W25Q64_WRITE_ENABLE);
    MySPI_Stop();
}

/**
 * @brief W25Q64等待忙状态
 */
void W25Q64_WaitBusy(void){
    int TimeOut = 100000;
    MySPI_Start();
    MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
    while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01 == 0x01) && TimeOut--!=0);
    MySPI_Stop();
}

/**
 * @brief W25Q64进行页编程
 * @param Address [u32] 页编程起始地址
 * @param DataArray [u8*] 页编程数据指针
 * @param Count [u8] 页编程数据个数
 */
void W25Q64_PageProgram(u32 Address, u8* DataArray, u8 count){
    W25Q64_WriteEnable();
    MySPI_Start();
    MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    for (int i = 0; i < count; i++)
    {
        MySPI_SwapByte(DataArray[i]);
    }
    MySPI_Stop();
    W25Q64_WaitBusy();
}

/**
 * @brief W25Q64扇擦除
 * @param Address [u32] 擦除起始地址
 */
void W25Q64_SectorErase(u32 Address){
    W25Q64_WriteEnable();
    MySPI_Start();
    MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
    MySPI_SwapByte(0x00);
    MySPI_SwapByte(0x00);
    MySPI_SwapByte(0x00);
    MySPI_Stop();
    W25Q64_WaitBusy();
}

/**
 * @brief W25Q64读取数据
 * @param Address [u32] 数据起始地址
 * @param DataArray [u8*] 数据存放地址
 * @param Count [u32] 读取数据个数
 */
void W25Q64_ReadData(u32 Address, u8* DataArray, u32 count){
    MySPI_Start();
    MySPI_SwapByte(W25Q64_READ_DATA);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    for (int i = 0; i < count; i++)
    {
        DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);    
    }
    MySPI_Stop();
}