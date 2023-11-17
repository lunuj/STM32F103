#ifndef __STORE_H__
#define __STORE_H__
#define STORE_START_ADDRESS 0x800FC00
#define STORE_COUNT 256
extern u32 Store_Cache[];
void Store_Init(void);
void Store_Save(void);
void Store_Clear(void);

#endif // __STORE_H__

