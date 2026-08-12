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

#define USB_GEN_INT_EN USB_INTCTRL_RESET|USB_INTCTRL_SUSPEND|USB_INTCTRL_RESUME|USB_INTCTRL_SOF

template<
uint32_t usb_base,
auto 
>
class USBEnumerator;
class USB_DescriptorTypes;


template<auto CDC_DC>
class USB_Descriptors;

class UsbISR:IPeriferalISR{
public:
void Registration(std::function<void()> isr, uint32_t sw_def, ...);
};

//////////////////////////CLASS USB
template<
uint32_t usb_base,
uint32_t usb_int,//INT_USB0
uint32_t sysctl_periferal,//SYSCTL_PERIFERAL_USB0
auto usb_dev  //DEVICE_CLASS
>
class USB{
enum _device_state device_state; 

//INTERRUPT
UsbISR UISR;
public:
USB(){
  UISR.Registration([this](){
      this->ISR();
      },usb_base);

  ExtSetupHandlerRegister([this](const _Buffer& su_buf,uint32_t& sup_data){

                   USBWRP::DevEndpointDataAck(usb_base, MyUSB_EP::EP0,false);
                         while(!(HWREGB(usb_base+ USB_CSRL0 )&USB_CSRL0_SETEND));
                   USBWRP::DevAddrSet(usb_base,(unsigned long)(buffer.wValueL&0x7F));

                    device_state=Adressed;
                  },
                  SET_ADDRESS);

////////USB INIT
 MAP_SysCtlPeripheralEnable(sysctl_periferal);

  //The next step is to enable the USB PLL 
  //so that the correct clocking is provided to the PHY.

  MAP_SysCtlUSBPLLEnable();

 // USBIntRegister(usb_base, ISR_USB);
  
MAP_IntEnable(usb_int);

USBWRP::IntDisableControl(usb_base,USB_INTCTRL_ALL);
USBWRP::IntEnableControl(usb_base,USB_GEN_INT_EN);

USBWRP::IntDisableEndpoint(usb_base,USB_INTEP_ALL);
USBWRP::IntEnableEndpoint(usb_base,USB_INT_EP0);

USBWRP::IntEnable(usb_base,USB_INT_ALL );

USBWRP::DevConnect(usb_base);

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
  int_COM_status=USBWRP::IntStatusEndpoint(usb_base);
  if(int_COM_status!=0)
    USB_COM_Vector(int_COM_status);
  int_GEN_status=USBWRP::IntStatusControl(usb_base);
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
unsigned long SetupPacketSz = USBWRP::EndpointDataAvail(usb_base, MyUSB_EP::EP0);

  if(SetupPacketSz>0)
  {
   Enumerator.USB_COM_Vector(int_COM_status,SetupPacketSz,device_state);
  //  int_COM_status&=~(USB_INTEP_0);
  }
}
USB_COM_Handlers<usb_base>::Execute(int_COM_status);

return 0;
}

////////////////////

USBEnumerator<usb_base,usb_dev>Enumerator;
USB_Descriptors<usb_dev> Descriptors;

};//class USB


template<
uint32_t usb_base,
auto usb_dev
>
class USBEnumerator{
 inline static SetupStage_t SetupStage;
 
static void EP_StatusClear(MyUSB_EP ep){
 uint32_t st  = USBWRP::EndpointStatus(usb_base, ep);
    USBWRP::DevEndpointStatusClear(usb_base, ep, st);
}


public:
inline int USB_COM_Vector(uint32_t int_COM_status,unsigned long   SetupPacketSz,_device_state& device_state){

    USBWRP::EndpointDataGet (usb_base,  MyUSB_EP::EP0, (uint8_t*)&buffer,  &SetupPacketSz);
      if(SetupStage.Stage==SETUP)
          SetupStage.Request=buffer.wRequest;
    processingSetupPackage(SetupStage.Request,device_state);

return 0;
}

//////////////////
static void processingSetupPackage(uint16_t rq,_device_state& device_state){
	
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
                        USBWRP::DevEndpointDataAck(usb_base,  MyUSB_EP::EP0, true);
                        break;

                    default:
                        // CLEAR TEST_MODE по спеке нельзя
                        USBWRP::DevEndpointStall(usb_base,  MyUSB_EP::EP0, USB_EP_DEV_OUT);
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
                    USBWRP::DevEndpointStall(usb_base,  MyUSB_EP::EP0, USB_EP_DEV_OUT);
                    break;
                }

                switch (buffer.wIndexL)
                {
                    case 0x81: // EP1 IN — Interrupt (SERIAL_STATE)
                        USBWRP::DevEndpointStallClear(usb_base,  MyUSB_EP::EP1, USB_EP_DEV_IN);
                        USBWRP::EndpointDataToggleClear(usb_base, MyUSB_EP::EP1, USB_EP_DEV_IN);
                        EP_StatusClear( MyUSB_EP::EP1);
                        Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x81);
                        USBWRP::DevEndpointDataAck(usb_base,  MyUSB_EP::EP0, true);
                        break;

                    case 0x02: // EP2 OUT — Bulk OUT
                        USBWRP::DevEndpointStallClear(usb_base,  MyUSB_EP::EP2, USB_EP_DEV_OUT);
                        USBWRP::EndpointDataToggleClear(usb_base, MyUSB_EP::EP2, USB_EP_DEV_OUT);
                         EP_StatusClear( MyUSB_EP::EP2);
                          Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x02);
                        USBWRP::DevEndpointDataAck(usb_base,  MyUSB_EP::EP0, true);
                        // снова разрешить приём на OUT
                        USBWRP::DevEndpointDataAck(usb_base,  MyUSB_EP::EP2, false);

                        break;

                    case 0x82: // EP2 IN — Bulk IN (типичный CDC)
                        EP_StatusClear(MyUSB_EP::EP2);
                        USBWRP::EndpointDataToggleClear(usb_base, MyUSB_EP::EP2, USB_EP_DEV_IN);             
                        Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x82);
                        USBWRP::DevEndpointStallClear(usb_base,  MyUSB_EP::EP2, USB_EP_DEV_IN);
                        SysCtlDelay(DELAY_LOAD_1us*100);
                        USBWRP::DevEndpointDataAck(usb_base,  MyUSB_EP::EP0, true);
                        break;

                    case 0x83: // EP3 IN — только если такой endpoint есть
                        USBWRP::DevEndpointStallClear(usb_base,  MyUSB_EP::EP3, USB_EP_DEV_IN);
                        USBWRP::EndpointDataToggleClear(usb_base, MyUSB_EP::EP3, USB_EP_DEV_IN);
                         Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x83);
                        USBWRP::DevEndpointDataAck(usb_base,  MyUSB_EP::EP0, true);
                        break;

                    case 0x01: // EP1 OUT — на всякий случай (в логе бывало wIndex=0001)
                        // если EP1 OUT нет в дескрипторах — можно просто ACK
                         Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x01);
                        USBWRP::DevEndpointDataAck(usb_base,  MyUSB_EP::EP0, true);
                        break;

                    default:
                        USBWRP::DevEndpointStall(usb_base, MyUSB_EP::EP0, USB_EP_DEV_OUT);
                        break;
                }
                break;

		case SET_FEATURE_DEVICE:
                  // wValue = feature
                  switch (buffer.wValueL)
                  {
                      case 1: // DEVICE_REMOTE_WAKEUP
                          // remote_wakeup_enabled = 1;
                          USBWRP::DevEndpointDataAck(usb_base, MyUSB_EP::EP0, true);
                          break;

                      case 2: // TEST_MODE (для FS CDC обычно не нужен)
                          USBWRP::DevEndpointStall(usb_base, MyUSB_EP::EP0, USB_EP_DEV_OUT);
                          break;

                      default:
                          USBWRP::DevEndpointStall(usb_base, MyUSB_EP::EP0, USB_EP_DEV_OUT);
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
              if(!USB_Descriptors<usb_dev>::DescriptorSend(buffer.wValueH,buffer.wLengthL,buffer.wValueL))
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
		goto no_implementation;
		break;

		case SET_CONFIGURATION      :

                Execute_ExtSetupHandler(SET_CONFIGURATION,0,buffer,(uint32_t&)device_state);
                USBDevEndpointDataAck(usb_base, 0,true);
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
USBWRP::DevEndpointDataAck(usb_base, MyUSB_EP::EP0, false);
//ToDebugPrint.DebugPrintAdd(0,EP_CONTROL_STATUS_F,SET_CONFIGURATION,"SETUP STAGE CDC_SET_LINE_CODING");
}
else
{
    Execute_ExtSetupHandler(USB_CDC_SET_LINE_CODING,0,buffer,(uint32_t&)SetupStage.data_len);  
                USBWRP::DevEndpointDataAck(usb_base, MyUSB_EP::EP0, true);
SetupStage.Stage=enumSetupStage::SETUP;
}                  
                break;
                case USB_CDC_GET_LINE_CODING:

                // Отправляем текущую структуру Line Coding
                Execute_ExtSetupHandler(USB_CDC_GET_LINE_CODING) ; 



                // Завершаем control-transfer
                USBWRP::DevEndpointDataAck(usb_base, MyUSB_EP::EP0, true);

                break;

    
            //    break;
                case USB_CDC_SET_CONTROL_LINE_STATE:
               Execute_ExtSetupHandler(USB_CDC_SET_CONTROL_LINE_STATE,0,buffer) ;

                USBWRP::DevEndpointDataAck(usb_base, MyUSB_EP::EP0, true);
                 break;	
		
no_implementation:		
		default:
                USBWRP::DevEndpointStall(usb_base,MyUSB_EP::EP0,USB_EP_DEV_IN);
		//stall();
		break;
	}
};//Process packet


static void status_dev(){
//bus powred, remote wakeup
SetUpAnswer((uint8_t*)&STATUS_DEVICE,sizeof(STATUS_DEVICE),buffer.wLengthL);
        USBWRP::EndpointDataPut(usb_base, MyUSB_EP::EP0, (uint8_t*)&STATUS_DEVICE, buffer.wLengthL);
}
static void SetUpAnswer(uint8_t* buf,uint8_t buf_sz,uint8_t host_await_sz){

        uint8_t byte_left= buf_sz>host_await_sz?host_await_sz:buf_sz;
        uint8_t* data_begin=buf;


        while(byte_left>=EP0_SZ){
          uint8_t byte_to_transfer=EP0_SZ;      
          while( USBWRP::EndpointDataPut(usb_base,MyUSB_EP::EP0,data_begin,byte_to_transfer)==-1){;}; 
        if(byte_left==0)      
          {while(USBWRP::EndpointDataSend(usb_base,MyUSB_EP::EP0,USB_TRANS_IN)==-1){;};break;}
        else {while(USBWRP::EndpointDataSend(usb_base,MyUSB_EP::EP0,USB_TRANS_IN)==-1){;}};
        byte_left-=byte_to_transfer;
        data_begin+=byte_to_transfer;
	}
        //0<byte_left<EP0_SZ
        while( USBWRP::EndpointDataPut(usb_base,MyUSB_EP::EP0,data_begin,byte_left)==-1){;};
        while( USBWRP::EndpointDataSend(usb_base,MyUSB_EP::EP0,USB_TRANS_IN_LAST)==-1){;};
}

};//Class USB_Enumerator




template<
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

/*template<class Specific,class IFC, std::size_t N>
struct  __attribute__((packed))InterfaceBlock
{
    InterfaceDescriptor_t descriptor;
    Specific specific;
    std::array<EPDescriptor_t, N> endpoints;
};*/
/*template<class IFC, std::size_t... I>
constexpr static auto
MakeInterface(
    const IFC& ifc,
    std::index_sequence<I...>)
{
    if constexpr (std::is_same_v<typename IFC::Specific, NoSpecific>)
    {
        return InterfaceBlock<
            NoSpecific,
            IFC,
            sizeof...(I)
        >{
            MakeInterfaceDescriptor(ifc),
            MakeInterfaceEndpointDescriptors(
                ifc,
                std::index_sequence<I...>{}
            )
        };
    }
    else
    {
        return InterfaceBlock<
            typename IFC::Specific,
            IFC,
            sizeof...(I)
        >{
            MakeInterfaceDescriptor(ifc),
            ifc.specific,
            MakeInterfaceEndpointDescriptors(
                ifc,
                std::index_sequence<I...>{}
            )
        };
    }
}*/
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

/*template<class Specific, uint8_t N, std::size_t... I>
constexpr static auto
MakeInterface(
    const newIFC<Specific, N>& ifc,
    std::index_sequence<I...>)
{
    return InterfaceBlock<
        Specific,
        newIFC<Specific, N>,
        sizeof...(I)
    >{
        MakeInterfaceDescriptor(ifc),
        ifc.specific,
        MakeInterfaceEndpointDescriptors(
            ifc,
            std::index_sequence<I...>{}
        )
    };
}*/
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
          while( USBWRP::EndpointDataPut(USB0_BASE,MyUSB_EP::EP0,data_begin,byte_to_transfer)==-1){;}; 
        if(byte_left==0)      
          {while(USBWRP::EndpointDataSend(USB0_BASE,MyUSB_EP::EP0,USB_TRANS_IN)==-1){;};break;}
        else {while(USBWRP::EndpointDataSend(USB0_BASE,MyUSB_EP::EP0,USB_TRANS_IN)==-1){;}};
        byte_left-=byte_to_transfer;
        data_begin+=byte_to_transfer;
	}
        //0<byte_left<EP0_SZ
  //      memcpy(dbg_buf,buf,buf_sz);
        while( USBWRP::EndpointDataPut(USB0_BASE,MyUSB_EP::EP0,data_begin,byte_left)==-1){;};
        //uint32_t cnt = HWREGB(USB0_BASE + USB_O_COUNT0);
        while( USBWRP::EndpointDataSend(USB0_BASE,MyUSB_EP::EP0,USB_TRANS_IN_LAST)==-1){;};
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




