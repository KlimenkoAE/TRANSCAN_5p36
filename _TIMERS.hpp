#pragma once
extern "C"{
#include <stdint.h>
#include <stdbool.h>
}


struct _TimersIntRegisterList{
bool TIM0A_TIMEOUT_INT:1;
bool TIM0B_TIMEOUT_INT:1;
bool TIM1A_TIMEOUT_INT:1;
bool TIM1B_TIMEOUT_INT:1;
struct Timer32* pT0A;
struct Timer32* pT0B;
struct Timer32* pT1A;
struct Timer32* pT1B;
}TimersIntRegisterList;

enum TimerPeriodes{pInvalid=0xFFFF,pT1=0,pT2=1,pT3=2,pT4=3,pT5=4,pT6=5,pT7=6,pT8=7,pT9=8};
struct Timer32{
uint32_t ExtCnt;
uint32_t T0;
bool T0_int:1;
  union{
    struct {   
    const uint32_t T1;
    const uint32_t T2;
    const uint32_t T3;
    const uint32_t T4;
    const uint32_t T5;
    const uint32_t T6;
    const uint32_t T7;
    const uint32_t T8;
    const uint32_t T9;
    };
    uint32_t T[9];
    }ExtPeriodes;
    union{
    struct {   
    const uint32_t presc1;
    const uint32_t presc2;
    const uint32_t presc3;
    const uint32_t presc4;
    const uint32_t presc5;
    const uint32_t presc6;
    const uint32_t presc7;
    const uint32_t presc8;
    const uint32_t presc9;
    };
    uint32_t P[9];
    }Presc;
     union{
    struct {   
     bool T1_int;
     bool T2_int;
     bool T3_int;
     bool T4_int;
     bool T5_int;
     bool T6_int;
     bool T7_int;
     bool T8_int;
     bool T9_int;
    };
    bool F[9];
    }IntF;
bool TIMER_IS_INIT;
bool TIMER_IS_ENABLE;
const uint32_t SYSCTL_PERIPH_TIMER;
const uint32_t TIMER_BASE;
const uint32_t TIMER_AB;
const uint32_t TIMER_TIMEOUT;
const uint32_t INT_TIMER_N_AB;
  void (*SetMainPeriod)(struct Timer32*,uint32_t);
  enum TimerPeriodes (*AddExtPeriod)(struct Timer32*,uint32_t);
};


//структуры
struct _Timer0A_us_prescallers{
uint32_t MainPeriod;
uint32_t ScalSmall;
uint32_t ScalBig;
};
//функции
extern void Timer_SetMainPeriod_us(struct Timer32* t,uint32_t P_us);
extern enum TimerPeriodes Timer_AddExtPeriod_us(struct Timer32* t,uint32_t P_us);
extern void Timer_us_Init(struct Timer32* t );