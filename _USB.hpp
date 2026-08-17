#pragma once

extern "C"{
#include "usb.h"
#include "hw_usb.h"
#include "sysctl.h"
#include "hw_ints.h"
#include "rom.h"
#include "rom_map.h"
#include "hw_memmap.h"
#include"interrupt.h"
#include "stdio.h"
}
#include <cstdint>
#include <cstdbool>
#include <functional>
#include <algorithm>
#include <cstdarg>

#include "periferalISR.hpp"
#include "USB_CONSTS.hpp"
//#include "USB_THIS_PROGRAM_DEFS.hpp"
#include "periferalInterruptsHandlers.hpp"
//#include "VENDOR_CONSTANT_WRAP.hpp"
#include "wrappers_headers.hpp"

//#define USB_GEN_INT_EN USB_INTCTRL_RESET|USB_INTCTRL_SUSPEND|USB_INTCTRL_RESUME|USB_INTCTRL_SOF
struct SetUpFlags;
template<
auto ,
auto 
>
class USBEnumerator;

class USB_DescriptorTypes;


template<auto ,auto >
class USB_Descriptors;

class UsbISR:IPeriferalISR{
public:
void Registration(std::function<void()> isr, uint32_t sw_def, ...);
};

//////////////////////////CLASS USB
template<
PHYControlEndpoint<PROC> CTR_EP,
auto DEVICE  //DEVICE_CLASS
>
class USB{
enum _device_state device_state; 

//INTERRUPT
UsbISR UISR;
public:
USB(){
  UISR.Registration([this](){
      this->ISR();
      },CTR_EP.USB_BASE);

  ExtSetupHandlerRegister([this](const _Buffer& su_buf,uint32_t& sup_data){

                   USBWRP::DevEndpointDataAck( CTR_EP,false);
                         while(!(HWREGB(CTR_EP.USB_BASE+ USB_CSRL0 )&USB_CSRL0_SETEND));
                   USBWRP::DevAddrSet(CTR_EP,(unsigned long)(buffer.wValueL&0x7F));

                    device_state=Adressed;
                  },
                  SET_ADDRESS);


////////USB INIT
/* MAP_SysCtlPeripheralEnable(sysctl_periferal);

  //The next step is to enable the USB PLL 
  //so that the correct clocking is provided to the PHY.

  MAP_SysCtlUSBPLLEnable();

 // USBIntRegister(usb_base, ISR_USB);
  
MAP_IntEnable(INT_USB0);

USBWRP::IntDisableControl(usb_base,USB_INTCTRL_ALL);
USBWRP::IntEnableControl(usb_base,USB_GEN_INT_EN);

USBWRP::IntDisableEndpoint(usb_base,USB_INTEP_ALL);
USBWRP::IntEnableEndpoint(usb_base,USB_INT_EP0);

USBWRP::IntEnable(usb_base,USB_INT_ALL );

USBWRP::DevConnect(usb_base);*/
USBWRP::UsbInit(CTR_EP );
//Execute_ExtSetupHandler(SET_CONFIGURATION,0,buffer,(uint32_t&)device_state);

}



void ISR(){

volatile uint8_t csr0;
volatile uint8_t count0;
volatile uint8_t type0;

csr0   = HWREGB(USB0_BASE + USB_O_CSRL0);
count0 = HWREGB(USB0_BASE + USB_O_COUNT0);
type0  = HWREGB(USB0_BASE + USB_O_TYPE0);   // если есть

uint32_t int_GEN_status;
uint32_t int_COM_status;
  int_COM_status=USBWRP::IntStatusEndpoint(CTR_EP);
  if(int_COM_status!=0)
  // printf("CS %d \n",int_COM_status);
    USB_COM_Vector(int_COM_status);
  int_GEN_status=USBWRP::IntStatusControl(CTR_EP);
    USB_GEN_Vector(int_GEN_status);
return;
}

inline int USB_GEN_Vector(uint32_t int_GEN_status){

if(int_GEN_status&USB_INTCTRL_RESET){
  return 1;
}


if(int_GEN_status&USB_INTCTRL_RESUME){
return 3;
}

if(int_GEN_status&USB_INTCTRL_SUSPEND){

  device_state=Suspend;
  return 2;
}

if(int_GEN_status&USB_INTCTRL_SOF){
  return USB_IS_SOF;
  }
return 0;
}

inline int USB_COM_Vector(uint32_t int_COM_status){

 if(int_COM_status&USB_INTEP_0){
unsigned long SetupPacketSz = USBWRP::EndpointDataAvail(CTR_EP.USB_BASE, CTR_EP);

  if(SetupPacketSz>0)
  {
   Enumerator.USB_SetUpHandler(int_COM_status,SetupPacketSz,device_state);
  //  int_COM_status&=~(USB_INTEP_0);
  }
}
USB_COM_Handlers<CTR_EP.USB_BASE>::Execute(int_COM_status);

return 0;
}

////////////////////

USBEnumerator<CTR_EP,DEVICE>Enumerator;
USB_Descriptors<CTR_EP,DEVICE> Descriptors;

};//class USB


template<
auto CTR_EP,
auto DEVICE
>
class USBEnumerator{
 inline static SetupStage_t SetupStage;
 /*
static void EP_StatusClear(USBVndCnst::MyUSB_EP ep){
 uint32_t st  = USBWRP::EndpointStatus(usb_base, ep);
    USBWRP::DevEndpointStatusClear(usb_base, ep, st);
}
*/

public:
inline int USB_SetUpHandler(uint32_t int_COM_status,unsigned long   SetupPacketSz,_device_state& device_state){

    USBWRP::EndpointDataGet ( CTR_EP, (uint8_t*)&buffer,  &SetupPacketSz);
      if(SetupStage.Stage==SETUP)
          SetupStage.Request=buffer.wRequest;
    processingSetupPackage(SetupStage.Request,device_state);

return 0;
}

//////////////////
static void processingSetupPackage(uint16_t rq,_device_state& device_state){
if(buffer.wValueH==2|buffer.wValueL==2)	{
uint8_t stop=1;
}
	switch(rq){
		case GET_STATUS_DEVICE      :
		status_dev();
		break;

		case GET_STATUS_INTERF      :
		goto no_implementation;
		break;

		case GET_STATUS_ENDPNT      :
		goto no_implementation;
		break;

		case CLEAR_FEATURE_DEVICE:
                switch (buffer.wValueL)
                {
                    case 1: // DEVICE_REMOTE_WAKEUP
                        // remote_wakeup_enabled = 0;
                        USBWRP::DevEndpointDataAck(CTR_EP, true);
                        break;

                    default:
                        // CLEAR TEST_MODE по спеке нельзя
                        USBWRP::DevEndpointStall(CTR_EP);
                        break;
                }
                break;

		case CLEAR_FEATURE_INTERF   :
		goto no_implementation;
		break;

		case CLEAR_FEATURE_ENDPNT   :

                // уточняем feature = ENDPOINT_HALT (wValue == 0)
                if (buffer.wValue != 0)
                {
                    USBWRP::DevEndpointStall(CTR_EP);
                    break;
                }

                switch (buffer.wIndexL)
                {
                    case 0x81: 
                        Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x81);                                           
                        break;

                    case 0x02: 
                          Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x02);
                        break;

                    case 0x82: // EP2 IN — Bulk IN (типичный CDC)            
                        Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x82);
                        break;

                    case 0x83: // EP3 IN — только если такой endpoint есть
                         Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x83);
                        break;

                    case 0x01: // EP1 OUT — на всякий случай (в логе бывало wIndex=0001)
                        // если EP1 OUT нет в дескрипторах — можно просто ACK
                         Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x01);
                        break;

                    default:
                        USBWRP::DevEndpointStall(CTR_EP);
                        break;
                }
                break;

		case SET_FEATURE_DEVICE:
                  // wValue = feature
                  switch (buffer.wValueL)
                  {
                      case 1: // DEVICE_REMOTE_WAKEUP
                          // remote_wakeup_enabled = 1;
                          USBWRP::DevEndpointDataAck(CTR_EP, true);
                          break;

                      case 2: // TEST_MODE (для FS CDC обычно не нужен)
                          USBWRP::DevEndpointStall(CTR_EP);
                          break;

                      default:
                          USBWRP::DevEndpointStall(CTR_EP);
                          break;
                  }
                  break;

		case SET_FEATURE_INTERF     :
		goto no_implementation;
		break;

		case SET_FEATURE_ENDPNT     :
		goto no_implementation;
		break;

		case SET_ADDRESS            :
                Execute_ExtSetupHandler(SET_ADDRESS) ;
             //   USBWRP::DevEndpointDataAck(usb_base,USB_EP_0,true);
              //      while(!(HWREGB(usb_base+ USB_CSRL0 )&USB_CSRL0_SETEND));
              //     USBWRP::DevAddrSet(usb_base,(unsigned long)(buffer.wValueL&0x7F));
		break;

		case GET_DESCRIPTOR_DEVICE  :
              if(!USB_Descriptors<CTR_EP,DEVICE>::DescriptorSend(buffer.wValueH,buffer.wLengthL,buffer.wValueL))
              goto no_implementation;	
        	break;

		case GET_DESCRIPTOR_INTERF  :
                goto no_implementation;
		break;

		case GET_DESCRIPTOR_ENDPNT  :
		goto no_implementation;
		break;

		case SET_DESCRIPTOR         :
		goto no_implementation;
		break;

		case GET_CONFIGURATION      :
                if(!USB_Descriptors<CTR_EP,DEVICE>::DescriptorSend(buffer.wValueH,buffer.wLengthL,buffer.wValueL))
		goto no_implementation;
		break;

		case SET_CONFIGURATION  :
             // 
                Execute_ExtSetupHandler(SET_CONFIGURATION,0,buffer,(uint32_t&)device_state);
               // USBWRP::DevEndpointDataAck(CTR_EP,true);
                  USBDevEndpointDataAck(USB0_BASE, 0,true);
             //   ToDebugPrint.DebugPrintAdd(0,EP_CONTROL_STATUS_F,SET_CONFIGURATION,"SET_CONFIGURATION");
		break;

		case GET_INTERFACE          :
		goto no_implementation;
		break;

		case SET_INTERFACE          :
		goto no_implementation;
		break;

		case SYNCH_FRAME            :
		goto no_implementation;
		break;

		case GET_REPORT             :
		goto no_implementation;
		break;
		
		case SET_IDLE        	   :
		break;
                case USB_CDC_SET_LINE_CODING:
               

if(SetupStage.Stage==enumSetupStage::SETUP){
SetupStage.Stage=enumSetupStage::DATA;
SetupStage.data_len=(uint16_t)buffer.wLengt;
USBWRP::DevEndpointDataAck(CTR_EP, false);
//ToDebugPrint.DebugPrintAdd(0,EP_CONTROL_STATUS_F,SET_CONFIGURATION,"SETUP STAGE CDC_SET_LINE_CODING");
//printf("0x2021 setup  \n");
}
else
{
//printf("0x2021 data  \n");
    Execute_ExtSetupHandler(USB_CDC_SET_LINE_CODING,0,buffer,(uint32_t&)SetupStage.data_len);  
                USBWRP::DevEndpointDataAck(CTR_EP, true);
SetupStage.Stage=enumSetupStage::SETUP;
}                  
                break;
                case USB_CDC_GET_LINE_CODING:

                // Отправляем текущую структуру Line Coding
                Execute_ExtSetupHandler(USB_CDC_GET_LINE_CODING) ; 



                // Завершаем control-transfer
                USBWRP::DevEndpointDataAck(CTR_EP, true);

                break;

    
            //    break;
                case USB_CDC_SET_CONTROL_LINE_STATE:
               //   printf("0x2221  \n");
                Execute_ExtSetupHandler(USB_CDC_SET_CONTROL_LINE_STATE,0,buffer) ;

                USBWRP::DevEndpointDataAck(CTR_EP, true);
                 break;	
no_implementation:		
		default:
               // USBWRP::DevEndpointStall(CTR_EP);
		//stall();
		break;		

	}

};//Process packet



static void status_dev(){
//bus powred, remote wakeup
SetUpAnswer((uint8_t*)&STATUS_DEVICE,sizeof(STATUS_DEVICE),buffer.wLengthL);
        USBWRP::EndpointDataPut(CTR_EP, (uint8_t*)&STATUS_DEVICE, buffer.wLengthL);
}
static void SetUpAnswer(uint8_t* buf,uint8_t buf_sz,uint8_t host_await_sz){

        uint8_t byte_left= buf_sz>host_await_sz?host_await_sz:buf_sz;
        uint8_t* data_begin=buf;


        while(byte_left>=EP0_SZ){
          uint8_t byte_to_transfer=EP0_SZ;      
          while( USBWRP::EndpointDataPut(CTR_EP,data_begin,byte_to_transfer)==-1){;}; 
        if(byte_left==0)      
          {while(USBWRP::EndpointDataSend(CTR_EP,USB_TRANS_IN)==-1){;};break;}
        else {while(USBWRP::EndpointDataSend(CTR_EP,USB_TRANS_IN)==-1){;}};
        byte_left-=byte_to_transfer;
        data_begin+=byte_to_transfer;
	}
        //0<byte_left<EP0_SZ
        while( USBWRP::EndpointDataPut(CTR_EP,data_begin,byte_left)==-1){;};
        while( USBWRP::EndpointDataSend(CTR_EP,USB_TRANS_IN_LAST)==-1){;};
}
};//Enumerator
/*
struct SetUpFlags{
union GetDev{
  struct{
  uint8_t getStatusDevice :1;
  uint8_t getStatusInterface :1;
  uint8_t getStatusEndPoint :1; 
  uint8_t getReport :1; 
  uint8_t getInterface :1; 
  };
  uint8_t all;
};

uint16_t clearFutureDevice_remoteWakeup :1; 
uint16_t clearFutureDevice_testMode :1;
uint16_t clearFutureInterface :1;
uint16_t SynkFrame :1; 



union SetDev{
struct{ 
uint8_t SetFutureDeviceRemoteWakeUp:1;
uint8_t SetFutureDeviceTestMode:1;
uint8_t SetFutureInterface :1;
uint8_t setAddress :1; 
uint8_t setConfigure :1; 
uint8_t setInterface :1;
uint8_t setIdle :1;
};
uint8_t all;
};
union ClearFutureEndpoint_IN{
  struct {
  uint16_t clearFutureEndPointHalt :1;
  uint16_t clearFutureEndPoint_81 :1;
  uint16_t clearFutureEndPoint_82 :1;
  uint16_t clearFutureEndPoint_83 :1;
  uint16_t clearFutureEndPoint_84 :1;
  uint16_t clearFutureEndPoint_85 :1;
  uint16_t clearFutureEndPoint_86 :1;
  uint16_t clearFutureEndPoint_87 :1;
  uint16_t clearFutureEndPoint_88 :1;
  uint16_t clearFutureEndPoint_89 :1;
  uint16_t clearFutureEndPoint_8A :1;
  uint16_t clearFutureEndPoint_8B :1;
  uint16_t clearFutureEndPoint_8C :1;
  uint16_t clearFutureEndPoint_8D :1;
  uint16_t clearFutureEndPoint_8E :1;
  uint16_t clearFutureEndPoint_8F :1;
  };
  uint16_t all;
};
union ClearFutureEndpoint_OUT{
  struct {
  uint16_t clearFutureEndPoint_01 :1;
  uint16_t clearFutureEndPoint_02 :1;
  uint16_t clearFutureEndPoint_03 :1;
  uint16_t clearFutureEndPoint_04 :1;
  uint16_t clearFutureEndPoint_05 :1;
  uint16_t clearFutureEndPoint_06 :1;
  uint16_t clearFutureEndPoint_07 :1;
  uint16_t clearFutureEndPoint_00 :1;
  uint16_t clearFutureEndPoint_09 :1;
  uint16_t clearFutureEndPoint_0A :1;
  uint16_t clearFutureEndPoint_0B :1;
  uint16_t clearFutureEndPoint_0C :1;
  uint16_t clearFutureEndPoint_0D :1;
  uint16_t clearFutureEndPoint_0E :1;
  uint16_t clearFutureEndPoint_0F :1;
  };
  uint16_t all;
};

 

union SetFutureEndpoint_IN{
  struct {
  uint16_t setFutureEndPoint :1;
  uint16_t setFutureEndPoint_81 :1;
  uint16_t setFutureEndPoint_82 :1;
  uint16_t setFutureEndPoint_83 :1;
  uint16_t setFutureEndPoint_84 :1;
  uint16_t setFutureEndPoint_85 :1;
  uint16_t setFutureEndPoint_86 :1;
  uint16_t setFutureEndPoint_87 :1;
  uint16_t setFutureEndPoint_88 :1;
  uint16_t setFutureEndPoint_89 :1;
  uint16_t setFutureEndPoint_8A :1;
  uint16_t setFutureEndPoint_8B :1;
  uint16_t setFutureEndPoint_8C :1;
  uint16_t setFutureEndPoint_8D :1;
  uint16_t setFutureEndPoint_8E :1;
  uint16_t setFutureEndPoint_8F :1;
  };
  uint16_t all;
};
union SetFutureEndpoint_OUT{
  struct {
  uint16_t setFutureEndPoint_01 :1;
  uint16_t setFutureEndPoint_02 :1;
  uint16_t setFutureEndPoint_03 :1;
  uint16_t setFutureEndPoint_04 :1;
  uint16_t setFutureEndPoint_05 :1;
  uint16_t setFutureEndPoint_06 :1;
  uint16_t setFutureEndPoint_07 :1;
  uint16_t setFutureEndPoint_00 :1;
  uint16_t setFutureEndPoint_09 :1;
  uint16_t setFutureEndPoint_0A :1;
  uint16_t setFutureEndPoint_0B :1;
  uint16_t setFutureEndPoint_0C :1;
  uint16_t setFutureEndPoint_0D :1;
  uint16_t setFutureEndPoint_0E :1;
  uint16_t setFutureEndPoint_0F :1;   
  };
  uint16_t all;
};  
            

union CDC_spec{
  struct {
  uint8_t CDC_setLineCodingSetup :1;
  uint8_t CDC_setLineCodingData :1;
  uint8_t CDC_setControllLineState :1;
  uint8_t CDC_getLineCoding :1;
  };
  uint8_t all;
};
};

static void GlobalControllProc(){
/*constexpr unsigned EPIndex(uint32_t m)//плучаем номер младшего установленного бита
{                                     //на этапе компиляции вычислит и присвоит лямбды в какомто порядке- не важно
    unsigned b = std::__countr_zero(m);

    return (b < 16) ? (b - 1)       // IN
                    : (31 - b + 15);// OUT
};
uint16_t flags;

while (SetUpFlags::CDC_spec.all)
{
    flags = SetUpFlags::CDC_spec.all;
    const unsigned bit = std::countr_zero(flags);

    SetUpFlags::CDC_spec.all = flags & (flags - 1);

    switch (bit)
    {
        case 0:
            if(SetupStage.Stage==enumSetupStage::SETUP){
            SetupStage.Stage=enumSetupStage::DATA;
            SetupStage.data_len=(uint16_t)buffer.wLengt;
            USBWRP::DevEndpointDataAck(CTR_EP, false);
            //ToDebugPrint.DebugPrintAdd(0,EP_CONTROL_STATUS_F,SET_CONFIGURATION,"SETUP STAGE CDC_SET_LINE_CODING");
            }
            else
            {
                Execute_ExtSetupHandler(USB_CDC_SET_LINE_CODING,0,buffer,(uint32_t&)SetupStage.data_len);  
                            USBWRP::DevEndpointDataAck(CTR_EP, true);
            SetupStage.Stage=enumSetupStage::SETUP;
            }                  
        break;
        case 1: ...
        break;
        case 2: ...
        break;
        case 3: ...
        break;
    //      uint8_t CDC_setLineCodingSetup :1;
 // uint8_t CDC_setLineCodingData :1;
 // uint8_t CDC_setControllLineState :1;
 // uint8_t CDC_getLineCoding :1
    }
}






		case GET_STATUS_DEVICE      :
		status_dev();
		break;

		case GET_STATUS_INTERF      :
		goto no_implementation;
		break;

		case GET_STATUS_ENDPNT      :
		goto no_implementation;
		break;

		case CLEAR_FEATURE_DEVICE:
                switch (buffer.wValueL)
                {
                    case 1: // DEVICE_REMOTE_WAKEUP
                        // remote_wakeup_enabled = 0;
                        USBWRP::DevEndpointDataAck(CTR_EP, true);
                        break;

                    default:
                        // CLEAR TEST_MODE по спеке нельзя
                        USBWRP::DevEndpointStall(CTR_EP);
                        break;
                }
                break;

		case CLEAR_FEATURE_INTERF   :
		goto no_implementation;
		break;

		case CLEAR_FEATURE_ENDPNT   :

                // уточняем feature = ENDPOINT_HALT (wValue == 0)
                if (buffer.wValue != 0)
                {
                    USBWRP::DevEndpointStall(CTR_EP);
                    break;
                }

                switch (buffer.wIndexL)
                {
                    case 0x81: 
                        Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x81);                                           
                        break;

                    case 0x02: 
                          Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x02);
                        break;

                    case 0x82: // EP2 IN — Bulk IN (типичный CDC)            
                        Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x82);
                        break;

                    case 0x83: // EP3 IN — только если такой endpoint есть
                         Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x83);
                        break;

                    case 0x01: // EP1 OUT — на всякий случай (в логе бывало wIndex=0001)
                        // если EP1 OUT нет в дескрипторах — можно просто ACK
                         Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x01);
                        break;

                    default:
                        USBWRP::DevEndpointStall(CTR_EP);
                        break;
                }
                break;

		case SET_FEATURE_DEVICE:
                  // wValue = feature
                  switch (buffer.wValueL)
                  {
                      case 1: // DEVICE_REMOTE_WAKEUP
                          // remote_wakeup_enabled = 1;
                          USBWRP::DevEndpointDataAck(CTR_EP, true);
                          break;

                      case 2: // TEST_MODE (для FS CDC обычно не нужен)
                          USBWRP::DevEndpointStall(CTR_EP);
                          break;

                      default:
                          USBWRP::DevEndpointStall(CTR_EP);
                          break;
                  }
                  break;

		case SET_FEATURE_INTERF     :
		goto no_implementation;
		break;

		case SET_FEATURE_ENDPNT     :
		goto no_implementation;
		break;

		case SET_ADDRESS            :
                Execute_ExtSetupHandler(SET_ADDRESS) ;
             //   USBWRP::DevEndpointDataAck(usb_base,USB_EP_0,true);
              //      while(!(HWREGB(usb_base+ USB_CSRL0 )&USB_CSRL0_SETEND));
              //     USBWRP::DevAddrSet(usb_base,(unsigned long)(buffer.wValueL&0x7F));
		break;

		case GET_DESCRIPTOR_DEVICE  :
              if(!USB_Descriptors<CTR_EP,DEVICE>::DescriptorSend(buffer.wValueH,buffer.wLengthL,buffer.wValueL))
              goto no_implementation;	
        	break;

		case GET_DESCRIPTOR_INTERF  :
                goto no_implementation;
		break;

		case GET_DESCRIPTOR_ENDPNT  :
		goto no_implementation;
		break;

		case SET_DESCRIPTOR         :
		goto no_implementation;
		break;

		case GET_CONFIGURATION      :
                if(!USB_Descriptors<CTR_EP,DEVICE>::DescriptorSend(buffer.wValueH,buffer.wLengthL,buffer.wValueL))
		goto no_implementation;
		break;

		case SET_CONFIGURATION  :
             // 
              //  Execute_ExtSetupHandler(SET_CONFIGURATION,0,buffer,(uint32_t&)device_state);
               // USBWRP::DevEndpointDataAck(CTR_EP,true);
                  USBDevEndpointDataAck(USB0_BASE, 0,true);
             //   ToDebugPrint.DebugPrintAdd(0,EP_CONTROL_STATUS_F,SET_CONFIGURATION,"SET_CONFIGURATION");
		break;

		case GET_INTERFACE          :
		goto no_implementation;
		break;

		case SET_INTERFACE          :
		goto no_implementation;
		break;

		case SYNCH_FRAME            :
		goto no_implementation;
		break;

		case GET_REPORT             :
		goto no_implementation;
		break;
		
		case SET_IDLE        	   :
		break;
                case USB_CDC_SET_LINE_CODING:
               

if(SetupStage.Stage==enumSetupStage::SETUP){
SetupStage.Stage=enumSetupStage::DATA;
SetupStage.data_len=(uint16_t)buffer.wLengt;
USBWRP::DevEndpointDataAck(CTR_EP, false);
//ToDebugPrint.DebugPrintAdd(0,EP_CONTROL_STATUS_F,SET_CONFIGURATION,"SETUP STAGE CDC_SET_LINE_CODING");
}
else
{
    Execute_ExtSetupHandler(USB_CDC_SET_LINE_CODING,0,buffer,(uint32_t&)SetupStage.data_len);  
                USBWRP::DevEndpointDataAck(CTR_EP, true);
SetupStage.Stage=enumSetupStage::SETUP;
}                  
                break;
                case USB_CDC_GET_LINE_CODING:

                // Отправляем текущую структуру Line Coding
                Execute_ExtSetupHandler(USB_CDC_GET_LINE_CODING) ; 



                // Завершаем control-transfer
                USBWRP::DevEndpointDataAck(CTR_EP, true);

                break;

    
            //    break;
                case USB_CDC_SET_CONTROL_LINE_STATE:
               Execute_ExtSetupHandler(USB_CDC_SET_CONTROL_LINE_STATE,0,buffer) ;

                USBWRP::DevEndpointDataAck(CTR_EP, true);
                 break;	
		
no_implementation:		
		default:
               // USBWRP::DevEndpointStall(CTR_EP);
		//stall();
		break;
	}

};


};//Class USB_Enumerator
*/



template<
auto CTR_EP, 
auto DEVICE
> class USB_Descriptors:USB_DescriptorTypes
{
inline static constexpr DeviceDescriptor_t  DeviceDescriptor=
 { //DeviceDescriptor
        .bLength=0x12,
	.bDescriptorType=0x01,
	.bcdUSBL=0x00,//in binary code decimal (i.e. 2.1 is 201H)
	.bcdUSBH=0x02,
	.bDeviceClass=0x00,
	.bDeviceSubClass=0x00,
	.bDeviceProtocol=0x00,
	.bMaxPacketSize=EP0_SZ,
	.idVendorL=DEVICE.vid&0xFF,
	.idVendorH=DEVICE.vid>>8,
	.idProductL=DEVICE.pid&0xFF,
	.idProductH=DEVICE.pid>>8,
	.bcdDeviceL=0x00,
	.bcdDeviceH=0x01,
	.iManufactured=0x01,
	.iProduct=0x02,
	.iSerialNumber=0x03,
	.bNumConfiguration=0x01
} ;

static_assert(sizeof(DeviceDescriptor) == 18,
          "DeviceDescriptor_t size error");

template<class Specific, uint8_t N>
constexpr static InterfaceDescriptor_t
MakeInterfaceDescriptor(const newIFC<Specific, N>& ifc)
{
    return {
        9,
        DESC_TYPE_INTERFACE,
        ifc.number,
        0,
        N,                 // bNumEndpoints
        ifc.i_class,
        ifc.sub_class,
        ifc.protocol,
        0
    };
}
//ENDPOINT DESCS
constexpr static EPDescriptor_t
MakeEndpointDescriptor(const Endpoint& ep)
{
    return {
        7,
        DESC_TYPE_ENDPOINT,
	 ep.address,	
	 ep.type, 
         static_cast<uint8_t>(ep.size&0xFF),
         static_cast<uint8_t>(ep.size>>8),
	 ep.interval
    };
}


template<class IFC, std::size_t... I>
constexpr static auto
MakeInterfaceEndpointDescriptors(
    const IFC& ifc,
    std::index_sequence<I...>)
{
    return std::array<EPDescriptor_t, sizeof...(I)>{
        MakeEndpointDescriptor(
            ifc.endpoints.endpoints[I]
        )...
    };
}
///***********

template<std::size_t... I>
constexpr static auto
MakeInterfaceDescriptors(std::index_sequence<I...>)
{
    return std::array<InterfaceDescriptor_t, sizeof...(I)>{
        MakeInterfaceDescriptor(
            get<I>(DEVICE.interfaces.interfaces)
        )...
    };
}


constexpr static auto InterfaceDesc =
    MakeInterfaceDescriptors(
        std::make_index_sequence<
            decltype(DEVICE.interfaces.interfaces)::size
        >{}
    );

static_assert(sizeof(InterfaceDesc[0]) == 9);



//**************************************СТРОИМ ИНТЕРФЕЙС

// результат для MakeInterface
template<class Specific, class IFC, std::size_t N>
struct InterfaceBlock
{
    InterfaceDescriptor_t descriptor;
    Specific specific;
    std::array<EPDescriptor_t, N> endpoints;
};

template<class IFC, std::size_t N>
struct InterfaceBlock<NoSpecific, IFC, N>
{
    InterfaceDescriptor_t descriptor;
    std::array<EPDescriptor_t, N> endpoints;
};

template<class IFC, std::size_t... I>
constexpr static auto
MakeInterface(
    const IFC& ifc,
    std::index_sequence<I...>)
{
    using Specific = typename IFC::SpecificType;

    if constexpr (std::is_same_v<Specific, NoSpecific>)
    {
        return InterfaceBlock<NoSpecific, IFC, sizeof...(I)>{
            MakeInterfaceDescriptor(ifc),
            MakeInterfaceEndpointDescriptors(
                ifc,
                std::index_sequence<I...>{}
            )
        };
    }
    else
    {
        return InterfaceBlock<Specific, IFC, sizeof...(I)>{
            MakeInterfaceDescriptor(ifc),
            ifc.specific,
            MakeInterfaceEndpointDescriptors(
                ifc,
                std::index_sequence<I...>{}
            )
        };
    }
}

//это собирает все интерфейсы в последпвательную структуру
template<class Tuple, std::size_t... I>
constexpr static auto
MakeInterfaces(
    const Tuple& interfaces,
    std::index_sequence<I...>)
{
    return CTuple<
        decltype(
            MakeInterface(
                get<I>(interfaces),
                std::make_index_sequence<
                    sizeof(get<I>(interfaces).endpoints.endpoints) /
                    sizeof(Endpoint)
                >{}
            )
        )...
    >{
        MakeInterface(
            get<I>(interfaces),
            std::make_index_sequence<
                sizeof(get<I>(interfaces).endpoints.endpoints) /
                sizeof(Endpoint)
            >{}
        )...
    };
}

constexpr static auto InterfaceBlocks =
    MakeInterfaces(
        DEVICE.interfaces.interfaces,
        std::make_index_sequence<
            decltype(DEVICE.interfaces.interfaces)::size
        >{}
    );

static_assert(
    decltype(InterfaceBlocks)::size == 2
);
constexpr static auto InterfaceCount =
    decltype(InterfaceBlocks)::size;

struct FullConfigurationDescriptor_t
{
    ConfigurationDescriptor_t cd;
    decltype(InterfaceBlocks) interfaces;
};





////configure total size
template<class Tuple, std::size_t... I>
constexpr static std::size_t
GetInterfacesSize(
    const Tuple& interfaces,
    std::index_sequence<I...>)
{
    return (sizeof(get<I>(interfaces)) + ...);
}

constexpr static auto config_total_len =
    sizeof(ConfigurationDescriptor_t) +
    GetInterfacesSize(
        InterfaceBlocks,
        std::make_index_sequence<
            decltype(InterfaceBlocks)::size
        >{}
    );



static constexpr uint8_t d_cfg_len=sizeof(ConfigurationDescriptor_t);

	
inline static constexpr
 ConfigurationDescriptor_t ConfigurationDescriptor={//ConfigurationDescriptor
		. bLength=d_cfg_len,
		. bDescriptorType=DESC_TYPE_CONFIGURATION,
		. wTotalLenghtL=static_cast<uint8_t>(config_total_len&0xFF),
		. wTotalLenghtH=static_cast<uint8_t>(config_total_len>>8),
		. bNumInterface=InterfaceCount,//число интерфейсов поддерживаемое конфигурацией
		. bConfigurationValue=0x01,//значение используемое SetConfiguration()  для выбора этой конфигурации
		. iConfiguration=0x00,//индекс строки описывающей конфигурацию
		. bmAttributes=0x80, //b5-remote wakeup,b6 - self powered
		. bMaxPower=0x32// 2 ma per units, i.e. 50 - 100 ma
	};



inline static constexpr struct __attribute__((packed)){
	ConfigurationDescriptor_t cd=ConfigurationDescriptor;
        decltype(InterfaceBlocks) interfaces = InterfaceBlocks;
    
}FullConfigurationDescriptor{};


static_assert(
sizeof(FullConfigurationDescriptor)==67
);
static_assert(sizeof(ConfigurationDescriptor_t) == 9);
static_assert(sizeof(InterfaceDescriptor_t) == 9);
static_assert(sizeof(EPDescriptor_t) == 7);
//static_assert(sizeof(InterfaceBlocks) == 58);

static_assert(sizeof(get<0>(InterfaceBlocks)) == 35);
static_assert(sizeof(get<1>(InterfaceBlocks)) == 23);
static_assert(sizeof(InterfaceDescriptor_t) == 9);
static_assert(sizeof(get<0>(InterfaceBlocks).specific) == 19);
static_assert(sizeof(get<0>(InterfaceBlocks).endpoints) == 7);
static_assert(
    sizeof(get<0>(get<0>(InterfaceBlocks).specific)) == 5
);

static_assert(
    sizeof(get<1>(get<0>(InterfaceBlocks).specific)) == 5
);

static_assert(
    sizeof(get<2>(get<0>(InterfaceBlocks).specific)) == 4
);

static_assert(
    sizeof(get<3>(get<0>(InterfaceBlocks).specific)) == 5
);
static_assert(alignof(get<0>(InterfaceBlocks)) == 1);
static_assert(alignof(get<1>(InterfaceBlocks)) == 1);
static_assert(alignof(decltype(InterfaceBlocks)) == 1);
static_assert(sizeof(decltype(InterfaceBlocks)) == 58);
#define LANG_ID               0x00
#define MAN_INDEX             0x01
#define PRD_INDEX             0x02
#define SRN_INDEX             0x03





static constexpr  StringDescriptor_t ManDescriptor ={
	14
	,DESC_TYPE_STRING
	,{L'A',L'n',L'd',L'r',L'e',L'w'}
	} ;
	
static constexpr StringDescriptor_t ProductDescriptor ={
	10
	,DESC_TYPE_STRING
	,{L'T',L'E',L'S',L'T',L'0'}
};

static constexpr StringDescriptor_t SerialNumber = {
    16,               // длина: 2 + 7*2
    DESC_TYPE_STRING, // тип = 0x03
    { L'1', L'2', L'3', L'4', L'5', L'6', L'7' }
};
static constexpr StringDescriptor_t LanguageDescriptor ={
	4
	,DESC_TYPE_STRING
	,{0x0409}
};
//////////////////////////
static void SetUpAnswer(uint8_t* buf,uint8_t buf_sz,uint8_t host_await_sz){

if(buf_sz==70){
uint8_t bpt=1;
}
        uint8_t byte_left= buf_sz>host_await_sz?host_await_sz:buf_sz;
        uint8_t* data_begin=buf;
uint8_t dbg_buf[170];
memcpy(dbg_buf,buf,buf_sz);

        while(byte_left>=EP0_SZ){
          uint8_t byte_to_transfer=EP0_SZ;      
          while( USBWRP::EndpointDataPut(CTR_EP,data_begin,byte_to_transfer)==-1){;}; 
        if(byte_left==0)      
          {while(USBWRP::EndpointDataSend(CTR_EP,USB_TRANS_IN)==-1){;};break;}
        else {while(USBWRP::EndpointDataSend(CTR_EP,USB_TRANS_IN)==-1){;}};
        byte_left-=byte_to_transfer;
        data_begin+=byte_to_transfer;
	}
        //0<byte_left<EP0_SZ
  //      memcpy(dbg_buf,buf,buf_sz);
        while( USBWRP::EndpointDataPut(CTR_EP,data_begin,byte_left)==-1){;};
        //uint32_t cnt = HWREGB(USB0_BASE + USB_O_COUNT0);
        while( USBWRP::EndpointDataSend(CTR_EP,USB_TRANS_IN_LAST)==-1){;};
}
public:
static bool DescriptorSend(uint8_t desc_type,uint16_t host_await_sz,uint8_t index=0){

		switch(desc_type){

			case DESC_TYPE_DEVICE:

			SetUpAnswer((uint8_t*)&DeviceDescriptor,sizeof(DeviceDescriptor),host_await_sz);


                        return true;

			case DESC_TYPE_CONFIGURATION:{
			uint16_t dbg =sizeof(FullConfigurationDescriptor);
                        SetUpAnswer((uint8_t*)&FullConfigurationDescriptor,sizeof(FullConfigurationDescriptor),host_await_sz);
			return true;
                        }

			case DESC_TYPE_STRING:	
			return string(index,host_await_sz);

			case DESC_TYPE_INTERFACE:
			break;
			case DESC_TYPE_ENDPOINT:
			break;
			case DESC_TYPE_DEVICE_QUALIFIER:
			break;
			case DESC_TYPE_OTHER_SPEED_CONFIGURATION:
			break;
			case DESC_TYPE_INTERFACE_POWER1:
			break;
		}
return false;
 }   
private:
static bool string(uint8_t index ,uint8_t host_await_sz){
    switch (index){
    case 0:
    SetUpAnswer((uint8_t*)&LanguageDescriptor,sizeof(LanguageDescriptor),host_await_sz);
    return true;
    case 1:
    SetUpAnswer((uint8_t*)&ManDescriptor,sizeof(ManDescriptor),host_await_sz);
    return true;
    break;
    case 2:
    SetUpAnswer((uint8_t*)&ProductDescriptor,sizeof(ProductDescriptor),host_await_sz);
    return true;
    case 3:
    SetUpAnswer((uint8_t*)&SerialNumber,sizeof(SerialNumber),host_await_sz);
    return true;
    }
    return false;
  }

};//desc class




