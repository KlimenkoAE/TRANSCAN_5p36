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
#include "USB_THIS_PROGRAM_DEFS.hpp"
#include "periferalInterruptsHandlers.hpp"

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

                   MAP_USBDevEndpointDataAck(usb_base,USB_EP_0,false);
                         while(!(HWREGB(usb_base+ USB_CSRL0 )&USB_CSRL0_SETEND));
                   MAP_USBDevAddrSet(usb_base,(unsigned long)(buffer.wValueL&0x7F));

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

MAP_USBIntDisableControl(usb_base,USB_INTCTRL_ALL);
MAP_USBIntEnableControl(usb_base,USB_GEN_INT_EN);

MAP_USBIntDisableEndpoint(usb_base,USB_INTEP_ALL);
MAP_USBIntEnableEndpoint(usb_base,USB_INT_EP0);

MAP_USBIntEnable(usb_base,USB_INT_ALL );

MAP_USBDevConnect(usb_base);

/*
volatile uint8_t txmaxp0;
volatile uint8_t rxmaxp0;
volatile uint8_t txfifosz;
volatile uint8_t rxfifosz;
volatile uint8_t txfifoadd;
volatile uint8_t rxfifoadd;

txmaxp0   = HWREGB(USB0_BASE + USB_O_TXMAXP1);
rxmaxp0   = HWREGB(USB0_BASE + USB_O_RXMAXP1);

txfifosz  = HWREGB(USB0_BASE + USB_O_TXFIFOSZ);
rxfifosz  = HWREGB(USB0_BASE + USB_O_RXFIFOSZ);

txfifoadd = HWREGB(USB0_BASE + USB_O_TXFIFOADD);
rxfifoadd = HWREGB(USB0_BASE + USB_O_RXFIFOADD);


volatile uint8_t csr0;
volatile uint8_t count0;
volatile uint8_t type0;

csr0   = HWREGB(USB0_BASE + USB_O_CSRL0);
count0 = HWREGB(USB0_BASE + USB_O_COUNT0);
type0  = HWREGB(USB0_BASE + USB_O_TYPE0); */  // если есть

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
  int_COM_status=MAP_USBIntStatusEndpoint(USB0_BASE);
  if(int_COM_status!=0)
    USB_COM_Vector(int_COM_status);
  int_GEN_status=MAP_USBIntStatusControl(USB0_BASE);
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
unsigned long SetupPacketSz = MAP_USBEndpointDataAvail(usb_base, USB_EP_0);

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
 
static void EP_StatusClear(uint32_t ep){
 uint32_t st  = USBEndpointStatus(usb_base, ep);
    MAP_USBDevEndpointStatusClear(usb_base, ep, st);
}


public:
inline int USB_COM_Vector(uint32_t int_COM_status,unsigned long   SetupPacketSz,_device_state& device_state){

    MAP_USBEndpointDataGet (usb_base, USB_EP_0, (uint8_t*)&buffer,  &SetupPacketSz);
 uint32_t dbg_reg= HWREGB(usb_base + USB_O_CSRL0);
      if(SetupStage.Stage==SETUP)
          SetupStage.Request=buffer.wRequest;// (uint16_t)(buffer.bmRequestType)<<8|(buffer.bRequest);
    processingSetupPackage(SetupStage.Request,device_state);
 //    dbg_reg= HWREGB(usb_base + USB_O_CSRL0);
//    uint32_t dbg_stop=0;
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
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    default:
                        // CLEAR TEST_MODE по спеке нельзя
                        MAP_USBDevEndpointStall(usb_base, USB_EP_0, USB_EP_DEV_OUT);
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
                    MAP_USBDevEndpointStall(usb_base, USB_EP_0, USB_EP_DEV_OUT);
                    break;
                }

                switch (buffer.wIndexL)
                {
                    case 0x81: // EP1 IN — Interrupt (SERIAL_STATE)
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_1, USB_EP_DEV_IN);
                        MAP_USBEndpointDataToggleClear(usb_base, USB_EP_1, USB_EP_DEV_IN);
                         EP_StatusClear(USB_EP_1);
                        Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x81);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    case 0x02: // EP2 OUT — Bulk OUT
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_2, USB_EP_DEV_OUT);
                        MAP_USBEndpointDataToggleClear(usb_base, USB_EP_2, USB_EP_DEV_OUT);
                         EP_StatusClear(USB_EP_2);
                          Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x02);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        // снова разрешить приём на OUT
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_2, false);

                        break;

                    case 0x82: // EP2 IN — Bulk IN (типичный CDC)
                        EP_StatusClear(USB_EP_2);
                        MAP_USBEndpointDataToggleClear(usb_base, USB_EP_2, USB_EP_DEV_IN);             
                        Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x82);
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_2, USB_EP_DEV_IN);
                        SysCtlDelay(DELAY_LOAD_1us*100);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    case 0x83: // EP3 IN — только если такой endpoint есть
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_3, USB_EP_DEV_IN);
                        MAP_USBEndpointDataToggleClear(usb_base, USB_EP_3, USB_EP_DEV_IN);
                         Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x83);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    case 0x01: // EP1 OUT — на всякий случай (в логе бывало wIndex=0001)
                        // если EP1 OUT нет в дескрипторах — можно просто ACK
                         Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x01);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    default:
                        MAP_USBDevEndpointStall(usb_base, USB_EP_0, USB_EP_DEV_OUT);
                        break;
                }
                break;

		case SET_FEATURE_DEVICE:
                  // wValue = feature
                  switch (buffer.wValueL)
                  {
                      case 1: // DEVICE_REMOTE_WAKEUP
                          // remote_wakeup_enabled = 1;
                          MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                          break;

                      case 2: // TEST_MODE (для FS CDC обычно не нужен)
                          MAP_USBDevEndpointStall(usb_base, USB_EP_0, USB_EP_DEV_OUT);
                          break;

                      default:
                          MAP_USBDevEndpointStall(usb_base, USB_EP_0, USB_EP_DEV_OUT);
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
             //   MAP_USBDevEndpointDataAck(usb_base,USB_EP_0,true);
              //      while(!(HWREGB(usb_base+ USB_CSRL0 )&USB_CSRL0_SETEND));
              //     MAP_USBDevAddrSet(usb_base,(unsigned long)(buffer.wValueL&0x7F));
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
MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, false);
//ToDebugPrint.DebugPrintAdd(0,EP_CONTROL_STATUS_F,SET_CONFIGURATION,"SETUP STAGE CDC_SET_LINE_CODING");
}
else
{
    Execute_ExtSetupHandler(USB_CDC_SET_LINE_CODING,0,buffer,(uint32_t&)SetupStage.data_len);  
                MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
SetupStage.Stage=enumSetupStage::SETUP;
}                  
                break;
                case USB_CDC_GET_LINE_CODING:

                // Отправляем текущую структуру Line Coding
                Execute_ExtSetupHandler(USB_CDC_GET_LINE_CODING) ; 



                // Завершаем control-transfer
                MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);

                break;

    
            //    break;
                case USB_CDC_SET_CONTROL_LINE_STATE:
               Execute_ExtSetupHandler(USB_CDC_SET_CONTROL_LINE_STATE,0,buffer) ;

                MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                 break;	
		
no_implementation:		
		default:
                USBDevEndpointStall(usb_base,USB_EP_0,USB_EP_DEV_IN);
		//stall();
		break;
	}
};//Process packet


static void status_dev(){
//bus powred, remote wakeup
SetUpAnswer((uint8_t*)&STATUS_DEVICE,sizeof(STATUS_DEVICE),buffer.wLengthL);
        MAP_USBEndpointDataPut(usb_base, USB_EP_0, (uint8_t*)&STATUS_DEVICE, buffer.wLengthL);
}
static void SetUpAnswer(uint8_t* buf,uint8_t buf_sz,uint8_t host_await_sz){

        uint8_t byte_left= buf_sz>host_await_sz?host_await_sz:buf_sz;
        uint8_t* data_begin=buf;


        while(byte_left>=EP0_SZ){
          uint8_t byte_to_transfer=EP0_SZ;      
          while( MAP_USBEndpointDataPut(usb_base,USB_EP_0,data_begin,byte_to_transfer)==-1){;}; 
        if(byte_left==0)      
          {while(MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN)==-1){;};break;}
        else {while(MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN)==-1){;}};
        byte_left-=byte_to_transfer;
        data_begin+=byte_to_transfer;
	}
        //0<byte_left<EP0_SZ
        while( MAP_USBEndpointDataPut(usb_base,USB_EP_0,data_begin,byte_left)==-1){;};
        while( MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN_LAST)==-1){;};
}

};//Class USB_Enumerator






/*ConfigurationDescriptor_t cd;
        InterfaceDescriptor_t idCommunication;
        CDCHeaderDescriptor_t cdc_h;
        CDCCallManagementDescriptor_t cdc_callMan;
        CDCACMDescriptor_t cdc_acm;
        CDCUnionDescriptor_t cdc_union;
        EPDescriptor_t ep_communication;

        InterfaceDescriptor_t idData;
       
       EPDescriptor_t ep_data_in;
       EPDescriptor_t ep_data_out;*/
//////////////////////////////////////////////////////////////////////////////



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


//constexpr static InterfaceDescriptor_t<> interfaceces_descs[CDC_DC.cdc_interfaces.cnt]=

constexpr static InterfaceDescriptor_t
MakeInterfaceDescriptor(const auto& ifc)
{
    return {
        9,
        DESC_TYPE_INTERFACE,
        ifc.number,
        0,
        ifc.ep_cnt,
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

// результата для MakeInterface
template<class IFC, std::size_t N>
struct InterfaceBlock
{
    InterfaceDescriptor_t descriptor;
    typename IFC::Specific specific;
    std::array<EPDescriptor_t, N> endpoints;
};
//это собирает один интерфейс
//template<class Tuple, std::size_t
template<class IFC, std::size_t... I>
constexpr static auto
MakeInterface(
    const IFC& ifc,
    std::index_sequence<I...>)
{
    return InterfaceBlock<IFC, sizeof...(I)>{
        MakeInterfaceDescriptor(ifc),
        ifc.specific,
        MakeInterfaceEndpoints(
            ifc,
            std::index_sequence<I...>{}
        )
    };
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

struct FullConfigurationDescriptor_t
{
    ConfigurationDescriptor_t cd;
    decltype(InterfaceBlocks) interfaces;
};

constexpr static FullConfigurationDescriptor_t
FullConfigurationDescriptor{
    ConfigurationDescriptor,
    InterfaceBlocks
};



//**********************
static constexpr uint16_t config_total_len=
+sizeof(ConfigurationDescriptor_t)
+DEVICE.interfaces.cnt*sizeof(InterfaceDesc[0])
+sizeof(CDCHeaderDescriptor_t)
+sizeof(CDCACMDescriptor_t)
+sizeof(CDCCallManagementDescriptor_t)
+sizeof(CDCUnionDescriptor_t)
+DEVICE.endpoints.cnt*sizeof(EndpointDesc[0]);

static constexpr uint8_t d_cfg_len=sizeof(ConfigurationDescriptor_t);
	
inline static constexpr
 ConfigurationDescriptor_t ConfigurationDescriptor={//ConfigurationDescriptor
		. bLength=d_cfg_len,
		. bDescriptorType=DESC_TYPE_CONFIGURATION,
		. wTotalLenghtL=config_total_len&0xFF,
		. wTotalLenghtH=config_total_len>>8,
		. bNumInterface=DEVICE.interfaces.cnt,//число интерфейсов поддерживаемое конфигурацией
		. bConfigurationValue=0x01,//значение используемое SetConfiguration()  для выбора этой конфигурации
		. iConfiguration=0x00,//индекс строки описывающей конфигурацию
		. bmAttributes=0x80, //b5-remote wakeup,b6 - self powered
		. bMaxPower=0x32// 2 ma per units, i.e. 50 - 100 ma
	};





//////////////////////////CDC

inline static constexpr
CDCHeaderDescriptor_t CDCHeaderDescriptor=
{//CDCHeaderDescriptor
    . bFunctionLength=0x05,      // Размер этого функционального дескриптора (байт)
    . bDescriptorType=0x24,      // CS_INTERFACE (0x24) - класс-специфический дескриптор интерфейса
    . bDescriptorSubtype=0x00,   // Header Functional Descriptor (0x00)
    . bcdCDC_L=0x10,             // Версия спецификации CDC, младший байт
    . bcdCDC_H=0x01             // Версия спецификации CDC, старший байт
} ;

inline static constexpr 
CDCACMDescriptor_t CDCACMDescriptor=
{//CDCACMDescriptor
    . bFunctionLength=0x04,      // Размер дескриптора
    . bDescriptorType=0x24,      // CS_INTERFACE (0x24)
    . bDescriptorSubtype=0x02,   // Abstract Control Management Functional Descriptor (0x02)
    . bmCapabilities=0x02       // Возможности ACM-интерфейса
                                // bit0 = поддержка Set_Comm_Feature/Clear_Comm_Feature
                                // bit1 = поддержка Set_Line_Coding,
                                //        Set_Control_Line_State,
                                //        Get_Line_Coding
                                // bit2 = Send_Break
                                // bit3 = Network Connection
} ;

inline static constexpr 
CDCCallManagementDescriptor_t CDCCallManagementDescriptor=
{//CDCCallManagementDescriptor
    .bFunctionLength=0x05,      // Размер дескриптора
    .bDescriptorType=0x24,      // CS_INTERFACE (0x24)
    .bDescriptorSubtype=0x01,   // Call Management Functional Descriptor (0x01)
    .bmCapabilities=0x00,       // Возможности управления вызовами
                               // bit0 = устройство самостоятельно обрабатывает Call Management
                               // bit1 = Data Interface используется для Call Management

    .bDataInterface=0x01       // Номер Data Interface
} ;

inline static constexpr 
CDCUnionDescriptor_t CDCUnionDescriptor
{//CDCUnionDescriptor
    .bFunctionLength=0x05,        // Размер дескриптора
    .bDescriptorType=0x24,        // CS_INTERFACE (0x24)
   .bDescriptorSubtype=0x06,     // Union Functional Descriptor (0x06)

    .bMasterInterface=0x00,       // Номер Communication Interface

    .bSlaveInterface0=0x01       // Номер первого Data Interface
} ;


/* InterfaceDescriptor_t idCommunication;
        CDCHeaderDescriptor_t cdc_h;
        CDCCallManagementDescriptor_t cdc_callMan;
        CDCACMDescriptor_t cdc_acm;
        CDCUnionDescriptor_t cdc_union;
        EPDescriptor_t ep_communication;

        InterfaceDescriptor_t idData;
       
       EPDescriptor_t ep_data_in;
       EPDescriptor_t ep_data_out;*/

inline static constexpr struct{
	ConfigurationDescriptor_t cd=ConfigurationDescriptor,
        InterfaceDescriptor_t=InterfaceDesc[0],
        CDCHeaderDescriptor_t cdc_h=CDCHeaderDescriptor,
        CDCCallManagementDescriptor_t cdc_callMan=CDCCallManagementDescriptor,
        CDCACMDescriptor_t cdc_acm=CDCACMDescriptor,
        CDCUnionDescriptor_t cdc_union=CDCUnionDescriptor,
        EPDescriptor_t ep_communication=EndpointDesc[0],

        InterfaceDescriptor_t idData=InterfaceDesc[0],
        EPDescriptor_t ep_data_in=EndpointDesc[1],
        EPDescriptor_t ep_data_out=EndpointDesc[2]
    
}FullConfigurationDescriptor{};


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

        uint8_t byte_left= buf_sz>host_await_sz?host_await_sz:buf_sz;
        uint8_t* data_begin=buf;
uint8_t dbg_buf[64];
memcpy(dbg_buf,buf,buf_sz);

        while(byte_left>=EP0_SZ){
          uint8_t byte_to_transfer=EP0_SZ;      
          while( MAP_USBEndpointDataPut(USB0_BASE,USB_EP_0,data_begin,byte_to_transfer)==-1){;}; 
        if(byte_left==0)      
          {while(MAP_USBEndpointDataSend(USB0_BASE,USB_EP_0,USB_TRANS_IN)==-1){;};break;}
        else {while(MAP_USBEndpointDataSend(USB0_BASE,USB_EP_0,USB_TRANS_IN)==-1){;}};
        byte_left-=byte_to_transfer;
        data_begin+=byte_to_transfer;
	}
        //0<byte_left<EP0_SZ
        while( MAP_USBEndpointDataPut(USB0_BASE,USB_EP_0,data_begin,byte_left)==-1){;};
        //uint32_t cnt = HWREGB(USB0_BASE + USB_O_COUNT0);
        while( MAP_USBEndpointDataSend(USB0_BASE,USB_EP_0,USB_TRANS_IN_LAST)==-1){;};
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




