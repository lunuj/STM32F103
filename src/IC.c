#include "stm32f10x.h"
#include "IC.h"

void IC_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM3);
    // TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted,0x00);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 -1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    TIM_ICInitTypeDef TIM_ICInitTypeDefStructure;
    TIM_ICInitTypeDefStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitTypeDefStructure.TIM_ICFilter = 0xf;
    TIM_ICInitTypeDefStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitTypeDefStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitTypeDefStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3, &TIM_ICInitTypeDefStructure);

    TIM_PWMIConfig(TIM3, &TIM_ICInitTypeDefStructure);
    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
    TIM_Cmd(TIM3, ENABLE);
}

u32 IC_GetFreq(void){
    return 1000000/(TIM_GetCapture1(TIM3)+1);
}

u32 IC_GetDuty(void){
    return (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1);
}