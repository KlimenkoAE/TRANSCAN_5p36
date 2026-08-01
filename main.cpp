#include "fifo_ring.hpp"
#include "serial_print.hpp"
#include "_CDC.hpp"
#include "USB_THIS_PROGRAM_DEFS.hpp"

extern "C"{
#include "hw_memmap.h"
#include "hw_uart.h"
 }



int main(){
 FIFO_Ring<64> A; 
 
Serial_Print SP1([&A](uint8_t b){ A.add_byte(b);});
Serial_Print SP2([=](uint8_t b){ UARTCharPut(UART0_BASE, b); });

bool f1;
bool f2;

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
> CDC0(f1,f2);
};