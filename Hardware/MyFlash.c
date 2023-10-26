#include "stm32f10x.h"
#include "MyFlash.h"


u32 MyFlash_ReadWord(u32 Address){
    return *((__IO u32 *)(Address));
}

u16 MyFlash_ReadHalfWord(u32 Address){
    return *((__IO u16 *)(Address));
}

u8 MyFlash_ReadByte(u32 Address){
    return *((__IO u8 *)(Address));
}

void MyFlash_EraseAllPage(void){
    FLASH_Unlock();
    FLASH_EraseAllPages();
    FLASH_Lock();
}

void MyFlash_ErasePage(u32 PageAddress){
    FLASH_Unlock();
    FLASH_ErasePage(PageAddress);
    FLASH_Lock();
}

void MyFlash_ProgramWord(u32 Address, u32 Data){
    FLASH_Unlock();
    FLASH_ProgramWord(Address, Data);
    FLASH_Lock();
}

void MyFlash_ProgramHalfWord(u32 Address, u16 Data){
    FLASH_Unlock();
    FLASH_ProgramHalfWord(Address, Data);
    FLASH_Lock();
}