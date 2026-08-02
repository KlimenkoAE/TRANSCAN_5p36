#include "fifo_ring.hpp"
#include "serial_print.hpp"
#include "_CDC.hpp"
#include "USB_THIS_PROGRAM_DEFS.hpp"
#include "_TIMERS.hpp"

extern "C"{
#include "timer.h"
#include "sysctl.h"
#include "hw_memmap.h"
#include "hw_uart.h"
#include "interrupt.h"
 }



int main(){
//common timer us
/////////////////
TimerPeriodic_us<
TIMER0_BASE
,TIMER_CFG_32_BIT_PER
, SYSCTL_PERIPH_TIMER0
,TIMER_A
,TIMER_TIMA_TIMEOUT
,1
,10,100,1000,10000,100000,1000000> T_us;



//cdc 0
CDC
<
 0x800
,0x800

,USB0_BASE

,CDC0_DATA_IN_EP
,CDC0_DATA_IN_EP_SZ
,CDC0_DATA_IN_INT

,CDC0_DATA_OUT_EP
,CDC0_DATA_OUT_EP_SZ
,CDC0_DATA_OUT_INT

,CDC0_COMMUNICATION_EP
,CDC0_COMMUNICFTION_EP_SZ
,CDC0_COMMUNICATION_INT    
> CDC0(T_us.IntFlag(0),T_us.IntFlag(0));


};