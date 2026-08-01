#include "fifo_ring.hpp"
#include "serial_print.hpp"
#include "../StellarisWare/inc/hw_memmap.h"
#ifdef __cplusplus extern "C"{
#endif
#include "../StellarisWare/inc/hw_uart.h"
#ifdef __cplusplus }
#endif


int main(){
 FIFO_Ring<64> A; 
 
Serial_Print SP1([&A](uint8_t b){ A.add_byte(b);});
Serial_Print SP2([=](uint8_t b){ UARTCharPut(UART0_BASE, b); });


}