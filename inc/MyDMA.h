/*
 * @Author: lunuj
 * @Date: 2023-09-23 21:34:22
 * @LastEditTime: 2023-09-23 21:37:05
 * @FilePath: \test\Hardware\MyDMA.h
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#ifndef __MYDMA_H
#define __MYDMA_H

void MyDMA_Init(u32 AddrA, u32 AddrB);
void MyDMA_Transf(u32 Size);
#endif