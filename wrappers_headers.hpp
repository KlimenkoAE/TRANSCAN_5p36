#pragma once
extern "C"{
#define STELLARIS
#ifdef STELLARIS
#include "lm3s5p36.h"
#include "hw_types.h"
#include "hw_ints.h"
#include "timer.h"
#include "sysctl.h"
#include "hw_memmap.h"
#include "hw_uart.h"
#include "interrupt.h"
#include "usb.h"
#include "hw_usb.h"
#endif
}
#include <cstdint>


template <class T>
class VendorConsts;

template <class T>
class FunctionWraper{
class USB;
};

class Stellaris{
public:
class USB;
};
template<typename T>
struct PHYEndpoint;
template<typename T>
struct PHYControlEndpoint;


template<typename T> 
struct  PHY_USB{

};
template <typename T>
struct USB_FIFO{
uint32_t  SZ;//vendor const
bool DoubleBuffered;
uint32_t CFG_FLAGS;
};

template <typename T>
struct PHYEndpointBase{
uint32_t USB_BASE;
uint32_t IDX;
uint32_t ALIAS;//USB_EP_N - Stellaris !=EP_IDX 
uint32_t SZ;//number 16/64/
uint32_t INTEP;//interrupt
uint8_t  ADDR;

};

template <typename T>
struct PHYEndpoint:PHYEndpointBase<T>{
uint32_t CFG_FLAGS;
USB_FIFO<T> FIFO;
};
template <typename T>
struct USB_INIT_DATA{
uint32_t INT_USBDevice;
uint32_t INT_GEN_FlagsAll;
uint32_t INT_GEN_Flags_Enable;
uint32_t INT_All;
uint32_t INT_EP0;
uint32_t SysCtlPeriferal;
};

template <typename T>
struct PHYControlEndpoint:PHYEndpointBase<T>{
USB_INIT_DATA<T> INIT_DATA;
};




using  PROC=Stellaris;


using USBVndCnst = VendorConsts<PROC>;

#include "USB_CLASSES.hpp"

#include "VENDOR_CONSTANT_WRAP.hpp"

#include "VendorFunctionsWrap.hpp"



#include "BackEnd.hpp"

#include "USB_THIS_PROGRAM_DEFS.hpp"