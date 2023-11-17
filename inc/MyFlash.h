#ifndef __MYFLASH_H__
#define __MYFLASH_H__

u32 MyFlash_ReadWord(u32 Address);
u16 MyFlash_ReadHalfWord(u32 Address);
u8 MyFlash_ReadByte(u32 Address);

void MyFlash_EraseAllPage(void);
void MyFlash_ErasePage(u32 PageAddress);

void MyFlash_ProgramWord(u32 Address, u32 Data);

void MyFlash_ProgramHalfWord(u32 Address, u16 Data);

#endif // __MYFLASH_H__

