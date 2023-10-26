#include "stm32f10x.h"
#include "MyFlash.h"
#include "Store.h"

u32 Store_Cache[STORE_COUNT];

void Store_Init(void){
    if (MyFlash_ReadWord(STORE_START_ADDRESS) != 0xA5A5A5A5)
    {
        MyFlash_ErasePage(STORE_START_ADDRESS);
        MyFlash_ProgramWord(STORE_START_ADDRESS, 0xA5A5A5A5);
        for (u16 i = 1; i < STORE_COUNT; i++)
        {
            MyFlash_ProgramWord(STORE_START_ADDRESS + i*4,0x00000000);
        }
    }
    for (int i = 0; i < STORE_COUNT; i++)
    {
        Store_Cache[i] = MyFlash_ReadWord(STORE_START_ADDRESS + i*4);
    }
}

void Store_Save(void){
    MyFlash_ErasePage(STORE_START_ADDRESS);
    for (int i = 0; i < STORE_COUNT; i++)
    {
        MyFlash_ProgramWord(STORE_START_ADDRESS + i*4, Store_Cache[i]);
    }
}

void Store_Clear(void){
    for (int i = 1; i < STORE_COUNT; i++)
    {
        Store_Cache[i] = 0x000000;
    }
    Store_Save();
}