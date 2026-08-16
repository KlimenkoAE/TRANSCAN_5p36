#include "fifo_ring.hpp"
#include "serial_print.hpp"
#include "_CDC.hpp"
#include "USB_THIS_PROGRAM_DEFS.hpp"
#include "_TIMERS.hpp"
#include "_USB.hpp"
#include "wrappers_headers.hpp"

/*extern "C"{
#include "hw_ints.h"
#include "timer.h"
#include "sysctl.h"
#include "hw_memmap.h"
#include "hw_uart.h"
#include "interrupt.h"
#include "lm3s5p36.h"
 }*/

/*extern "C" void CPUcpsie(void)
{
    __asm volatile("cpsie i");
}

extern "C" void CPUcpsid(void)
{
    __asm volatile("cpsid i");
}
*/

volatile const char *gAssertFile;
volatile unsigned long gAssertLine;
extern "C"
void __error__(char *pcFilename, unsigned long ulLine)
{
    gAssertFile = pcFilename;
    gAssertLine = ulLine;

    while (1)
    {
        __asm volatile ("nop");
    }
}
/*
extern "C" void HardFault_HandlerC(uint32_t *sp);

extern "C"
__attribute__((naked))
void HardFault_Handler(void)
{
    __asm volatile(
        "tst lr,#4\n"
        "ite eq\n"
        "mrseq r0,msp\n"
        "mrsne r0,psp\n"
        "b HardFault_HandlerC");
}

volatile uint32_t HF_PC;
volatile uint32_t HF_LR;
volatile uint32_t HF_HFSR;
volatile uint32_t HF_CFSR;
extern "C"
void HardFault_HandlerC(uint32_t *sp)
{
    HF_PC = sp[6];
    HF_LR = sp[5];

    HF_HFSR = NVIC_HFAULT_STAT_R;
    HF_CFSR = NVIC_FAULT_STAT_R;

    while (1);
}*/
/*extern "C"{

volatile uint32_t HF_HFSR;
volatile uint32_t HF_CFSR;
volatile uint32_t HF_BFAR;
volatile uint32_t HF_MMFAR;
volatile uint32_t HF_DFSR;
void HardFault_Handler(void)
{
    HF_HFSR  =NVIC_HFAULT_STAT_R;
    HF_CFSR  = NVIC_FAULT_STAT_R;
    HF_BFAR  = NVIC_FAULT_ADDR_R;
    HF_MMFAR = NVIC_MM_ADDR_R;
    HF_DFSR  = NVIC_DEBUG_STAT_R;
uint8_t stop=0;
    while (1)
    {
        __asm volatile ("nop");
    }
}
}*/
int main(){
/*//PLL 20 MHz 400/8
SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL |SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);*/
 //MAP_IntMasterDisable();
//PLL 50 MHz                 
SysCtlClockSet(
    SYSCTL_SYSDIV_4 |
    SYSCTL_USE_PLL |
    SYSCTL_OSC_MAIN |
    SYSCTL_XTAL_16MHZ);
SysCtlPeripheralClockGating(true);
uint32_t dbg = SysCtlClockGet();

MAP_SysCtlPeripheralEnable(CONTROL_EP.INIT_DATA.SysCtlPeriferal );
  //common timer us
  /////////////////
  /*TimerPeriodic_us<
  TIMER0_BASE
  ,TIMER_CFG_32_BIT_PER
  , SYSCTL_PERIPH_TIMER0
  ,TIMER_A
  ,TIMER_TIMA_TIMEOUT
  ,1
  ,10,100,1000,10000,100000,1000000> T_us;

T_us.Disable();*/
 MAP_IntMasterEnable();
bool T1=false;
bool T2=false;
 


  CDC
  <
  CONTROL_EP,
  CDC_INIT   
  > CDC0(T1,T2);//(T_us.IntFlag(0),T_us.IntFlag(5));

 
 
   USB<
  CONTROL_EP,
  CDC_DEVICE_CLASS //
  >USB0;


uint8_t df1,df2;
  
  




  //cdc 0






  MAP_IntMasterEnable();





  while(1) {




  }
};