#pragma once
extern "C"{
#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "sysctl.h"
#include "rom.h"
#include "rom_map.h"
#include"interrupt.h"



}
#include <functional>
#include <algorithm>
extern "C"{
 void ISR0();
 void ISR1();
 void ISR2();
 void ISR3();
 void ISR4();
 void ISR5();
 void ISR6();
 void ISR7();
 void ISR8();
 void ISR9();
};

class TimerISR {   // без static class
public:
    static uint8_t isr_count;
    static std::function<void()> lmd[10];
    static void (*ISR[10])();

    static void Registration(uint32_t b, uint32_t t, std::function<void()> isr);
    static void InitTable();  // один раз при старте
};
/*static class TimerISR{
public:
static uint8_t isr_count;


static  std::function<void()> lmd[10];
static void (*ISR[10])();

static void Registration(uint32_t b,uint32_t t, std::function<void()> isr){
lmd[isr_count]=isr;
TimerIntRegister(b,t,ISR[isr_count]);
}
TimerISR(){
ISR[0]=ISR0;
ISR[1]=ISR1;
ISR[2]=ISR2;
ISR[3]=ISR3;
ISR[4]=ISR4;
ISR[5]=ISR5;
ISR[6]=ISR6;
ISR[7]=ISR7;
ISR[8]=ISR8;
ISR[9]=ISR9;
}
};
*/
template<uint32_t timer_base, uint32_t timer_cfg_bit_per,
uint32_t sysctl_periferal,
uint32_t timer_letter,
uint32_t timer_timeout,
uint32_t period_us,uint32_t... ext_periodes>

class TimerPeriodic_us{

class InerStruct{
  public:
  uint32_t period;
  uint32_t load;
  uint32_t presc;
  bool  int_flag;

  InerStruct(uint32_t p0,uint32_t p){
    period=p;
    load=SysCtlClockGet()/1000000 * p0 - 1;
    presc=p/p0;
    int_flag=false;
  };
 // uint32_t GetLoad(){return load; }
 // uint32_t GetPresc(){return presc;}
  bool& IntFlag(){return int_flag;} 
  };

InerStruct main_period = {InerStruct{period_us,period_us}};
uint8_t  ext_periodes_cnt=sizeof...(ext_periodes);
uint32_t max_ext_period = (std::max)({ext_periodes...});
InerStruct ExtPeriodes[sizeof...(ext_periodes)]={InerStruct{period_us,ext_periodes}...};


bool TIMER_IS_INIT;
bool TIMER_IS_ENABLE;

void ISR(){
static uint32_t counter=0;
  uint32_t ts=TimerIntStatus(timer_base,true);

  if( ts&timer_timeout){
        TimerIntClear(timer_base, timer_timeout);
        main_period.int_flag=true;
 

        for(int i=0;i<ext_periodes_cnt;++i){
          if(counter%ExtPeriodes[i].presc==0){
          ExtPeriodes[i].int_flag=true;
          if(ExtPeriodes[i].period==max_ext_period)counter=0;
            else ++counter;
          }
        }
  }
};
public:
TimerPeriodic_us(){
TIMER_IS_INIT=false;
    SysCtlPeripheralEnable(sysctl_periferal);

    TimerDisable(timer_base, timer_letter);

    TimerConfigure(timer_base, timer_cfg_bit_per);

    TimerLoadSet(timer_base,timer_letter,main_period.load);
    TimerISR::Registration(timer_base,timer_letter,[this](){
    this->ISR();
    });
  //  TimerIntRegister(timer_base,timer_letter,Timer_ISR_Wrapper);
    TimerIntClear(timer_base, timer_timeout);
    TimerIntEnable(timer_base, timer_timeout);
TIMER_IS_INIT=true;
};
void Enable(){
if(TIMER_IS_ENABLE==false&&TIMER_IS_INIT){
    TimerEnable(timer_base,timer_letter);
    TimerIntEnable(timer_base,timer_timeout);
    TIMER_IS_ENABLE=true;
    }
};
void Disable(){
  if(TIMER_IS_ENABLE==true&&TIMER_IS_INIT){
    MAP_TimerDisable(timer_base, timer_letter);
    TimerIntDisable(timer_base, timer_timeout);
    TIMER_IS_ENABLE=false;
    }
  }
bool& IntFlag(uint8_t i){return ExtPeriodes[i].IntFlag();} 
};

